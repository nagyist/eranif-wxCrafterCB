#ifndef NEWCODEBLOCKSPROJECTWIZARD_H
#define NEWCODEBLOCKSPROJECTWIZARD_H
#include "UI.h"

struct ProjectInfo
{
    wxFileName    cbp_path;
    wxArrayString wx_components;
    wxString      wx_prefix;
    wxString      wx_build_type;
};

class NewCodeBlocksProjectWizard : public NewCodeBlocksProjectWizardBase
{
public:
    NewCodeBlocksProjectWizard(wxWindow* parent);
    virtual ~NewCodeBlocksProjectWizard();
    ProjectInfo GetProjectDetails() const;
    
protected:
    virtual void OnEnableIfMSW(wxUpdateUIEvent& event);
    virtual void OnPageChanging(wxWizardEvent& event);
    virtual void OnProjectFolderPathChanged(wxFileDirPickerEvent& event);
    virtual void OnProjectNameUpdated(wxCommandEvent& event);
private:
    void DoUpdateProjectPathPreview();
    
};
#endif // NEWCODEBLOCKSPROJECTWIZARD_H
