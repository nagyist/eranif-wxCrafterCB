#ifndef WXCRAFTERCBSETTINGS_H
#define WXCRAFTERCBSETTINGS_H

#include <wx/string.h>
#include "wxcLib/json_node.h"

class wxCrafterCBSettings
{
    wxString m_wxcPath;
    wxRect   m_settingsDialogRect;

public:
    void SetWxcPath(const wxString& wxcPath) {
        this->m_wxcPath = wxcPath;
    }
    const wxString& GetWxcPath() const {
        return m_wxcPath;
    }

    void SetSettingsDialogRect(const wxRect& settingsDialogRect) {
        this->m_settingsDialogRect = settingsDialogRect;
    }
    const wxRect& GetSettingsDialogRect() const {
        return m_settingsDialogRect;
    }
    wxCrafterCBSettings();
    virtual ~wxCrafterCBSettings();

    void ToJSON(JSONElement &json) const;
    void FromJSON(const JSONElement &json);

    /**
     * @brief save the configuration to file
     */
    wxCrafterCBSettings& Load();

    /**
     * @brief save the configuration to the file system
     */
    wxCrafterCBSettings& Save();
};

#endif // WXCRAFTERCBSETTINGS_H
