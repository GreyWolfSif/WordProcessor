#include "wx/wx.h"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"

#ifndef MYFRAME_H
#define MYFRAME_H
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    //menus
    wxMenuBar* menuBar;
    wxMenu* fileMenu;
    wxMenu* helpMenu;

    //widgets
    wxButton* button;
    wxTextCtrl* control;

    //events
    void OnOpenFile(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnButtonOK(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);

private:
    //this class handles events
    DECLARE_EVENT_TABLE()
};
#endif
