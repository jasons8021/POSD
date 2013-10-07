#ifndef ADDCOMPONENTCMD_H_
#define ADDCOMPONENTCMD_H_

#define PARAMETER_NOVALUE -1
#define PARAMETER_PRECOMPONENTID -1
#define PARAMETER_NEXTCOMPONENTID 1

#include "Command.h"
#include "ERModel.h"

class ERModel;

class AddComponentCmd : public Command {
public:
	AddComponentCmd(ERModel* erModel, string, string);
	virtual ~AddComponentCmd();
	void execute();
	void unexecute();
private:
	ERModel* _erModel;
	int _componentID;
	string _type;
	string _text;

};

#endif 
