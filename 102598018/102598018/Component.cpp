#include "Component.h"

Component::Component()
{
// 	this->id = id;
// 	this->type = type;
// 	this->text = text;
}

Component::Component(int id, string type, string text)
{
	this->id = id;
	this->type = type;
	this->text = text;
}

Component::~Component()
{

}

int Component::getID()
{
	return this->id;
}

string Component::getType()
{
	return this->type;
}

string Component::getText()
{
	return this->text;
}

void Component::connectTo( Component* )
{

}

bool Component::canConnectTo( Component* )
{
	return true;
}

