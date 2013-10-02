/*
 * History.cpp
 *
 *  Created on: 2009/11/29
 *      Author: zwshen
 */

#include "CommandManager.h"

CommandManager::CommandManager() {
}

CommandManager::~CommandManager() {
	while (!_undoCmds.empty()) {
		Command* c = _undoCmds.top();
		_undoCmds.pop();
		delete c;
	}
	while (!_redoCmds.empty()) {
		Command* c = _redoCmds.top();
		_redoCmds.pop();
		delete c;
	}
}

void CommandManager::execute(Command* cmd) {
	cmd->execute();
	_undoCmds.push(cmd);

	// cleanup and release redoable commands
	while (!_redoCmds.empty()) {
		Command* c = _redoCmds.top();
		_redoCmds.pop();
		delete c;
	}
}

void CommandManager::redo() {
	if (_redoCmds.size() == 0)
		return; // or throw exception

	Command* c = _redoCmds.top();
	_redoCmds.pop();
	c->execute(); // redo the command
	_undoCmds.push(c);
}

void CommandManager::undo() {
	if (_undoCmds.size() == 0)
		return;

	Command* c = _undoCmds.top();
	_undoCmds.pop();
	c->unexecute(); // undo the command
	_redoCmds.push(c);
}