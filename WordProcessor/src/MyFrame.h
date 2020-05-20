#include "wx/wx.h"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"

#ifndef MYFRAME_H
#define MYFRAME_H
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    ~MyFrame();
    //menus
    wxMenuBar* menuBar;
    wxMenu* fileMenu;
    wxMenu* helpMenu;
    wxMenu* settingsMenu;
    wxMenuItem* darkThemeMenuItem;
    wxMenuItem* lightThemeMenuItem;

    //widgets
    wxTextCtrl* control;

    //sizer (alignes all the widgets)
    wxBoxSizer* sizer;

    //events
    void OnOpenFile(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnFind(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPersonalize(wxCommandEvent& event);
    void OnResize(wxSizeEvent& event);
    void OnButtonOK(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);

private:
    //this class handles events
    DECLARE_EVENT_TABLE()
};
#endif
