#ifndef ERMODEL
#define ERMODEL

#include <QtCore/QCoreApplication>
#include <string>
#include <vector>
#include "Component.h"
#include "ComponentFactory.h"

class ERModel
{
public:
	ERModel();
	~ERModel();
	void addNode(string, string);
	void addConnection(Component, Component);
	void getTable();
private:
	int componentID;
	vector<Component> components;
};

#endif