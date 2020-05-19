#include "MyFrame.h"
#include "MyTextCtrl.h"

//The event lookup table
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_OPEN, MyFrame::OnOpenFile)
EVT_MENU(wxID_SAVE, MyFrame::OnSave)
EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_SIZE(MyFrame::OnSize)
EVT_BUTTON(wxID_OK, MyFrame::OnButtonOK)
EVT_CHAR(MyFrame::OnKeyDown)
END_EVENT_TABLE()

void InitializeMenu(wxMenu* fileMenu, wxMenu* helpMenu, wxMenuBar* menuBar)
{
    //appends menu option to the dropdown menu and connects event handlers
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    fileMenu->Append(wxID_OPEN, "&Open\tNot Done", "Open file on computer");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl-S", "Save your progress");
    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");

    //places dropdown menus onto the menu bar
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");
}

void InitializeStatusBar(MyFrame* frame)
{
    frame->CreateStatusBar(2);
    frame->SetStatusText("Welcome to wxWidgets!");
    frame->SetStatusText("Some more information...", 1);
}

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
    SetSize(wxSize(1920, 1080));
    SetIcon(wxICON(sample));

    menuBar = new wxMenuBar();
    fileMenu = new wxMenu();
    helpMenu = new wxMenu();

    InitializeMenu(fileMenu, helpMenu, menuBar);
    SetMenuBar(menuBar);

    InitializeStatusBar(this);

    //initialize widgets
    control = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(500, 400));

}

//EVENT HANDLERS

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, "Open existing file", "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    wxFileInputStream inputStream(openFileDialog.GetPath());
    wxTextInputStream textStream(inputStream, wxT("\x09"), wxConvUTF8);
    if (!inputStream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }
    
    wxString line;
    while (inputStream.IsOk() && !inputStream.Eof())
    {
        line = textStream.ReadLine();
        control->AppendText(line);
        control->AppendText(wxT('\n'));
    }
}

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