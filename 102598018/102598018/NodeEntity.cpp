#include "NodeEntity.h"

NodeEntity::NodeEntity()
{
}

NodeEntity::NodeEntity( int id, string text )
{
	setID(id);
	setType("E");
	setText(text);
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