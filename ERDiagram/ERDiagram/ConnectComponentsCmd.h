#ifndef CONNECTCOMPONENTSCMD_H_
#define CONNECTCOMPONENTSCMD_H_

#define PARAMETER_NOVALUE -1
#define PARAMETER_PRECOMPONENTID -1
#define PARAMETER_NEXTCOMPONENTID 1

#include "command.h"
#include "ERModel.h"

class ERModel;

class ConnectComponentsCmd : public Command
{
public:
	ConnectComponentsCmd(ERModel* erModel, int, int, string);
	virtual ~ConnectComponentsCmd();
	virtual void execute();
	virtual void unexecute();
private:
	ERModel* _erModel;
	int _componentID;
	int _sourceNodeID;
	int _destinationNodeID;
	string _text;
};

#endif