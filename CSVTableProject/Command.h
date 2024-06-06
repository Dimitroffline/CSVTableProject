#include "MyString.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

const int maxArguments = 10;

class Command
{
private:
    MyString arguments[maxArguments];
    int argCount;

public:
    Command();

    void parse(const MyString& input);

    int getArgCount() const;

    MyString& operator[](int index);
};
