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

bool NodeEntity::canConnectTo( Component* targetNode )
{
	if (targetNode->getType() == PARAMETER_RELATIONSHOP || targetNode->getType() == PARAMETER_ATTRIBUTE)
		return true;
	else
		return false;
}