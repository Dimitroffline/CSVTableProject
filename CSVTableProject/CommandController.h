#pragma once
#include "Command.h"
#include "Table.h"
#include "fstream"

class CommandController
{
private:
	Table table;
	Command command;
	MyString filePath;
	static CommandController* pInstance;

	CommandController() {}

public:
	CommandController(const CommandController& other) = delete;
	CommandController& operator=(const CommandController& othewr) = delete;

	static CommandController* Instance();
	
	static void Release();

	bool loadFromFile(const char* filePath);
	bool saveToFile();
	bool saveToFile(const char* filePath);
};