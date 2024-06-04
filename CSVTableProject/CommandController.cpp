#include "CommandController.h"

CommandController* CommandController::pInstance = nullptr;

CommandController* CommandController::Instance()
{
    if (!pInstance)
        pInstance = new CommandController;

    return pInstance;
}

bool CommandController::execute(const MyString& input)
{
    command.parse(input);

    int argc = command.getArgCount();

    if (argc == 0)
    {
        cout << "Please enter a valid command.\n";
        return 0;
    }

    if (command[0] == "open")
    {
        if (argc != 2)
        {
            cout << "Invalid number of arguments. Usage: open <file path>\n";
            return 0;
        }

        Table temp = undoTable;
        undoTable = table;

        if (!loadFromFile(command[1].cstr()))
        {
            cout << "Error reading from file, please try again.\n";
            undoTable = temp;
        }
        else
        {
            cout << "Table loaded.\n";
            hasChanged = true;
        }

        return 0;
    }

    if (command[0] == "save")
    {
        if (argc == 1)
        {
            if (filePath == "")
            {
                cout << "No open table found. Please open a table first.\n";
                return 0;
            }

            if (!saveToFile())
            {
                cout << "Error saving to the same file. You can use save <file path> to save to a new one.\n";
                return 0;
            }
            else
            {
                cout << "File saved.\n";
                hasChanged = false;
                return 0;
            }
        }
        else if (argc == 2)
        {
            if (!saveToFile(command[1].cstr()))
            {
                cout << "Could not save to new path, please try again.\n";
            }
            else
            {
                cout << "File saved.\n";
                hasChanged = false;
            }

            return 0;
        }
        else
        {
            cout << "Invalid number of arguments. Usage: save - saves to the current file; save <file path> - saves to the given path.\n";
            return 0;
        }
    }

    if (command[0] == "exit")
    {
        if (hasChanged)
        {
            cout << "There are unsaved changes, do you want to quit regardless?(Y/N): ";
            char ans;
            while(true)
            {
                cin >> ans;
                if (ans == 'Y')
                    return 1;
                else if (ans == 'N')
                    return 0;
                else
                {
                    cout << "\nPlease enter Y or N: ";
                }
            }
        }

        return 1;
    }

    if (command[0] == "print")
    {
        cout << table << '\n';

        return 0;
    }

    if (command[0] == "remove")
    {
        if (argc != 2 && argc != 3)
        {
            cout << "Invalid number of arguments. Usage: remove index <index> - removes column at <index>; remove name <name> - removes column with <name>; remove dupes - removes duplicate rows.\n";
            return 0;
        }

        if (argc == 3)
        {
            if (command[1] == "index")
            {
                int index;

                if (!command[2].toInt(index))
                {
                    cout << "Invalid index, try again please.\n";
                    return 0;
                }
                else
                {
                    undoTable = table;
                    hasChanged = true;
                    table.removeColumn(index);
                    cout << "Column removed.\n";
                    return 0;
                }
            }
        }
    }

    if (command[0] == "undo")
    {
        table = undoTable;
        cout << "Undone.\n";
        return 0;
    }

    cout << "Unknown command. Please use the command \"help\" for further instructions.\n";
    return 0;
}

void CommandController::Release()
{
	delete pInstance;
	pInstance = nullptr;
}

bool CommandController::loadFromFile(const char* filePath)
{
    ifstream file(filePath);

    if (!file.is_open())
    {
        throw runtime_error("Could not open file.");
        return false;
    }

    MyString line;
    int size = 0;
    
    while (getline(file, line))
    {
        if (!size)
        {
            int len = line.size();

            for (int i = 0; i < len; i++)
                if (line[i] == ' ')
                    ++size;

            ++size;
        }

        TableRow row;
        row.parseFromFile(line, size);
        table.addRow(row);
    }

    file.close();
    this->filePath = filePath;

    return true;
}

bool CommandController::saveToFile()
{
    ofstream file(filePath.cstr());

    if (!file.is_open())
    {
        throw runtime_error("Could not open file");
        return false;
    }

    file << table;

    file.close();
    return true;
}

bool CommandController::saveToFile(const char* filePath)
{
    MyString temp = this->filePath;
    this->filePath = filePath;

    if (!saveToFile())
    {
        this->filePath = temp;
        return false;
    }

    return true;
}
