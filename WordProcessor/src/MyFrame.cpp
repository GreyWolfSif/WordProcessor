#include "MyFrame.h"
#include "MyTextCtrl.h"

//The event lookup table
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_OPEN, MyFrame::OnOpenFile)
EVT_MENU(wxID_SAVE, MyFrame::OnSaveAs)
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
    frame->SetStatusText("");
    frame->SetStatusText("", 1);
}

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxPoint(50, 50), wxSize(900, 600))
{
    SetIcon(wxICON(sample));

    menuBar = new wxMenuBar();
    fileMenu = new wxMenu();
    helpMenu = new wxMenu();

    InitializeMenu(fileMenu, helpMenu, menuBar);
    SetMenuBar(menuBar);

    InitializeStatusBar(this);

    control = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 300), wxTE_MULTILINE);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(control, 1, wxEXPAND, wxALL);
    
    SetSizer(sizer);
    sizer->Fit(this);
    sizer->SetSizeHints(this);
}

MyFrame::~MyFrame()
{
    delete[] control;
}

//EVENT HANDLERS

bool fileDialogIsOpen(MyFrame* frame, wxFileDialog* fileDialog)
{
    if (fileDialog->ShowModal() == wxID_CANCEL)
    {
        return false;
    }
    return true;
}

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
    wxFileDialog* fileDialog = new wxFileDialog(this, "Open File", wxEmptyString, wxEmptyString, "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fileDialogIsOpen(this, fileDialog))
    {
        wxFileInputStream inputStream(fileDialog->GetPath());
        wxTextInputStream textStream(inputStream, wxT("\x09"), wxConvUTF8);
        if (!inputStream.IsOk())
        {
            wxLogError("Cannot open file '%s'.", fileDialog->GetPath());
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
}

void MyFrame::OnSaveAs(wxCommandEvent& event)
{
    wxFileDialog* fileDialog = new wxFileDialog(this, "Save File", wxEmptyString, wxEmptyString, wxEmptyString, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fileDialogIsOpen(this, fileDialog))
    {
        //TODO
    }
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    wxExit();
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s\nWindows Version: %s"), wxVERSION_STRING, wxPlatformInfo::Get().GetOperatingSystemIdName());
    wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnResize(wxSizeEvent& event)
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
            wxExit();
        }
    }
    else
    {
        event.Skip();
    }
}