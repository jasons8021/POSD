#ifndef DELETECOMPONENTCMD_H_
#define DELETECOMPONENTCMD_H_

#include "command.h"
#include "ERModel.h"

class DeleteComponentCmd : public Command
{
public:
	DeleteComponentCmd();
	~DeleteComponentCmd();
	void execute();
	void unexecute();
private:
	ERModel* _erModel;
};

#endif