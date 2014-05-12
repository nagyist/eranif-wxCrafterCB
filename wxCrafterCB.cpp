#include <wx/app.h>
#include "wxCrafterCB.h"
#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <manager.h>
#include <projectmanager.h>
#include <cbproject.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/ffile.h>
#include "wxcLib/wxcReplyEventData.h"
#include "wxcHelper.h"
#include <algorithm>
#include <editormanager.h>
#include "wxCrafterTab.h"
#include <cbauibook.h>

#ifdef __WXMSW__
#   include <wx/msw/registry.h>
#endif

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
PluginRegistrant<wxCrafterCB> reg(_T("wxCrafterCB"));
}

wxCrafterCB::wxCrafterCB()
    : m_projectTree(NULL)
{
}

wxCrafterCB::~wxCrafterCB()
{
}

void wxCrafterCB::OnAttach()
{
    m_projectTree = Manager::Get()->GetProjectManager()->GetUI().GetTree();
    wxASSERT( m_projectTree );

    m_projectTree->Connect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(wxCrafterCB::OnTreeItemActivated), NULL, this);
    m_connector.Connect(wxcEVT_NET_REPLY_FILES_GENERATED, wxCommandEventHandler(wxCrafterCB::OnFilesGenerated), NULL, this);
    
    // Add our tab to the project view
    wxcImages images;
    cbAuiNotebook* book = Manager::Get()->GetProjectManager()->GetUI().GetNotebook();
    m_tabView = new wxCrafterTab( book, this );
    book->AddPage( m_tabView, _("wxCrafter"), false, images.Bitmap(wxT("m_bmpWxCrafterLogo")));
}

void wxCrafterCB::OnRelease(bool appShutDown)
{
    // Shutdown wxCrafter
    m_connector.Shutdown();
    m_projectTree->Disconnect(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(wxCrafterCB::OnTreeItemActivated), NULL, this);
    m_connector.Disconnect(wxcEVT_NET_REPLY_FILES_GENERATED, wxCommandEventHandler(wxCrafterCB::OnFilesGenerated), NULL, this);
}

void wxCrafterCB::BuildMenu(wxMenuBar* menuBar)
{
    wxUnusedVar( menuBar );
}

void wxCrafterCB::OnTreeItemActivated(wxTreeEvent& event)
{
    // Call skip to make sure that the default operation works, unless
    // we decide otherwise
    event.Skip(true);

    if ( event.GetItem().IsOk() ) {
        ProjectManager *prjManager = Manager::Get()->GetProjectManager();
        FileTreeData* ftd = (FileTreeData*) m_projectTree->GetItemData( event.GetItem() );
        if ( IsWxCrafterFile( ftd ) ) {
            event.Skip(false);
            if ( EnsureWxCrafterIsRunning() ) {
                m_connector.LoadFile( ftd->GetProjectFile()->file.GetFullPath() );
            }
        }
    }
}

void wxCrafterCB::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    wxUnusedVar(type);
    wxUnusedVar(menu);
    wxUnusedVar(data);
}

bool wxCrafterCB::IsWxCrafterFile(const FileTreeData* ftd) const
{
    return ftd &&
           ftd->GetKind() == FileTreeData::ftdkFile &&
           ftd->GetProjectFile() &&
           ftd->GetProjectFile()->file.GetExt() == wxT("wxcp");
}

wxArrayString wxCrafterCB::DoGetAllProjectTargets(cbProject* proj) const
{
    int targetCounts = proj->GetBuildTargetsCount();
    wxArrayString allTargets;
    for(int i=0; i<targetCounts; ++i) {
        allTargets.Add( proj->GetBuildTarget(i)->GetTitle() );
    }
    return allTargets;
}

bool wxCrafterCB::EnsureWxCrafterIsRunning()
{
    if ( m_connector.IsConnected() ) {
        return true;
    }
    
    // Launch wxCrafter process is server mode
    try {
        wxString wxcrafterPath;
#ifdef __WXMSW__
        wxRegKey key(wxRegKey::HKLM, wxT("Software\\wxCrafter\\settings"));
        if ( !key.QueryValue(wxT("InstallPath"), wxcrafterPath) ) {
            // FIXME :: report an error
            return false;
            
        } else {
            wxFileName fnWxc(wxcrafterPath, wxT("wxcrafter.exe"));
            fnWxc.AppendDir(wxT("Standalone"));
            wxcrafterPath = fnWxc.GetFullPath();
        }
        
#elif defined(__WXGTK__)
        wxcrafterPath = wxT("/usr/bin/wxcrafter");
#endif
        m_connector.LaunchAndConnect( wxcrafterPath );

    } catch (clSocketException &e) {
        // FIXME :: report an error
        return false;
    }
    return true;
}

void wxCrafterCB::OnFilesGenerated(wxCommandEvent& event)
{
    wxcReplyEventData *red = dynamic_cast<wxcReplyEventData*>( event.GetClientObject() );
    if ( red ) {
        const wxcReplyEventData::StringVec_t& files = red->GetFiles();
        wxFileName wxcpFile(red->GetWxcpFile());
        
        // Load the project that has this file
        cbProject* proj = Manager::Get()->GetProjectManager()->FindProjectForFile(wxcpFile.GetFullPath(), NULL, false, false);
        if ( proj ) {
            std::vector<wxFileName> vFiles;
            std::for_each( files.begin(), files.end(), StrToFileNameVecFunctor( vFiles ) );
            
            // Add the files
            wxcHelper::AddFilesToProject( proj, vFiles, true );
            
            // Reload externally modified files if needed
            Manager::Get()->GetEditorManager()->CheckForExternallyModifiedFiles();
        }

        // And free the event data
        wxDELETE( red );
    }
}
