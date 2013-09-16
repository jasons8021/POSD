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

	componentID = 0;
	
	newComponent = componentFactory.creatComponent(++componentID, type, text);
  	components.push_back(newComponent);
	cout << newComponent->getID() << "\n";
	cout << newComponent->getType() << "\n";
	cout << newComponent->getText() << "\n";
}

void ERModel::addConnection( Component firstNode, Component secondNode )
{

}

void ERModel::getTable()
{

}
