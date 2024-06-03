#include "CommandController.h"

int main()
{
	CommandController::Instance()->loadFromFile("test.csv");

	CommandController::Instance()->saveToFile("result.csv");


	CommandController::Release();
	return 0;
}