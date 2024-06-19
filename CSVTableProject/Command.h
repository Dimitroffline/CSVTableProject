#include <string>
#include <cstring>
#include <iostream>
#include <stdexcept>

using namespace std;

const int maxArguments = 10;

class Command
{
private:
    string arguments[maxArguments];
    int argCount;

public:
    Command();

    void parse(string input);

    int getArgCount() const;

    string& operator[](int index);
};
