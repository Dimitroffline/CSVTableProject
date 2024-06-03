#include "CommandController.h"

CommandController* CommandController::pInstance = nullptr;

CommandController* CommandController::Instance()
{
    if (!pInstance)
        pInstance = new CommandController;

    return pInstance;
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
