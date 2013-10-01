#ifndef CONNECTCOMPONENTSCMD_H_
#define CONNECTCOMPONENTSCMD_H_

#include "command.h"

class ConnectComponentsCmd : public Command
{
public:
	ConnectComponentsCmd();
	~ConnectComponentsCmd();
	void execute();
	void unexecute();
};

#endif