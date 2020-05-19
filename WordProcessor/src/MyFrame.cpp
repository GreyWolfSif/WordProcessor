#include "MyFrame.h"
#include "MyTextCtrl.h"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_OPEN, MyFrame::OnOpenFile)
EVT_MENU(wxID_SAVE, MyFrame::OnSave)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_SIZE(MyFrame::OnSize)
EVT_BUTTON(wxID_OK, MyFrame::OnButtonOK)
EVT_CHAR(MyFrame::OnKeyDown)
END_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
    SetSize(wxSize(1000, 1000));
    SetIcon(wxICON(sample));

    wxMenu* fileMenu = new wxMenu();
    wxMenu* helpMenu = new wxMenu();

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    fileMenu->Append(wxID_OPEN, "&Open\tNot Done", "Open file on computer");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl-S", "Save your progress");
    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets!");
    SetStatusText("Some more information...", 1);

    wxButton* button = new wxButton(this, wxID_OK, wxT("OK"), wxPoint(50, 50));

    wxTextCtrl* control = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(900, 900));

}

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
    wxString file = wxFileSelector("Choose a file to open", wxEmptyString, wxEmptyString, "txt");
    if (!file.IsEmpty())
    {
        //TODO
    }
}

// event handlers
void MyFrame::OnSave(wxCommandEvent& event)
{
    //TODO
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    //Destroy the frame
    Close();
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s\nWindows Version: %s"), wxVERSION_STRING, wxPlatformInfo::Get().GetOperatingSystemIdName());
    wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnSize(wxSizeEvent& event)
{

}

void MyFrame::OnButtonOK(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT(":)"));
    wxMessageBox(msg, wxT("The button was clicked!"), wxOK | wxICON_INFORMATION, this);
}

//TODO
void MyFrame::OnKeyDown(wxKeyEvent& event)
{
    if ((event.GetEventType() == wxEVT_KEY_DOWN) && (((wxKeyEvent&)event).GetKeyCode() == WXK_ESCAPE))
    {
        int answer = wxMessageBox("Quit program?", "Confirm", wxYES_NO);
        if (answer == wxYES)
        {
            Close();
        }
    }
    else
    {
        event.Skip();
    }
}