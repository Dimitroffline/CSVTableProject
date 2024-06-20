#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/**
 * \class TableRow
 * \brief Represents a row in the table.
 *
 * The row is represented as a vector of strings.
 */
class TableRow
{
private:
    vector<string> data;

public:
    /**
     * \brief Default constructor, using vector's and string's default constructors.
     */
    TableRow() = default;

    /**
     * \brief Creates a new row with the given data.
     * \param data The data for the row.
     */
    TableRow(vector<string> data);

    /**
     * \brief Overloaded operator[].
     * \param index The index to access.
     * \return Returns a reference to the string in position index if position is in boundaries.
     * 
     * If index is out of boundaries, throws exception.
     */
    string& operator[](int index);

    /**
     * \brief Overloaded const operator[].
     * \param index The index to access.
     * \return Returns a constant reference to the string in position index if position is in boundaries.
     *
     * If index is out of boundaries, throws exception.
     */
    const string& operator[](int index)const;

    /**
     * \brief Removes an element at the given position.
     * \param index The index to remove.
     *
     * If index is out of boundaries, doesn't do anything.
     */
    void removeElement(int index);

    /**
     * \brief Loads a row from a string.
     * \param data Given string to load from.
     *
     * Cuts the string in pieces with delimiter ' ' and loads a row with the given pieces.
     */
    void parseFromFile(string data);

    /**
     * \brief Returns the size of the vector.
     * \return Returns an integer - the size of the vector.
     */
    int getSize()const;

    /**
     * \brief Adds a new element to the end of the row.
     * \param newElement The new element to be added.
     */
    void addElement(string newElement);

    /**
     * \brief Swaps the positions of the elements at index first and second.
     * \param first The index of the first element.
     * \param second The index of the second element.
     * \return TRUE if the indexes are correct and the swap is successful.
     * \return FALSE if the indexes are out of boundaries.
     */
    bool swap(int first, int second);

    /**
     * \brief Resets the row to an empty one.
     */
    void reset();

    /**
     * \brief Checks if the row is empty.
     * \return TRUE if the row is empty.
     * \return FALSE if the row is not empty.
     */
    bool isEmpty()const;

    friend ostream& operator<<(ostream& os, const TableRow& row);
    friend bool operator==(const TableRow& lhs, const TableRow& rhs);
};

/*!
 * \brief Overloading the operator << to print a TableRow.
 * \param os The stream to output to.
 * \param row The given TableRow.
 * \return The output stream by reference.
 */
ostream& operator<<(ostream& os, const TableRow& row);

/*!
 * \brief Overloading the operator == to compare two TableRows.
 * \param lhs First TableRow.
 * \param rhs Second TableRow.
 * \return TRUE if they are identical.
 * \return FALSE if they are not identical.
 */
bool operator==(const TableRow& lhs, const TableRow& rhs);