#include "wx/wx.h"

#ifndef MYFRAME_H
#define MYFRAME_H
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    //events
    void OnOpenFile(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
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
