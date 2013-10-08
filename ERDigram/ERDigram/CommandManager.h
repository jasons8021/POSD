/*
 * History.h
 *
 *  Created on: 2009/11/29
 *      Author: zwshen
 */

#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include "Command.h"
#include <stack>

using namespace std;

class CommandManager {
public:
	CommandManager();
	virtual ~CommandManager();
	void execute(Command* c);
	bool redo();
	bool undo();
private:
	stack<Command*> _undoCmds;
	stack<Command*> _redoCmds;
};

#endif 
