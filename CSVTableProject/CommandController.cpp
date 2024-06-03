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

        if (!loadFromFile(command[1].cstr()))
            cout << "Error reading from file, please try again.\n";
        else
            cout << "Table loaded.\n";

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
        // if changed, save first
        return 1;
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

    int rows = table.rowCount();

    for (int i = 0; i < rows; ++i)
    {
        file << table[i];
        if (i < rows - 1)
            file << '\n';
    }

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
