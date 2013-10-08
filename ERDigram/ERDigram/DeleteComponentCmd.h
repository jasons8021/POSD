#ifndef DELETECOMPONENTCMD_H_
#define DELETECOMPONENTCMD_H_

#define PARAMETER_NULLSTRING ""
#define PARAMETER_NOVALUE -1
#define PARAMETER_PRECOMPONENTID -1
#define PARAMETER_NEXTCOMPONENTID 1
#define PARAMETER_HAVEPRIMARYKEY 0
#define PARAMETER_ATTRIBUTE "A"
#define PARAMETER_ENTITY "E"
#define PARAMETER_RELATIONSHIP "R"
#define PARAMETER_CONNECTOR "C"

#include "command.h"
#include "ERModel.h"
#include "NodeEntity.h"

class ERModel;

class DeleteComponentCmd : public Command
{
public:
	DeleteComponentCmd(ERModel* erModel, int);
	~DeleteComponentCmd();
	void execute();
	void unexecute();
	void storeInformation();
	void relatedComponentInformation();
	void reBuildRelatedConnection();
private:
	ERModel* _erModel;
	int _componentID;
	int _sourceNodeID;
	int _destinationNodeID;
	string _type;
	string _text;
	vector<vector<int>> _relatedConnections;
	vector<string> _relatedConnectionText;
	vector<int> _primaryKeys;
};

#endif