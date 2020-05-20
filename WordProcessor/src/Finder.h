#include "wx/wx.h"

#ifndef FINDER_H
#define FINDER_H
class Finder
{
private:
	int* GenerateFailureArray(std::string pattern)
	{
		const int length = pattern.length();
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
	void Search(std::string text, std::string pattern)
	{
		int i = 0;
		int j = 0;

		int* failure = GenerateFailureArray(pattern);

		while (j < text.length())
		{
			if (text[j] == pattern[i])
			{
				i++;
				j++;
			}
			if (i == pattern.length())
			{
				std::cout << "Pattern found from " << (j - i) << " to " << j << '\n';
				i = failure[i - 1];
			}
			else if (j < text.length() && text[j] != pattern[i])
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