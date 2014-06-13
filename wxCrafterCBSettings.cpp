#include "wxCrafterCBSettings.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

#ifdef __WXMSW__
#   include <wx/msw/registry.h>
#endif

wxCrafterCBSettings::wxCrafterCBSettings()
{
#ifdef __WXMSW__
    // By default read the value from the registry
    wxString wxcrafterPath;
    wxRegKey key(wxRegKey::HKLM, wxT("Software\\wxCrafter\\settings"));
    if ( key.QueryValue(wxT("InstallPath"), wxcrafterPath) ) {
        wxFileName fnWxc(wxcrafterPath, wxT("wxcrafter.exe"));
        fnWxc.AppendDir(wxT("Standalone"));
        m_wxcPath = fnWxc.GetFullPath();
    }
#else
    m_wxcPath = wxT("/usr/bin/wxcrafter");
#endif
}

wxCrafterCBSettings::~wxCrafterCBSettings()
{
}

void wxCrafterCBSettings::FromJSON(const JSONElement& json)
{
    m_wxcPath = json.namedObject(wxT("m_wxcPath")).toString(m_wxcPath);
    
    // Read the settings dialog size and pos
    wxPoint settingsDlgPt  ( wxDefaultPosition );
    wxSize  settingsDlgSize( wxDefaultSize     );
    
    if ( json.hasNamedObject(wxT("m_settingsDialogRect.size")) && json.hasNamedObject(wxT("m_settingsDialogRect.point")) ) {
        settingsDlgSize = json.namedObject(wxT("m_settingsDialogRect.size")).toSize();
        settingsDlgPt   = json.namedObject(wxT("m_settingsDialogRect.point")).toPoint();
        m_settingsDialogRect = wxRect(settingsDlgPt, settingsDlgSize);
    }
}

void wxCrafterCBSettings::ToJSON(JSONElement &json) const
{
    json.addProperty(wxT("m_wxcPath"),                  m_wxcPath);
    json.addProperty(wxT("m_settingsDialogRect.size"),  m_settingsDialogRect.GetSize());
    json.addProperty(wxT("m_settingsDialogRect.point"), m_settingsDialogRect.GetPosition());
}

wxCrafterCBSettings& wxCrafterCBSettings::Load()
{
    wxFileName fnConfig(wxStandardPaths::Get().GetUserConfigDir(), wxT(".wxCrafterCB.conf"));
    JSONRoot root( fnConfig );
    FromJSON( root.toElement() );
    return *this;
}

wxCrafterCBSettings& wxCrafterCBSettings::Save()
{
    wxFileName fnConfig(wxStandardPaths::Get().GetUserConfigDir(), wxT(".wxCrafterCB.conf"));
    JSONRoot root(cJSON_Object);
    JSONElement json = root.toElement();
    ToJSON( json );
    root.save( fnConfig );
    return *this;
}
