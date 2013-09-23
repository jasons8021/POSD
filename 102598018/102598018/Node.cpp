#include "Node.h"


Node::Node() : Component()
{
}

Node::Node( int id, string type, string text ) : Component( id, type, text )
{
}

Node::~Node()
{
}
