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
	Component::connectTo(targetNode);
}

bool NodeRelationship::canConnectTo( Component* targetNode )
{
	if (targetNode->getType() == PARAMETER_ENTITY)
		return true;
	else
		return false;
}
