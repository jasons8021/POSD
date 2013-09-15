#include <QDebug>
#include "ComponentFactory.h"

ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
}

Component* ComponentFactory::creatComponent( int id, string type, string text )
{
	Component* component = NULL;

	if (type == "A")
		component = (Component*) new NodeAttribute(id, text);
	else if (type == "E")
		component = (Component*) new NodeEntity(id, text);
	else if (type == "R")
		component = (Component*) new NodeRelationship(id, text);
	else
		qDebug() << "You may enter some wrong letter, please enter again.";
// 	switch(type)
// 	{
// 		case 0:
// 			component = (Component*) new NodeAttribute();
// 			break;
// 		case 1:
// 			component = (Component*) new NodeEntity();
// 			break;
// 		case 2:
// 			component = (Component*) new NodeRelationship();
// 			break;
// 		default:
// 			qDebug() << "You may enter some wrong letter, please enter again.";
// 			break;
// 	}

	return component;
}
