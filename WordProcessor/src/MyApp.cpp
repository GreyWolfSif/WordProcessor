#include "MyApp.h"
#include "MyFrame.h"

wxIMPLEMENT_APP(MyApp);
wxDECLARE_APP(MyApp);

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

    MyFrame* frame = new MyFrame(wxT("Notepad"));
    frame->Show(true);

    return true;
}