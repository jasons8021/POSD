#include "AddComponentCmd.h"

AddComponentCmd::AddComponentCmd(ERModel* erModel, string type, string text)
{
	_erModel = erModel;
	_type = type;
	_text = text;
	_componentID = PARAMETER_NOVALUE;
}

AddComponentCmd::~AddComponentCmd()
{
}

void AddComponentCmd::execute()
{
	//	執行addNode後，取得加入進去的componentID
	if (_componentID == PARAMETER_NOVALUE)						// 不是Redo的情況
		_componentID = _erModel->addNode(_type, _text);
	else														// Redo的情況
	{	
		_erModel->setComponentID(_erModel->getComponentID() + PARAMETER_NEXTCOMPONENTID);
		_componentID = _erModel->addNode(_componentID, _type, _text);
	}
}

void AddComponentCmd::unexecute()
{
	_erModel->setComponentID(_erModel->getComponentID() + PARAMETER_PRECOMPONENTID);
	_erModel->deleteFunction(_componentID);
}