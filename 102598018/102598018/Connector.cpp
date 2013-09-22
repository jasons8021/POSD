#include "Connector.h"


Connector::Connector()
{
}

Connector::Connector( int id, string text ) : Component( id, PARAMETER_CONNECTOR, text )
{

}

Connector::~Connector()
{
}

void Connector::connectTo( Component* )
{
	// Maybe implement in future homework.
}

bool Connector::canConnectTo( Component* )
{
	// Maybe implement in future homework.
	return false;
}

void Connector::setSourceNode( Component* sourceNode )
{
	this->sourceNode = sourceNode;
}

void Connector::setDestinationNode( Component* destinationNode )
{
	this->destinationNode = destinationNode;
}

Component* Connector::getSourceNode()
{
	return this->sourceNode;
}

Component* Connector::getDestinationNode()
{
	return this->destinationNode;
}

void Connector::setConnectedNode( Component* sourceNode, Component* destinationNode )
{
	setSourceNode(sourceNode);
	setDestinationNode(destinationNode);
}
