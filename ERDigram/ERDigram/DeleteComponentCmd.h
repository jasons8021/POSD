#ifndef DELETECOMPONENTCMD_H_
#define DELETECOMPONENTCMD_H_

#include "command.h"

class DeleteComponentCmd : public Command
{
public:
	DeleteComponentCmd();
	~DeleteComponentCmd();
	void execute();
	void unexecute();
};

#endif