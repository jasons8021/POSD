#include "Component.h"

Component::Component()
{
}

Component::Component(int id, string type, string text)
{
	this->id = id;
	this->type = type;
	this->text = text;
}

Component::~Component()
{

}

int Component::getID()
{
	return this->id;
}

string Component::getType()
{
	return this->type;
}

string Component::getText()
{
	return this->text;
}

void Component::connectTo( Component* targetNode )
{
	// TargetNode isn't in connections
	if(!(searchConnections(targetNode->getID())))
	{
		pushConnection(targetNode);								// Push connected Node into connections
		targetNode->pushConnection(this);
	}
}

bool Component::canConnectTo( Component* TargetNode )
{
	// The method is implemeneted by derived class.
	return false;
}

bool Component::searchConnections( int searchID )
{
	for( int i = 0; i < connections.size(); i++)
	{
		// find!
		if (connections[i]->getID() == searchID)
			return true;
	}
	// Not find!
	return false;
}

void Component::pushConnection( Component* connectedNode)
{
	connections.push_back(connectedNode);
}

