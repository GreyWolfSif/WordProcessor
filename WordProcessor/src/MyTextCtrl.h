#include "wx/wx.h"

#ifndef MYTEXTCTRL_H
#define MYTEXTCTRL_H
class MyTextCtrl : public wxTextCtrl
{
public:
	void OnChar(wxKeyEvent& event);

};
#endif