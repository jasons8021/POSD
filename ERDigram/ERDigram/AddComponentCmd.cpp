/*
 * AddCommand.cpp
 *
 *  Created on: 2009/11/29
 *      Author: zwshen
 */

#include "AddComponentCmd.h"

AddComponentCmd::AddComponentCmd(/*Model* m, Shape::ShapeType type*/) {
// 	model = m;
// 	m_type = type;
}

AddComponentCmd::~AddComponentCmd() {
}

void AddComponentCmd::execute() {
// 	model->addShape(m_type);
}

void AddComponentCmd::unexecute() {
// 	model->deleteLastShape();
}