#include "MyString.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

class Command
{
private:
    MyString arguments[10];
    int argCount;

public:
    Command();

    void parse(const MyString& input);

    int getArgCount() const;

    MyString& operator[](int index);
};
