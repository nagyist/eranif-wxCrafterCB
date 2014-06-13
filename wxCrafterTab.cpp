#include <wx/app.h>
#include "wxCrafterTab.h"
#include "wxCrafterCB.h"
#include <projectmanager.h>
#include <cbworkspace.h>
#include "NewWxCrafterFileDlg.h"
#include "wxcHelper.h"
#include "wxcHelper.h"
#include <cbproject.h>
#include <wx/menu.h>
#include "NewCodeBlocksProjectWizard.h"
#include <configmanager.h>
#include "wxCrafterSettingsDlg.h"

class wxCrafterTabItemData : public wxTreeItemData
{
public:
    enum {
        kKindFile    = 0,
        kKindProject = 1,
    };
protected:
    wxString m_filename;
    int      m_kind;

public:
    wxCrafterTabItemData(const wxString& filename) : m_filename(filename), m_kind(kKindFile) {}
    wxCrafterTabItemData(int kind) : m_kind(kind) {}

    void SetFilename(const wxString& filename) {
        this->m_filename = filename;
    }
    const wxString& GetFilename() const {
        return m_filename;
    }
    int GetKind() const {
        return m_kind;
    }
};

// -----------------------------------

wxCrafterTab::wxCrafterTab(wxWindow* parent, wxCrafterCB* plugin)
    : wxCrafterTabBase(parent)
    , m_plugin(plugin)
{
    m_treeCtrl->AssignImageList( new wxcImages() );
    Manager::Get()->RegisterEventSink(cbEVT_WORKSPACE_CHANGED, new cbEventFunctor<wxCrafterTab, CodeBlocksEvent>(this, &wxCrafterTab::OnWorkspaceChanged));
    
    wxTheApp->Connect(ID_MENU_NEW_FRAME,         wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxCrafterTab::OnNewForm), NULL, this);
    wxTheApp->Connect(ID_MENU_NEW_DIALOG,        wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxCrafterTab::OnNewForm), NULL, this);
    wxTheApp->Connect(ID_MENU_NEW_IMGLIST,       wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxCrafterTab::OnNewForm), NULL, this);
    wxTheApp->Connect(ID_MENU_NEW_PANEL,         wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxCrafterTab::OnNewForm), NULL, this);
    wxTheApp->Connect(ID_MENU_NEW_POPUPWINDOW,   wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxCrafterTab::OnNewForm), NULL, this);
    wxTheApp->Connect(ID_MENU_NEW_WIZARD,        wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(wxCrafterTab::OnNewForm), NULL, this);

}

wxCrafterTab::~wxCrafterTab()
{
}

void wxCrafterTab::OnNewFormUI(wxUpdateUIEvent& event)
{
    wxCrafterTabItemData* itemData = GetSelectionItemData();
    event.Enable( itemData && itemData->GetKind() == wxCrafterTabItemData::kKindFile );
}

void wxCrafterTab::OnNewWxCrafterFile(wxCommandEvent& event)
{
    NewWxCrafterFileDlg dlg(NULL);
    if ( dlg.ShowModal() == wxID_OK ) {
        wxFileName fnResrouceFile( dlg.GetPath() );
        fnResrouceFile.SetExt(wxT("wxcp")); // make sure we got the correct extension
        if ( wxcHelper::CreateEmptyFile( fnResrouceFile ) ) {
            // Add the file to a project
            cbProject* pProj = wxcHelper::GetProject( dlg.GetProjectName() );
            if ( pProj ) {
                // Add the file to the project
                wxcHelper::AddFileToProject(pProj, fnResrouceFile, false);
                BuildTree();
                
            }
        }
    }
}

void wxCrafterTab::OnNewWxCrafterFileUI(wxUpdateUIEvent& event)
{
    wxCrafterTabItemData* itemData = GetSelectionItemData();
    event.Enable( itemData && itemData->GetKind() == wxCrafterTabItemData::kKindProject );
}

void wxCrafterTab::OnWorkspaceChanged(CodeBlocksEvent& event)
{
    event.Skip();
    BuildTree();
}

void wxCrafterTab::DoClear()
{
    m_treeCtrl->DeleteAllItems();
}

wxTreeItemId wxCrafterTab::GetProjectNode(const wxString& name)
{
    wxTreeItemIdValue cookie;
    wxTreeItemId child = m_treeCtrl->GetFirstChild(m_treeCtrl->GetRootItem(), cookie);
    while ( child.IsOk() ) {
        if ( m_treeCtrl->GetItemText(child) == name ) {
            return child;
        }
        child = m_treeCtrl->GetNextChild(m_treeCtrl->GetRootItem(), cookie);
    }
    return wxTreeItemId();
}

