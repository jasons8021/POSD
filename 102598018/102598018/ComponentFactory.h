#ifndef COMPONENTFACTORY
#define COMPONENTFACTORY

#include <QtCore/QCoreApplication>
#include <string>
#include "Component.h"
#include "NodeAttribute.h"
#include "NodeEntity.h"
#include "NodeRelationship.h"

class ComponentFactory
{
public:
	ComponentFactory(void);
	~ComponentFactory(void);
	Component* creatComponent(int, string, string);
};

#endif