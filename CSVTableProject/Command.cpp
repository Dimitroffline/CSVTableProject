#include "Command.h"

Command::Command()
{
	argCount = 0;
}

void Command::parse(const MyString& input)
{
    argCount = 0;
    MyString currentArg;

    int size = input.size();
    for (int i = 0; i < size; i++)
    {
        char ch = input[i];

        if (ch == ' ')
        {
            if (!currentArg.isEmpty())
            {
                arguments[argCount++] = currentArg;
                currentArg = "";
            }

            if (argCount >= 10) break;
        }
        else
        {
            currentArg = currentArg + ch;
        }
    }

    if (!currentArg.isEmpty() && argCount < 10)
    {
        arguments[argCount++] = currentArg;
    }
}

int Command::getArgCount() const
{
    return argCount;
}

MyString& Command::operator[](int index)
{
    if (index < 0 || index >= argCount)
        throw std::out_of_range("Argument index out of range");

    return arguments[index];
}