wxCrafterTabItemData* wxCrafterTab::GetSelectionItemData()
{
    wxTreeItemId sel = m_treeCtrl->GetSelection();
    if ( !sel.IsOk() ) {
        return NULL;
    }

    return dynamic_cast<wxCrafterTabItemData*>( m_treeCtrl->GetItemData(sel) );
}

void wxCrafterTab::BuildTree()
{
    m_treeCtrl->Freeze();
    m_treeCtrl->DeleteAllItems();
    
    m_treeCtrl->AddRoot(_("Hidden Root"));
    
    // Load all wxcp files
    FilesList allWxcpFiles;
    wxcHelper::GetAllFiles( allWxcpFiles, wxT("wxcp") );
    
    // Now add the file to the tab view
    FilesList::iterator iter = allWxcpFiles.begin();
    for(; iter != allWxcpFiles.end(); ++iter ) {
        wxFileName fnProjectFile( (*iter)->GetParentProject()->GetFilename() );
        wxFileName fnResrouceFile( (*iter)->file );
        wxTreeItemId projectItem = GetProjectNode( (*iter)->GetParentProject()->GetTitle() );
        if ( !projectItem.IsOk() ) {
            // First time, add a project node
            projectItem = m_treeCtrl->AppendItem(m_treeCtrl->GetRootItem(), (*iter)->GetParentProject()->GetTitle(), 1, 1, new wxCrafterTabItemData(wxCrafterTabItemData::kKindProject));
        }
        wxCrafterTabItemData* itemData = new wxCrafterTabItemData(fnResrouceFile.GetFullPath());
        
        fnResrouceFile.MakeRelativeTo( fnProjectFile.GetPath() );
        m_treeCtrl->AppendItem(projectItem, fnResrouceFile.GetFullPath(), 0, 0, itemData);
    }
    m_treeCtrl->ExpandAll();
    m_treeCtrl->Thaw();
}

void wxCrafterTab::OnItemActivated(wxTreeEvent& event)
{
    wxUnusedVar( event );
    wxCrafterTabItemData* itemData = GetSelectionItemData();
    if ( itemData && itemData->GetKind() == wxCrafterTabItemData::kKindFile ) {
        if( m_plugin->EnsureWxCrafterIsRunning() ) {
            m_plugin->GetConnector().LoadFile( itemData->GetFilename() );
        }
    }
}

void wxCrafterTab::OnNewForm(wxCommandEvent& event)
{
    wxUnusedVar( event );
    wxCrafterTabItemData* itemData = GetSelectionItemData();
    if ( !itemData || (itemData->GetKind() != wxCrafterTabItemData::kKindFile) ) {
        return;
    }
    
    // Make sure wxCrafter is up and running
    if ( ! m_plugin->EnsureWxCrafterIsRunning() ) {
        return;
    }
    
    wxFileName wxcpFile = itemData->GetFilename();
    switch( event.GetId() ) {
    case ID_MENU_NEW_DIALOG:
        m_plugin->GetConnector().NewForm(wxcpFile, wxCrafter::kCommandTypeNewDialog);
        break;
    case ID_MENU_NEW_FRAME:
        m_plugin->GetConnector().NewForm(wxcpFile, wxCrafter::kCommandTypeNewFrame);
        break;
    case ID_MENU_NEW_IMGLIST:
        m_plugin->GetConnector().NewForm(wxcpFile, wxCrafter::kCommandTypeNewImageList);
        break;
    case ID_MENU_NEW_PANEL:
        m_plugin->GetConnector().NewForm(wxcpFile, wxCrafter::kCommandTypeNewPanel);
        break;
    case ID_MENU_NEW_POPUPWINDOW:
        m_plugin->GetConnector().NewForm(wxcpFile, wxCrafter::kCommandTypeNewPopupWindow);
        break;
    case ID_MENU_NEW_WIZARD:
        m_plugin->GetConnector().NewForm(wxcpFile, wxCrafter::kCommandTypeNewWizard);
        break;
    default:
        break;
    }
}

