#include "NodeAttribute.h"

NodeAttribute::NodeAttribute()
{
	_connectedEntity = false;
	_isPrimaryKey = false;
}

NodeAttribute::NodeAttribute( int id, string text ) : Node( id, PARAMETER_ATTRIBUTE, text)
{
	_connectedEntity = false;
	_isPrimaryKey = false;
}

NodeAttribute::~NodeAttribute()
{
	for(int i = 0; i < getConnections().size(); i++)
		delete(getConnections()[i]);
	getConnections().clear();
}

void NodeAttribute::connectTo( Component* targetNode )
{
	Component::connectTo(targetNode);
	_connectedEntity = true;
}

string NodeAttribute::canConnectTo( Component* targetNode )
{
	string checkMessage = Component::canConnectTo(targetNode);

	if (targetNode->getType() == PARAMETER_ENTITY && !(_connectedEntity))
	{
		if (checkMessage == TEXT_CONNECTION_FINISH)		// TargetNode can be connected.
			return TEXT_CONNECTION_FINISH;
		else											// Already connected or connected itself
			return checkMessage;
	}
	else												// Type error
		return TEXT_NODENUMBEGIN + targetNode->getIDString() + TEXT_CONNECTION_NOTCONNECTION + this->getIDString() + TEXT_ENDTEXT;
}

bool NodeAttribute::getIsPrimaryKey()
{
	return this->_isPrimaryKey;
}

void NodeAttribute::setIsPrimaryKey( bool isPK )
{
	this->_isPrimaryKey = isPK;
}