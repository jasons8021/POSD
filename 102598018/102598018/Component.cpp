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

string Component::canConnectTo( Component* targetNode )
{
	if (this->getID() != targetNode->getID())
	{
		if (!(this->searchConnections(targetNode->getID())))
		{
			return TEXT_CONNECTION_FINISH;
		}
		else
			return TEXT_NODENUMBEGIN + this->getIDString() + TEXT_CONNECTION_ALREADYCONNECTION + targetNode->getIDString() + TEXT_ENDTEXT;
	}
	else
		return TEXT_NODENUMBEGIN + this->getIDString() + TEXT_CONNECTION_ITSELFCONNECTION;
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

std::string Component::getIDString()
{
	stringstream intNum;
	string intToStringNum;

	// int to string
	intNum << this->getID(); // int to stringstream
	intNum >> intToStringNum; // stringstream to string

	return intToStringNum;
}

vector<Component*> Component::getConnections()
{
	return this->connections;
}

