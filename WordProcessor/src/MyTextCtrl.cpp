#include "MyTextCtrl.h"

void MyTextCtrl::OnChar(wxKeyEvent& event)
{
	if (wxIsalpha(event.GetKeyCode()))
	{
		event.Skip();
		wxMessageBox(wxT("Hello!"));
	}
	else
	{
		wxBell();
	}
}