#include <string>
#include <cstring>
#include <iostream>
#include <stdexcept>

using namespace std;

const int maxArguments = 10;

/**
 * \class Command
 * \brief Represents a user command.
 *
 * The command can have up to maxArguments arguments. The first argument is always the name of the command, and the others are its parameters. The arguments are stored in an array of strings.
 */
class Command
{
private:
    string arguments[maxArguments];
    int argCount;

public:

    /**
     * \brief Creates an empty command.
     */
    Command();

    /**
     * \brief Cuts a line of user input into arguments and updates the arguments array.
     * \param input User input.
     */
    void parse(string input);

    /**
     * \brief Returns the number of arguments stored.
     * \return An integer - the number of arguments stored.
     */
    int getArgCount() const;

    /**
     * \brief Overload of operator[] to access the argument at the given index.
     * \param index
     * 
     * Throws an exception if index is out of boundaries.
     */
    string& operator[](int index);
};
