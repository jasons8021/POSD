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
		if (checkMessage == TEXT_CONNECTION_CANCONNECT)		// 可以跟目標Component進行connect
			return TEXT_CONNECTION_CANCONNECT;
		else												// 與目標Component已經connect 或 connect自己
			return checkMessage;
	}
	else													//	型態不符 或 此Attribute已經與其他Entity相連
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

void NodeAttribute::deleteConnectedComponent( int delComponentID )
{
	Component::deleteConnectedComponent(delComponentID);
	_connectedEntity = false;
}