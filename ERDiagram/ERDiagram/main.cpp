#include "ERModel.h"
#include "TextUI.h"
#include "PresentationModel.h"

using namespace std;

int main(int argc, char *argv[])
{
	ERModel* erModel = new ERModel();
	PresentationModel* presentationModel = new PresentationModel(erModel);
	TextUI* textUI= new TextUI(presentationModel);

	textUI->displayMenu();

	delete textUI;
	delete presentationModel;
	delete erModel;

	return 0;
}
