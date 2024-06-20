#include "CommandController.h"

int main()
{
	string line;

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