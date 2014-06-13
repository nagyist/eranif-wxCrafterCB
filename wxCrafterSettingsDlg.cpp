#include "wxCrafterSettingsDlg.h"
#include "wxCrafterCBSettings.h"

wxCrafterSettingsDlg::wxCrafterSettingsDlg(wxWindow* parent)
    : wxCrafterSettingsDlgBase(parent)
{
    m_settings.Load();
    m_textCtrlPath->ChangeValue( m_settings.GetWxcPath() );
    
    if ( !m_settings.GetSettingsDialogRect().IsEmpty() ) {
        SetSize( m_settings.GetSettingsDialogRect() );
    }
}

wxCrafterSettingsDlg::~wxCrafterSettingsDlg()
{
    m_settings.SetSettingsDialogRect( GetRect() );
    m_settings.Save();
}

void wxCrafterSettingsDlg::OnOKUI(wxUpdateUIEvent& event)
{
    event.Enable( !m_textCtrlPath->IsEmpty() && wxFileExists( m_textCtrlPath->GetValue() ) );
}

void wxCrafterSettingsDlg::OnOK(wxCommandEvent& event)
{
    wxUnusedVar( event );
    m_settings.SetWxcPath( m_textCtrlPath->GetValue() );
    m_settings.Save();
    EndModal( wxID_OK );
}

void wxCrafterSettingsDlg::OnBrowse(wxCommandEvent& event)
{
    wxString filename = ::wxFileSelector(_("Select wxCrafter executable"));
    if ( !filename.IsEmpty() ) {
        m_textCtrlPath->ChangeValue( filename );
    }
}
