#include "NodeEntity.h"

NodeEntity::NodeEntity()
{
}

NodeEntity::NodeEntity( int id, string text ) : Node( id, text )
{
}

NodeEntity::~NodeEntity()
{
}

void NodeEntity::connectTo( Component* targetNode )
{

}

bool NodeEntity::canConnectTo( Component* targetNode )
{
	return true;
}