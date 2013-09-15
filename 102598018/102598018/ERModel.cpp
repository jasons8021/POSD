#include "ERModel.h"
#include "qlogging.h"
#include <QDebug>
#include <iostream>

ERModel::ERModel()
{
	componentID = 0;
}

ERModel::~ERModel()
{
	components.clear();
}

void ERModel::addNode( string type, string text )
{
	Component* newComponent;
	ComponentFactory componentFactory;

	//componentID = components.size();
	cout << components.size() << "\n";
	//newComponent = componentFactory.creatComponent(++componentID, type, text);
  	//components.push_back(*newComponent);
}

void ERModel::addConnection( Component firstNode, Component secondNode )
{

}

void ERModel::getTable()
{

}