void wxCrafterTab::OnItemMenu(wxTreeEvent& event)
{
    m_treeCtrl->SelectItem( event.GetItem() );
    
    wxMenu menu;
    wxMenuItem *menuItem(NULL);
    
    menuItem = new wxMenuItem(&menu, ID_MENU_NEW_FRAME, _("New wxFrame..."), _("New wxFrame..."), wxITEM_NORMAL);
    menuItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("wxframe")));
    menu.Append(menuItem);
    
    menuItem = new wxMenuItem(&menu, ID_MENU_NEW_DIALOG, _("New wxDialog..."), _("New wxDialog..."), wxITEM_NORMAL);
    menuItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("wxdialog")));
    menu.Append(menuItem);
    
    menuItem = new wxMenuItem(&menu, ID_MENU_NEW_PANEL, _("New wxPanel..."), _("New wxPanel..."), wxITEM_NORMAL);
    menuItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("wxpanel")));
    menu.Append(menuItem);
    
    menuItem = new wxMenuItem(&menu, ID_MENU_NEW_WIZARD, _("New wxWizard..."), _("New wxWizard..."), wxITEM_NORMAL);
    menuItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("wxwizard")));
    menu.Append(menuItem);
    
    menu.AppendSeparator();
    menuItem = new wxMenuItem(&menu, ID_MENU_NEW_POPUPWINDOW, _("New wxPopupWindow..."), _("New wxPopupWindow..."), wxITEM_NORMAL);
    menuItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("wxpopupwindow")));
    menu.Append(menuItem);
    
    menuItem = new wxMenuItem(&menu, ID_MENU_NEW_IMGLIST, _("New wxImageList..."), _("New wxImageList..."), wxITEM_NORMAL);
    menuItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("wximglist")));
    menu.Append(menuItem);
    
    m_treeCtrl->PopupMenu( &menu );
}

void wxCrafterTab::OnNewCBProject(wxCommandEvent& event)
{
    NewCodeBlocksProjectWizard wiz(NULL);
    if ( wiz.RunWizard( wiz.GetFirstPage() ) ) {
        // create the project
        ProjectInfo pi = wiz.GetProjectDetails();
        DoCreateProject( pi );
    }
}

void wxCrafterTab::DoCreateProject(const ProjectInfo& projectInfo)
{
    // Create the project folder
    wxFileName::Mkdir( projectInfo.cbp_path.GetPath(), 0777, wxPATH_MKDIR_FULL);
    
    // Get the resources Zip file
    wxString dataFolder = ConfigManager::GetDataFolder();
    wxFileName zipFile(dataFolder, wxT("wxCrafterCB.zip"));
    
    // Extract the files to this folder
    wxString dummy;
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("main.cpp"),                 projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("MainFrame.cpp"),            projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("MainFrame.h"),              projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("wxcrafter.cpp"),            projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("wxcrafter.h"),              projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("wxcrafter.wxcp"),           projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("wxcrafter_bitmaps.cpp"),    projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("wxCrafterCBTemplate.cbp"),  projectInfo.cbp_path.GetPath(), dummy);
    wxcHelper::ExtractFileFromZip(zipFile.GetFullPath(), wxT("resources.rc"),             projectInfo.cbp_path.GetPath(), dummy);

    // Perform a simple string replace on the cbp file
    wxFileName projectFile(projectInfo.cbp_path.GetPath(), wxT("wxCrafterCBTemplate.cbp"));
    wxString fileContent;
    wxcHelper::ReadFileContent( projectFile.GetFullPath(), fileContent );

    // Replace the place holders
    wxString buildType, components;
    if ( projectInfo.wx_build_type.Contains(wxT("Dynamic")) ) {
        buildType = wxT("gcc_dll");

    } else {
        buildType = wxT("gcc_lib");
    }

    for(size_t i=0; i<projectInfo.wx_components.GetCount(); ++i) {
        components << projectInfo.wx_components.Item(i) << wxT(",");
    }

    if ( !components.IsEmpty() ) {
        components.RemoveLast();
    }

    fileContent.Replace(wxT("${PROJECT_NAME}"),  projectInfo.cbp_path.GetName());
    fileContent.Replace(wxT("${WX_COMPONENTS}"), components);

#ifdef __WXMSW__
    fileContent.Replace(wxT("${WX_BUILD_TYPE}"), buildType);
    fileContent.Replace(wxT("${WX_PREFIX}"),     projectInfo.wx_prefix);
#else
    // Remove these placeholders on Linux
    fileContent.Replace(wxT("--prefix=${WX_PREFIX}"),           wxT(""));
    fileContent.Replace(wxT("--wxcfg=${WX_BUILD_TYPE}/mswud"),  wxT(""));
    fileContent.Replace(wxT("--wxcfg=${WX_BUILD_TYPE}/mswu"),   wxT(""));
#endif

    wxcHelper::WriteFileContent( projectFile.GetFullPath(), fileContent );
    
    ::wxRenameFile(projectFile.GetFullPath(), projectInfo.cbp_path.GetFullPath());
    
    // And finally, load the project
    Manager::Get()->GetProjectManager()->LoadProject( projectInfo.cbp_path.GetFullPath() );
}

void wxCrafterTab::OnSettings(wxCommandEvent& event)
{
    wxCrafterSettingsDlg dlg(NULL);
    dlg.ShowModal();
}
