#ifndef WXCRAFTERTAB_H
#define WXCRAFTERTAB_H
#include "UI.h"
#include <sdk_events.h>
#include <NewCodeBlocksProjectWizard.h>

class wxCrafterCB;
class wxCrafterTabItemData;
class wxCrafterTab : public wxCrafterTabBase
{
    wxCrafterCB* m_plugin;
    
public:
    enum {
        ID_MENU_NEW_FRAME = 7000,
        ID_MENU_NEW_DIALOG,
        ID_MENU_NEW_PANEL,
        ID_MENU_NEW_WIZARD,
        ID_MENU_NEW_POPUPWINDOW,
        ID_MENU_NEW_IMGLIST
    };
    
private:
    void DoClear();
    void BuildTree();
    void DoCreateProject(const ProjectInfo &projectInfo);
    
    wxTreeItemId GetProjectNode( const wxString &name );
    wxCrafterTabItemData* GetSelectionItemData();

public:
    wxCrafterTab(wxWindow* parent, wxCrafterCB* plugin);
    virtual ~wxCrafterTab();

protected:
    virtual void OnSettings(wxCommandEvent& event);
    virtual void OnNewCBProject(wxCommandEvent& event);
    virtual void OnItemActivated(wxTreeEvent& event);
    virtual void OnItemMenu(wxTreeEvent& event);
    virtual void OnNewWxCrafterFileUI(wxUpdateUIEvent& event);
    virtual void OnNewWxCrafterFile(wxCommandEvent& event);
    virtual void OnNewFormUI(wxUpdateUIEvent& event);
    void OnNewForm(wxCommandEvent &event);
    
    // CodeBlocks events
    void OnWorkspaceChanged(CodeBlocksEvent &event);
};
#endif // WXCRAFTERTAB_H
