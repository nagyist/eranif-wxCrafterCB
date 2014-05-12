#include "NewWxCrafterFileDlg.h"
#include <manager.h>
#include <projectmanager.h>
#include <cbproject.h>
#include "wxcHelper.h"

NewWxCrafterFileDlg::NewWxCrafterFileDlg(wxWindow* parent)
    : NewWxCrafterFileDlgBase(parent)
{
    ProjectsArray* projects = Manager::Get()->GetProjectManager()->GetProjects();
    for(size_t i=0; i<projects->GetCount(); ++i) {
        cbProject* project = projects->Item(i);
        m_choiceProjects->Append(project->GetTitle());
    }
    m_choiceProjects->SetSelection(0);
    
    // Update the default path
    wxCommandEvent dummy;
    OnProjectSelected( dummy );
    
    Centre();
}

NewWxCrafterFileDlg::~NewWxCrafterFileDlg()
{
}

void NewWxCrafterFileDlg::OnButtonOKUI(wxUpdateUIEvent& event)
{
    event.Enable( !m_filePicker->GetPath().IsEmpty() );
}

void NewWxCrafterFileDlg::OnProjectSelected(wxCommandEvent& event)
{
    wxUnusedVar ( event );
    wxString projectName = m_choiceProjects->GetStringSelection();
    cbProject *selectedProject = wxcHelper::GetProject( projectName );
    if ( selectedProject ) {
        wxFileName fnProject(selectedProject->GetFilename());
        fnProject.SetFullName(wxT("wxcrafter.wxcp"));
        m_filePicker->SetPath( fnProject.GetFullPath() );
    }
}
