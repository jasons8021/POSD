#include "NodeRelationship.h"

NodeRelationship::NodeRelationship()
{

}

NodeRelationship::NodeRelationship( int id, string text ) : Node( id ,text )
{
}

NodeRelationship::~NodeRelationship()
{
}

void NodeRelationship::connectTo( Component* targetNode )
{

}

bool NodeRelationship::canConnectTo( Component* targetNode )
{
	return true;
}
