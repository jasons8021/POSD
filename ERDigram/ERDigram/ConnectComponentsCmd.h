#ifndef CONNECTCOMPONENTSCMD_H_
#define CONNECTCOMPONENTSCMD_H_

#include "command.h"
#include "ERModel.h"

class ConnectComponentsCmd : public Command
{
public:
	ConnectComponentsCmd(ERModel* erModel, int, int, int, string);
	virtual ~ConnectComponentsCmd();
	void execute();
	void unexecute();
private:
	ERModel* _erModel;
	int _componentID;
	int _sourceNodeID;
	int _destinationNodeID;
	string _text;
};

#endif