#pragma once
#include "Command.h"
#include "Table.h"
#include <fstream>
#include <string>

using namespace std;

/**
 * \class CommandController
 * \brief Represents a command controller.
 *
 * Controlls the user inputs, parses them and edits the table. The class is a singleton.
 */
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

	/**
	 * \brief Private default constructor, so it cannot be accessed.
	 */
	CommandController() {}

	/**
	 * \brief Loads a table from the given file path.
	 * \param filePath
	 * \return TRUE If the table loads successfully.
	 * \return FALSE If the file cannot be opened.
	 * 
	 * Saves the file path for future usage.
	 */
	bool loadFromFile(const char* filePath);

	/**
	 * \brief Saves the table to the saved file path.
	 * \return TRUE If the action is successful.
	 * \return FALSE If the file cannot be opened.
	 */
	bool saveToFile();

	/**
	 * \brief Saves the table to the given file path.
	 * \param filePath
	 * \return TRUE If the action is successful.
	 * \return FALSE If the file cannot be opened.
	 */
	bool saveToFile(const char* filePath);

public:

	/**
	 * \brief Copy constructor is deleted.
	 */
	CommandController(const CommandController& other) = delete;

	/**
	 * \brief Copy assignment operator is deleted.
	 */
	CommandController& operator=(const CommandController& othewr) = delete;

	/**
	 * \brief Static function to access the single instance of the class.
	 */
	static CommandController* Instance();

	/**
	 * \brief Executes the given user input.
	 * \param input
	 * 
	 * Takes user input, parses it into a command and executes the command.
	 */
	bool execute(string input);
	
	/**
	 * \brief Releases the memory for the instance of the Singleton class.
	 */
	static void Release();
};