#ifndef NEWCODEBLOCKSPROJECTWIZARD_H
#define NEWCODEBLOCKSPROJECTWIZARD_H
#include "UI.h"

class NewCodeBlocksProjectWizard : public NewCodeBlocksProjectWizardBase
{
public:
    NewCodeBlocksProjectWizard(wxWindow* parent);
    virtual ~NewCodeBlocksProjectWizard();
protected:
    virtual void OnProjectFolderPathChanged(wxFileDirPickerEvent& event);
    virtual void OnProjectNameUpdated(wxCommandEvent& event);
    
private:
    void DoUpdateProjectPathPreview();
    
};
#endif // NEWCODEBLOCKSPROJECTWIZARD_H
