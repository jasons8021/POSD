#ifndef COMPONENTFACTORY_H_
#define COMPONENTFACTORY_H_

#include <string>
#include "Component.h"
#include "Connector.h"
#include "NodeAttribute.h"
#include "NodeEntity.h"
#include "NodeRelationship.h"

class ComponentFactory
{
public:
	ComponentFactory();
	virtual ~ComponentFactory();
	Component* creatComponent(int, string, string);
};

#endif