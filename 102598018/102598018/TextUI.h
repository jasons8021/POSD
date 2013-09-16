#ifndef TEXTUI
#define TEXTUI

// #include <QDebug>
#include <iostream>
#include <string>
#include "ERModel.h"

using namespace std;

class TextUI
{
public:
	TextUI(ERModel*);
	~TextUI();
	void displayMenu();
	void processCommand();
private:
	ERModel* erModel;
};

#endif