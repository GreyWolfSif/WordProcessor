#ifndef CONTROLPARSER_H
#define CONTROLPARSER_H

#include "wx/wx.h"

#include <iostream>
#include <string>

class ControlParser
{
private:
	wxString text;

	int* GenerateFailureArray(const wxString& pattern)
	{
		const size_t length = pattern.Length();
		int* failure = new int[length];
		int i = 0;
		int j = 1;
		failure[0] = 0;

		while (j < length)
		{
			if (pattern[i] == pattern[j])
			{
				failure[j] = i + 1;
				i++;
				j++;
			}
			else
			{
				while (i > 0 && pattern[i] != pattern[j])
				{
					i--;
				}
				if (i == 0)
				{
					failure[j] = 0;
					j++;
				}
			}
		}
		return failure;
	}

public:
	ControlParser(const wxString& text) {
		this->text = text;
	};

	void Search(const wxString& pattern)
	{
		int i = 0;
		int j = 0;
		int* failure = GenerateFailureArray(pattern);

		while (j < text.Length())
		{
			if (text[j] == pattern[i])
			{
				i++;
				j++;
			}
			if (i == pattern.Length())
			{
				wxString output = "Pattern found from " + std::to_string(j - i) + " to " + std::to_string(j);
				wxMessageBox(output);
				i = failure[i - 1];
			}
			else if (j < text.Length() && text[j] != pattern[i])
			{
				if (i == 0)
				{
					j++;
				}
				else
				{
					i = failure[i - 1];
				}
			}
		}
	}
};
#endif