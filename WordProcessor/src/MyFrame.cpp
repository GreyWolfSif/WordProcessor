#include "MyFrame.h"

//The event lookup table
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_OPEN, MyFrame::OnOpenFile)
    EVT_MENU(wxID_SAVEAS, MyFrame::OnSaveAs)
    EVT_MENU(wxID_SAVE, MyFrame::OnSave)
    EVT_MENU(wxID_FIND, MyFrame::OnFind)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EDIT, MyFrame::OnSetDarkTheme)
    EVT_SIZE(MyFrame::OnSize)
END_EVENT_TABLE()

void InitializeMenu(wxMenu* fileMenu, wxMenu* helpMenu, wxMenu* settingsMenu, wxMenuBar* menuBar)
{
    //appends menu option to the dropdown menu and connects event handlers
    fileMenu->Append(wxID_OPEN, "&Open\tCtrl-O", "Open file");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_SAVEAS, "&Save As\tCtrl-S", "Save as new project");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl-S", "Save project");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "&Exit", "Exit program");
    
    helpMenu->Append(wxID_FIND, "&Find\tCtrl-F", "Find...");
    helpMenu->Append(wxID_ABOUT, "&Version Info\t", "Show about dialog");

    //places dropdown menus onto the menu bar
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(settingsMenu, "&Settings");
    menuBar->Append(helpMenu, "&Help");
}

void InitializeStatusBar(MyFrame* frame)
{
    frame->CreateStatusBar(2);
    frame->SetStatusText("");
    frame->SetStatusText("", 1);
}

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxPoint(100, 100))
{
    SetIcon(wxICON(sample));

    menuBar = new wxMenuBar();
    fileMenu = new wxMenu();
    helpMenu = new wxMenu();
    settingsMenu = new wxMenu();

    darkThemeMenuItem = new wxMenuItem(settingsMenu, wxID_EDIT, "&Dark Theme\tCtrl-P", "Enable dark theme");
    lightThemeMenuItem = new wxMenuItem(settingsMenu, wxID_EDIT, "&Light Theme\tCtrl-P", "Enable light theme");

    settingsMenu->Append(darkThemeMenuItem);

    InitializeMenu(fileMenu, helpMenu, settingsMenu, menuBar);
    SetMenuBar(menuBar);

    InitializeStatusBar(this);

    control = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 300), wxTE_MULTILINE);

    wxFont font(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
    control->SetFont(font);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(control, 1, wxEXPAND, wxALL);
    
    SetSizer(sizer);
    sizer->Fit(this);
    sizer->SetSizeHints(this);
}

//EVENT HANDLERS

bool fileDialogIsOpen(MyFrame* frame, wxFileDialog& fileDialog)
{
    if (fileDialog.ShowModal() == wxID_CANCEL)
    {
        return false;
    }
    return true;
}

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, "Open File", wxEmptyString, wxEmptyString, "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fileDialogIsOpen(this, fileDialog))
    {
        wxFileInputStream inputStream(fileDialog.GetPath());
        wxTextInputStream textStream(inputStream, wxT("\x09"), wxConvUTF8);
        if (!inputStream.IsOk())
        {
            wxLogError("Cannot open file '%s'.", fileDialog.GetPath());
            return;
        }

        wxString line;
        while (!inputStream.Eof())
        {
            line = textStream.ReadLine();
            control->AppendText(line);
            control->AppendText(wxT('\n'));
        }
    }
}

void MyFrame::OnSaveAs(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, "Save File", wxEmptyString, wxEmptyString, wxEmptyString, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fileDialogIsOpen(this, fileDialog))
    {
        //TODO
    }
}

void MyFrame::OnSave(wxCommandEvent& event)
{
    //TODO
}

void MyFrame::OnFind(wxCommandEvent& event)
{
    wxTextEntryDialog textEntryDialog(this, "Find what: ", "Find");
    textEntryDialog.SetTextValidator(wxFILTER_ALPHA);
    if (textEntryDialog.ShowModal() == wxID_OK)
    {
        wxString text = "";
        for (int i = 0; i < control->GetNumberOfLines(); i++)
        {
            wxString lineText = control->GetLineText(i);
            text.append(lineText);
        }
        ControlParser parser(text);
        wxString pattern = textEntryDialog.GetValue();
        parser.Search(pattern);
    }
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Destroy();
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s\nWindows Version: %s"), wxVERSION_STRING, wxPlatformInfo::Get().GetOperatingSystemIdName());
    wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnSetDarkTheme(wxCommandEvent& event)
{
    if (control->GetBackgroundColour() != *wxBLACK)
    {
        control->SetBackgroundColour(*wxBLACK);
        control->SetForegroundColour(*wxWHITE);
        settingsMenu->Remove(darkThemeMenuItem);
        settingsMenu->Append(lightThemeMenuItem);
    }
    else
    {
        control->SetBackgroundColour(*wxWHITE);
        control->SetForegroundColour(*wxBLACK);
        settingsMenu->Remove(lightThemeMenuItem);
        settingsMenu->Append(darkThemeMenuItem);
    }

    //copy lines from control to a vector
    std::vector<wxString> lines;
    for (int i = 0; i < control->GetNumberOfLines(); i++)
    {
        wxString lineText = control->GetLineText(i);
        lines.push_back(lineText);
    }

    //clear the control's text
    control->Clear();

    //copy lines back from vector to the control
    for (int i = 0; i < lines.size(); i++)
    {
        control->AppendText(lines[i]);
        if (i != lines.size() - 1)
        {
            control->AppendText('\n');
        }
    }
}

//Resizes the frame
void MyFrame::OnSize(wxSizeEvent& event) {}