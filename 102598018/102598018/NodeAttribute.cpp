#include "NodeAttribute.h"

NodeAttribute::NodeAttribute()
{

}

NodeAttribute::NodeAttribute( int id, string text ) : Node()
{
}

NodeAttribute::~NodeAttribute()
{
}

void NodeAttribute::connectTo( Component* targetNode )
{

}

bool NodeAttribute::canConnectTo( Component* targetNode )
{
	return true;
}
