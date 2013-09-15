#ifndef COMPONENT
#define COMPONENT

#include <QtCore/QCoreApplication>
#include <string>

using namespace std;

class Component
{
public:
	Component();
	~Component();
	int getID();
	string getType();
	string getText();
	void setID(int);
	void setType(string);
	void setText(string);
	void connectTo(Component*);
	bool canConnectTo(Component*);
private:
	int id;
	string type;
	string text;
};

#endif