#ifndef COMPONENT
#define COMPONENT

#include <vector>
#include <string>

using namespace std;

class Component
{
public:
	Component();
	Component(int, string, string);
	~Component();
	int getID();
	string getType();
	string getText();
	bool searchConnections(int);
	void pushConnection(Component*);
	void connectTo(Component*);
	virtual bool canConnectTo(Component*);
private:
	int id;
	string type;
	string text;
	vector<Component*> connections;
};

#endif