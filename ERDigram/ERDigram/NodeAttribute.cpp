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
		if (checkMessage == TEXT_CONNECTION_CANCONNECT)		// �i�H��ؼ�Component�i��connect
			return TEXT_CONNECTION_CANCONNECT;
		else												// �P�ؼ�Component�w�gconnect �� connect�ۤv
			return checkMessage;
	}
	else													//	���A���� �� ��Attribute�w�g�P��LEntity�۳s
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