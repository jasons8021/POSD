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
	//	����addNode��A���o�[�J�i�h��componentID
	if (_componentID == PARAMETER_NOVALUE)						// ���ORedo�����p
		_componentID = _erModel->addNode(_type, _text);
	else														// Redo�����p
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