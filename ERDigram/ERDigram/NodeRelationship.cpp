#include "NodeRelationship.h"
#include <iostream>


NodeRelationship::NodeRelationship()
{
}

NodeRelationship::NodeRelationship( int id, string text ) : Node( id, PARAMETER_RELATIONSHIP, text )
{
}

NodeRelationship::~NodeRelationship()
{
 	_entityCardinalitySet.clear();
}

void NodeRelationship::connectTo( Component* targetNode )
{
	Component::connectTo(targetNode);
}

string NodeRelationship::canConnectTo( Component* targetNode )
{
	string checkMessage = Component::canConnectTo(targetNode);

	if (targetNode->getType() == PARAMETER_ENTITY && this->getID() != targetNode->getID() && !(this->searchConnections(targetNode->getID())))
	{
		if (checkMessage == TEXT_CONNECTION_CANCONNECT)		// TargetNode can be connected.
			return TEXT_CONNECTION_CANCONNECT;
		else												// Already connected or connected itself
			return checkMessage;
	}
	else													// Type error
		return TEXT_NODENUMBEGIN + targetNode->getIDString() + TEXT_CONNECTION_NOTCONNECTION + this->getIDString() + TEXT_ENDTEXT;
}

void NodeRelationship::setEntityCardinality( pair<int, string> entityCardinality )
{
	this->_entityCardinalitySet.push_back(entityCardinality);
}

vector<pair<int, string>> NodeRelationship::getEntityCardinality()
{
	return this->_entityCardinalitySet;
}

void NodeRelationship::deleteConnectedComponent( int delComponentID )
{
	Component::deleteConnectedComponent(delComponentID);
	deleteEntityCardinality(delComponentID);
}

void NodeRelationship::deleteEntityCardinality( int delComponentID )
{
	for(int i = 0; i < _entityCardinalitySet.size(); i++)
	{
		if (_entityCardinalitySet[i].first == delComponentID)
			_entityCardinalitySet.erase(_entityCardinalitySet.begin()+i);
	}
}
