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
	if (type == "A")
		return new NodeAttribute(id, text) ;
	else if (type == "E")
		return new NodeEntity(id, text);
	else if (type == "R")
		return new NodeRelationship(id, text);
	else
		qDebug() << "You may enter some wrong letter, please enter again." << endl;
}
