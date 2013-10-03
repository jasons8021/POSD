#include "Toolkit.h"


Toolkit::Toolkit(void)
{
}


Toolkit::~Toolkit(void)
{
}

string Toolkit::integerToString( int targetNum )
{
	stringstream intNum;
	string intToStringNum;

	// int to string
	intNum << targetNum; // int to stringstream
	intNum >> intToStringNum; // stringstream to string

	return intToStringNum;
}

vector<string> Toolkit::splitFunction( string unSplitText, string splitChar )
{
	string::size_type pos;
	vector<string> splitTextSet;

	unSplitText += splitChar;
	int size = unSplitText.size();

	for (int i = 0; i < size; i++)
	{
		pos = unSplitText.find(splitChar,i);
		if (pos < size)
		{
			string tempSubString = unSplitText.substr(i, pos - i);
			splitTextSet.push_back(tempSubString);
			i = pos;
		}
	}
	return splitTextSet;
}
