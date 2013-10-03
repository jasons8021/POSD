#include "NodeEntity.h"

NodeEntity::NodeEntity()
{
}

NodeEntity::NodeEntity( int id, string text ) : Node( id, PARAMETER_ENTITY, text )
{
	_foreignKeySet.clear();
}

NodeEntity::~NodeEntity()
{
	_foreignKeySet.clear();
}

void NodeEntity::connectTo( Component* targetNode )
{	
	Component::connectTo(targetNode);
}

string NodeEntity::canConnectTo( Component* targetNode )
{
	string checkMessage = Component::canConnectTo(targetNode);

	if (targetNode->getType() == PARAMETER_RELATIONSHIP || targetNode->getType() == PARAMETER_ATTRIBUTE)
	{
		if (checkMessage == TEXT_CONNECTION_FINISH)		// TargetNode can be connected.
			return TEXT_CONNECTION_FINISH;
		else											// Already connected or connected itself
			return checkMessage;
	}
	else												// Type error
		return TEXT_NODENUMBEGIN + targetNode->getIDString() + TEXT_CONNECTION_NOTCONNECTION + this->getIDString() + TEXT_ENDTEXT;
}

void NodeEntity::setForeignKey( int foreignKeyOfEntityID )
{
	bool checkExist = false;
	//	pair<int,vector<int>> means that (entityID, entityPKset).
	for (int i = 0; i < _foreignKeySet.size(); i++)
	{
		if (_foreignKeySet[i] == foreignKeyOfEntityID)
			checkExist = true;
	}
	if (!checkExist)
		_foreignKeySet.push_back(foreignKeyOfEntityID);
}

vector<int> NodeEntity::getForeignKey()
{
	return this->_foreignKeySet;
}

void NodeEntity::setPrimaryKey( int primaryKeyOfAttributeID )
{
	bool checkExist = false;
	//	Check is existed or not.
	for (int i = 0; i < _primaryKeySet.size(); i++)
	{
		if (_primaryKeySet[i] == primaryKeyOfAttributeID)
			checkExist = true;
	}
	if (!checkExist)
		_primaryKeySet.push_back(primaryKeyOfAttributeID);
}

vector<int> NodeEntity::getPrimaryKey()
{
	return this->_primaryKeySet;
}
