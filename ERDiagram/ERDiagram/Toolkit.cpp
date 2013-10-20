#include "Toolkit.h"


Toolkit::Toolkit()
{
}


Toolkit::~Toolkit()
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
	string::size_type pos = 0;
	vector<string> splitTextSet;
	string token;

	unSplitText += splitChar;
	while ((pos = unSplitText.find(splitChar)) != std::string::npos) {
		token = unSplitText.substr(0, pos);
		splitTextSet.push_back(token);
		unSplitText.erase(0, pos + splitChar.length());
	}

	return splitTextSet;
}
