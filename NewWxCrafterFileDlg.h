#ifndef NEWWXCRAFTERFILEDLG_H
#define NEWWXCRAFTERFILEDLG_H
#include "UI.h"

class NewWxCrafterFileDlg : public NewWxCrafterFileDlgBase
{
public:
    NewWxCrafterFileDlg(wxWindow* parent);
    virtual ~NewWxCrafterFileDlg();
    
    wxString GetPath() const {
        return m_filePicker->GetPath();
    }
    
    wxString GetProjectName() const {
        return m_choiceProjects->GetStringSelection();
    }
    
protected:
    virtual void OnProjectSelected(wxCommandEvent& event);
    virtual void OnButtonOKUI(wxUpdateUIEvent& event);
};
#endif // NEWWXCRAFTERFILEDLG_H
