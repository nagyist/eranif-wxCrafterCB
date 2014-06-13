#ifndef WXCRAFTERSETTINGSDLG_H
#define WXCRAFTERSETTINGSDLG_H

#include "UI.h"
#include "wxCrafterCBSettings.h"

class wxCrafterSettingsDlg : public wxCrafterSettingsDlgBase
{
    wxCrafterCBSettings m_settings;
public:
    wxCrafterSettingsDlg(wxWindow* parent);
    virtual ~wxCrafterSettingsDlg();
    
protected:
    virtual void OnBrowse(wxCommandEvent& event);
    virtual void OnOK(wxCommandEvent& event);
    virtual void OnOKUI(wxUpdateUIEvent& event);
};
#endif // WXCRAFTERSETTINGSDLG_H
