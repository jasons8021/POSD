#include "ERModel.h"
#include "TextUI.h"
using namespace std;

int main(int argc, char *argv[])
{
	string i;
	TextUI* textUI;
	textUI = new TextUI(new ERModel());
	textUI->displayMenu();
	delete(textUI);

	return 0;
}
