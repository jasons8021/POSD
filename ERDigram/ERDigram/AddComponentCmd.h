/*
 * AddCommand.h
 *
 *  Created on: 2009/11/29
 *      Author: zwshen
 */

#ifndef ADDCOMPONENTCMD_H_
#define ADDCOMPONENTCMD_H_

#include "Command.h"

class AddComponentCmd : public Command {
public:
	AddComponentCmd(/*Model* m, Shape::ShapeType type*/);
	virtual ~AddComponentCmd();
	void execute();
	void unexecute();
// private:
// 	Model* model;
// 	Shape::ShapeType m_type;

};

#endif 
