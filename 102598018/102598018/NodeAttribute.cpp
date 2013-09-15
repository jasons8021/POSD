#include "NodeAttribute.h"

NodeAttribute::NodeAttribute()
{

}

NodeAttribute::NodeAttribute( int id, string text )
{
	setID(id);
	setType("A");
	setText(text);
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
