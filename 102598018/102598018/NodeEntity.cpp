#include "NodeEntity.h"

NodeEntity::NodeEntity()
{
}

NodeEntity::NodeEntity( int id, string text ) : Node( id, PARAMETER_ENTITY, text )
{
}

NodeEntity::~NodeEntity()
{
}

void NodeEntity::connectTo( Component* targetNode )
{	
	Component::connectTo(targetNode);
}

string NodeEntity::canConnectTo( Component* targetNode )
{
	string checkMessage = Component::canConnectTo(targetNode);

	if (targetNode->getType() == PARAMETER_RELATIONSHOP || targetNode->getType() == PARAMETER_ATTRIBUTE)
	{
		if (checkMessage == TEXT_CONNECTION_FINISH)		// TargetNode can be connected.
			return TEXT_CONNECTION_FINISH;
		else											// Already connected or connected itself
			return checkMessage;
	}
	else												// Type error
		return TEXT_NODENUMBEGIN + targetNode->getIDString() + TEXT_CONNECTION_NOTCONNECTION + this->getIDString() + TEXT_ENDTEXT;
}

void NodeEntity::setPrimaryKey( int attributeID )
{
	primaryKeys.push_back(attributeID);
}

vector<int> NodeEntity::getPrimaryKey()
{
	return this->primaryKeys;
}
