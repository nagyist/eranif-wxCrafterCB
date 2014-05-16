#include "NewCodeBlocksProjectWizard.h"
#include <globals.h>
#include <wx/tokenzr.h>

NewCodeBlocksProjectWizard::NewCodeBlocksProjectWizard(wxWindow* parent)
    : NewCodeBlocksProjectWizardBase(parent)
{
}

NewCodeBlocksProjectWizard::~NewCodeBlocksProjectWizard()
{
}

void NewCodeBlocksProjectWizard::OnProjectFolderPathChanged(wxFileDirPickerEvent& event)
{
    DoUpdateProjectPathPreview();
}

void NewCodeBlocksProjectWizard::OnProjectNameUpdated(wxCommandEvent& event)
{
    DoUpdateProjectPathPreview();
}

void NewCodeBlocksProjectWizard::DoUpdateProjectPathPreview()
{
    wxString path;
    path << m_dirPickerProjectFolder->GetPath() << wxFILE_SEP_PATH << m_textCtrlProjectName->GetValue() << wxFILE_SEP_PATH << m_textCtrlProjectName->GetValue() << wxT(".cbp");
    m_staticTextProjectPathPreview->SetLabel( path );
}

void NewCodeBlocksProjectWizard::OnPageChanging(wxWizardEvent& event)
{
    if ( event.GetDirection() ) {
        if ( event.GetPage() == m_pages.at(0) ) {
            // Moving from page1 -> page2
            if ( m_dirPickerProjectFolder->GetPath().IsEmpty() || m_textCtrlProjectName->IsEmpty() ) {
                ::cbMessageBox(_("Make sure you properly selected project name and location"), wxT("wxCrafter"), wxOK|wxICON_WARNING);
                event.Veto();
                return;
            }
        } 
#ifdef __WXMSW__
        else if ( event.GetPage() == m_pages.at(1) ) {
            if ( m_dirPickerWxPath->GetPath().IsEmpty() || !wxFileName::DirExists( m_dirPickerWxPath->GetPath()) ) {
                ::cbMessageBox(_("Please select a valid wxWidgets installation folder"), wxT("wxCrafter"), wxOK|wxICON_WARNING);
                event.Veto();
                return;
            }
        }
#endif
    }
}

ProjectInfo NewCodeBlocksProjectWizard::GetProjectDetails() const
{
    ProjectInfo pi;
    pi.cbp_path = m_staticTextProjectPathPreview->GetLabel();
    pi.wx_components = ::wxStringTokenize(m_textCtrlComponents->GetValue(), wxT("\n"), wxTOKEN_STRTOK);
    pi.wx_build_type = m_choiceBuildType->GetStringSelection();
    pi.wx_prefix = m_dirPickerWxPath->GetPath();
    return pi;
}

void NewCodeBlocksProjectWizard::OnEnableIfMSW(wxUpdateUIEvent& event)
{
#ifdef __WXMSW__
    event.Enable( true );
#else
    event.Enable( false );
#endif
}
