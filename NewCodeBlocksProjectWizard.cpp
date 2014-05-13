#include "NewCodeBlocksProjectWizard.h"

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
    path << m_dirPickerProjectFolder->GetPath() << wxFILE_SEP_PATH << m_textCtrlProjectName->GetValue();
    m_staticTextProjectPathPreview->SetLabel( path );
}
