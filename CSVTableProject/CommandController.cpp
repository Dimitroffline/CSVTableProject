#include "CommandController.h"

CommandController* CommandController::pInstance = nullptr;

CommandController* CommandController::Instance()
{
    if (!pInstance)
        pInstance = new CommandController;

    return pInstance;
}

bool CommandController::execute(string input)
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
        if (argc != 2 && argc != 3)
        {
            cout << "Invalid number of arguments. Usage: open <file path> (<names>) - loads table in <file path>, if <names> is 1, then it treats the first row as names for the columns. By default is 0.\n";
            return 0;
        }

        if (argc == 3)
        {
            int names;

            try
            {
                names = stoi(command[2]);
            }
            catch (const invalid_argument& e)
            {
                cout << "Invalid arguments. Usage: open <file path> (<names>) - loads table in <file path>, if <names> is 1, then it treats the first row as names for the columns. By default is 0.\n";
                return 0;
            }

            if (names != 0 && names != 1)
            {
                cout << "Invalid arguments. Usage: open <file path> (<names>) - loads table in <file path>, if <names> is 1, then it treats the first row as names for the columns. By default is 0.\n";
                return 0;
            }

            if (names == 1)
                hasNames = true;
        }

        Table temp = undoTable;
        undoTable = table;

        if (!loadFromFile(command[1].c_str()))
        {
            cout << "Error reading from file, please try again.\n";
            undoTable = temp;
        }
        else
        {
            cout << "Table loaded.\n";

            if (hasNames)
            {
                if (!table.getSize())
                {
                    cout << "Could not load names.\n";
                    return 0;
                }

                table.addNames();
            }
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
            if (!saveToFile(command[1].c_str()))
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

                try
                {
                    index = stoi(command[2]);
                }
                catch(const invalid_argument& e)
                {
                    cout << "Invalid index, try again please.\n";
                    return 0;
                }

                undoTable = table;
                hasChanged = true;
                table.removeColumn(index);
                cout << "Column removed.\n";
                return 0;

            }
            else if (command[1] == "name")
            {
                if(!hasNames)
                {
                    cout << "Table has no names.\n";
                    return 0;
                }

                undoTable = table;
                hasChanged = true;
                table.removeColumn(command[2]);
                cout << "Column removed.\n";
                return 0;
            }
            else
            {
                cout << "Invalid arguments. Usage: remove index <index> - removes column at <index>; remove name <name> - removes column with <name>; remove dupes - removes duplicate rows.\n";
                return 0;
            }
        }

        if (argc == 2)
        {
            if (command[1] == "dupes")
            {
                undoTable = table;
                hasChanged = true;
                table.removeDupes();
                cout << "Duplicates removed successfully.\n";
                return 0;
            }
            else
            {
                cout << "Invalid arguments. Usage: remove index <index> - removes column at <index>; remove name <name> - removes column with <name>; remove dupes - removes duplicate rows.\n";
                return 0;
            }
        }
    }

    if (command[0] == "undo")
    {
        if (!hasChanged)
        {
            cout << "Cannot undo when no changes were done.\n";
            return 0;
        }

        table = undoTable;
        cout << "Undone.\n";
        return 0;
    }

    if (command[0] == "copy")
    {
        if (argc != 2)
        {
            cout << "Invalid arguments. Usage: copy <index> - copies the row with index <index> at the end of the table; copy min/max - makes a new row with min/max values for each column; copy freq - makes a new row with the most frequent values.\n";
            return 0;
        }

        int index;

        try
        {
            index = stoi(command[1]);
            undoTable = table;
            hasChanged = true;
            table.copyRow(index);
            cout << "Row copied.\n";
            return 0;
        }
        catch (const invalid_argument& e)
        {
            if (command[1] == "max")
            {
                undoTable = table;
                hasChanged = true;
                table.copyMax();
                cout << "Row with max values created.\n";
                return 0;
            }
            else if (command[1] == "min")
            {
                undoTable = table;
                hasChanged = true;
                table.copyMin();
                cout << "Row with min values created.\n";
                return 0;
            }
            else if (command[1] == "freq")
            {
                undoTable = table;
                hasChanged = true;
                table.copyFrequent();
                cout << "Row with most frequent values created.\n";
                return 0;
            }
            else
            {
                cout << "Invalid arguments. Usage: copy <index> - copies the row with index <index> at the end of the table; copy min/max - makes a new row with min/max values for each column; copy freq - makes a new row with the most frequent values.\n";
                return 0;
            }
        }
    }

    if (command[0] == "permutate")
    {
        if (argc != 2)
        {
            cout << "Invalid number of arguments. Usage: permutate <string>, where string is a correct string of a new permutation, no spaces - permutates the columns in the given order.\n";
            return 0;
        }

        Table temp;

        temp = undoTable;

        undoTable = table;

        if (!table.permutate(command[1]))
        {
            cout << "Wrong permutation string, try again.\n";

            undoTable = temp;

            return 0;
        }

        hasChanged = true;
        cout << "Permutated successfully.\n";
        return 0;
    }

    if (command[0] == "filter")
    {
        if (argc != 4)
        {
            cout << "Invalid number of arguments. Usage: filter <index> <sign> <data> - sign can be <, >, <=, >=, ==, !=. Filters the rows which do not meet the condition.\n";
            return 0;
        }

        string sign = command[2];

        if (!(sign == "==") && !(sign == "!=") && !(sign == "<=") && !(sign == "<") && !(sign == ">=") && !(sign == ">"))
        {
            cout << "Invalid sign, sign can be <, >, <=, >=, ==, !=, please try again.\n";
            return 0;
        }

        int index;

        try
        {
            index = stoi(command[1]);
            table.filter(index, sign, command[3]);

            undoTable = table;
            hasChanged = true;
            cout << "Filtered successfully.\n";
            return 0;
        }
        catch (const invalid_argument& e)
        {
            if (!hasNames)
            {
                cout << "Table has no names.\n";
                return 0;
            }

            table.filter(command[1], sign, command[3]);

            undoTable = table;
            hasChanged = true;
            cout << "Filtered successfully.\n";
            return 0;
        }
    }

    if (command[0] == "sort")
    {
        if (argc != 3 && argc != 2)
        {
            cout << "Invalid number of arguments. Usage: sort <index> <order> - sorts the table based on column <index>. <order> is optional, default is ascending order, put 1 for ascending.\n";
            return 0;
        }

        int order = 0;

        if (argc == 3)
        {
            try
            {
                order = stoi(command[2]);
            }
            catch(const invalid_argument& e)
            {
                cout << "Invalid order, must be either 0 for ascending or 1 for descending order, please try again.\n";
                return 0;
            }
        }


        if (order != 0 && order != 1)
        {
            cout << "Invalid order, must be either 0 for ascending or 1 for descending order, please try again.\n";
            return 0;
        }

        bool ord = 0;

        if (order == 1)
            ord = 1;
        
        int index;

        try 
        {
            index = stoi(command[1]);
            table.sort(index, ord);

            undoTable = table;
            hasChanged = true;
            cout << "Table sorted successfully.\n";
            return 0;
        }
        catch (const invalid_argument& e)
        {
            if (!hasNames)
            {
                cout << "Table has no names.\n";
                return 0;
            }

            table.sort(command[1], ord);

            undoTable = table;
            hasChanged = true;
            cout << "Table sorted successfully.\n";
            return 0;
        }
    }

    if (command[0] == "help")
    {
        cout << "================================================================================================\n";
        cout << "\nAvailable functionalities:\n";
        cout << "Command Open: \nopen <file path> (<names>) - loads table in <file path>.\n<names> is optional, by default its false, put 0 for false or 1 for true. When true, treats the first row as names for the columns.\n\n";
        cout << "Command Save: \nsave - saves to the current file; \nsave <file path> - saves to the given path.\n\n";
        cout << "Command Exit: \nexit - exits the program.\n\n";
        cout << "Command Print: \nprint - prints the currently open table.\n\n";
        cout << "Command Remove: \nremove dupes - removes all duplicate rows; \nremove index <index> - removes the column on the given index; \nremove name <name> - removes the column with the given name.\n\n";
        cout << "Command Copy: \ncopy <index> - copies the row with the given index; \ncopy min/max - creates a new row with min/max value in each column; \ncopy freq - creates a new row with the most frequent data for each column.\n\n";
        cout << "Command Permutate: \npermutate <string> - permutates the columns in the given order. \nExample: \n>permutate 132 - changes the order of the second and third columns.\n\n";
        cout << "Command Filter: \nfilter <index> <sign> <data> - filters the rows which do not meet the condition in the given index column;\nfilter <name> <sign> <data> - filters the rows which do not meet the condition in the given name column.\nSign can be <, >, <=, >=, ==, !=.\n\n";
        cout << "Command Sort: \nsort <index> (<order>) - sorts the table based on column at given index;\nsort <name> (<order>) - sorts the table based on column with given name.\n<order> is optional, default is ascending order, put 0 for ascending or 1 for descending.\n\n";
        cout << "Command Undo: \nundo - undoes the last command.\n\n";
        cout << "================================================================================================\n";

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
        return false;
    }

    string line;
    int size = 0;
    table.~Table();
    
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
        row.parseFromFile(line);
        table.addRow(row);
    }

    file.close();
    this->filePath = filePath;

    return true;
}

bool CommandController::saveToFile()
{
    ofstream file(filePath.c_str());

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
    string temp = this->filePath;
    this->filePath = filePath;

    if (!saveToFile())
    {
        this->filePath = temp;
        return false;
    }

    return true;
}
