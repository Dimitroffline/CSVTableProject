#pragma once
#include "Command.h"
#include "Table.h"
#include <fstream>
#include <string>

using namespace std;

class CommandController
{
private:
	Table table;
	Table undoTable;
	Command command;
	string filePath;
	bool hasChanged = false;
	bool hasNames = false;
	static CommandController* pInstance;

	CommandController() {}

	bool loadFromFile(const char* filePath);
	bool saveToFile();
	bool saveToFile(const char* filePath);

public:
	CommandController(const CommandController& other) = delete;
	CommandController& operator=(const CommandController& othewr) = delete;

	static CommandController* Instance();

	bool execute(string input);
	
	static void Release();
};