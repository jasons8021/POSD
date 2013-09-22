#include "NodeRelationship.h"

NodeRelationship::NodeRelationship()
{
}

NodeRelationship::NodeRelationship( int id, string text ) : Node( id, PARAMETER_RELATIONSHOP, text )
{
}

NodeRelationship::~NodeRelationship()
{
}

void NodeRelationship::connectTo( Component* targetNode )
{
// 	// TargetNode isn't in connections
// 	if( !(searchConnections(targetNode->getID())) )
// 		pushConnection(targetNode);								// Push connected Node into connections
}

bool NodeRelationship::canConnectTo( Component* targetNode )
{
	if (targetNode->getType() == PARAMETER_ENTITY)
		return true;
	else
		return false;
}
