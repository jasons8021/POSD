#include "ComponentFactory.h"

#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHIP "R"

ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
}

Component* ComponentFactory::creatComponent( int id, string type, string text )
{
	if (type == PARAMETER_ATTRIBUTE)
		return new NodeAttribute(id, text);
	else if (type == PARAMETER_ENTITY)
		return new NodeEntity(id, text);
	else if (type == PARAMETER_RELATIONSHIP)
		return new NodeRelationship(id, text);
	else
		return new Connector(id, text);
}
