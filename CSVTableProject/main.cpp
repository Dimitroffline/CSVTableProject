#include "CommandController.h"

int main()
{
	MyString line;

	cout << ">";

	while (getline(cin, line))
	{
		if (CommandController::Instance()->execute(line))
			break;

		cout << ">";
	}

	CommandController::Release();
	return 0;
}