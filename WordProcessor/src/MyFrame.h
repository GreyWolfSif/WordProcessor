#ifndef MYFRAME_H
#define MYFRAME_H

#include "wx/wx.h"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"
#include "wx/notebook.h"
#include "ControlParser.h"

#include <iostream>
#include <vector>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

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
    void OnSave(wxCommandEvent& event);
    void OnFind(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSetDarkTheme(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);

private:
    //this class handles events
    DECLARE_EVENT_TABLE()
};
#endif
