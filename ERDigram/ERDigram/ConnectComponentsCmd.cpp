#include "ConnectComponentsCmd.h"

ConnectComponentsCmd::ConnectComponentsCmd(ERModel* erModel, int componentID, int sourceNodeID, int destinationNodeID, string text)
{
	_erModel = erModel;
	_componentID = componentID;
	_sourceNodeID = sourceNodeID;
	_destinationNodeID = destinationNodeID;
	_text = text;
}

ConnectComponentsCmd::~ConnectComponentsCmd()
{
	delete _erModel;
}

void ConnectComponentsCmd::execute()
{

}

void ConnectComponentsCmd::unexecute()
{

}
