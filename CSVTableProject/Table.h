#pragma once
#include "TableRow.h"

/**
 * \class Table
 * \brief Represents a table.
 *
 * The table is represented by a vector of TableRows. Can have a TableRow of names, which are treated as seperate from the table for methods, that work with the data in the table.
 */
class Table
{
private:
    TableRow names;
    vector<TableRow> rows;

public:
    
    /**
     * \brief Default constructor, creates an empty table.
     */
    Table() = default;

    /**
     * \brief Creates a table with a given vector of rows and names.
     * \param rows
     * \param names
     */
    Table(vector<TableRow> rows, const TableRow& names);

    /**
     * \brief Overloaded operator[].
     * \param index The index to access.
     * \return Returns a reference to the TableRow in position index if position is in boundaries.
     *
     * If index is out of boundaries, throws exception.
     */
    TableRow& operator[](int index);

    /**
     * \brief Overloaded const operator[].
     * \param index The index to access.
     * \return Returns a constant reference to the TableRow in position index if position is in boundaries.
     *
     * If index is out of boundaries, throws exception.
     */
    const TableRow& operator[](int index)const;

    /**
     * \brief Returns the amount of rows in the table.
     * \return Returs an integer - the size of the vector of rows.
     */
    int getSize() const;

    /**
     * \brief Adds a new row to the table.
     * \param row The row to be added.
     */
    void addRow(TableRow row);

    /**
     * \brief Adds a new row to the table, duplicate to the one on the given index.
     * \param index
     * \return TRUE If the idex is inside the boundaries.
     * \return FALSE otherwise.
     */
    bool copyRow(int index);

    /**
     * \brief Removes the row at the given index.
     * \param index
     * 
     * Does nothing if index is out of boundaries.
     */
    void removeRow(int index);

    /**
     * \brief Removes the column at the given index.
     * \param index
     * 
     * Removes the element at the given index for each row in the column. Does nothing if index is more than the columns in the table.
     */
    void removeColumn(int index);

    /**
     * \brief Removes the column with the given name.
     * \param name
     * 
     * Attempts to find the index of the column with the given name. If multiple are found, removes the last one found. If none are found, does nothing.
     */
    void removeColumn(string name);

    /**
     * \brief Finds the minimal element in the column at the given index.
     * \param index
     * \return Empty string if the index is out of boundaries. Otherwise it returns the minimal string in the given column.
     * 
     * Uses a special compare function.
     */
    string findMin(int index)const;

    /**
     * \brief Finds the maximum element in the column at the given index.
     * \param index
     * \return Empty string if the index is out of boundaries. Otherwise it returns the maximum string in the given column.
     *
     * Uses a special compare function.
     */
    string findMax(int index)const;

    /**
     * \brief Creates a new row with the minimal values for each column and adds it to the table.
     * 
     * Uses findMin. Does nothing if the table has no columns.
     */
    void copyMin();
    
    /**
     * \brief Creates a new row with the maximum values for each column and adds it to the table.
     *
     * Uses findMax. Does nothing if the table has no columns.
     */
    void copyMax();

    /**
     * \brief Creates a new row with the most frequent values for each column and adds it to the table.
     *
     * If there are multiple most frequent values, uses the smallest of them according to the compare function.
     */
    void copyFrequent();

    /**
     * \brief Swaps the positions of the given two rows.
     * \param first
     * \param second
     * \return TRUE If the index is inside of the boundaries and the swap is successful.
     * \return FALSE If the index is outside of the boundaries.
     */
    bool swapRows(int first, int second);

    /**
     * \brief Swaps the positions of the given two rows.
     * \param first
     * \param second
     * \return TRUE If the index is inside of the boundaries and the swap is successful.
     * \return FALSE If the index is outside of the boundaries.
     */
    bool swapCols(int first, int second);

    /**
     * \brief Swaps the order of the columns according to the given permutation string.
     * \param perm Permutation string, contains only unique numbers from 1 to the number of rows.
     * \return TRUE If the permutation is successful.
     * \return FALSE If the permutation string is wrong.
     */
    bool permutate(string perm);

    /**
     * \brief Removes the duplicate rows in the table.
     */
    void removeDupes();

    /**
     * \brief Sorts the table based on the column at the given index and the given order.
     * \param index
     * \param order If TRUE, sorts in descending order, if FALSE sorts in ascending order.
     * 
     * If index is outside of boundaries, does nothing.
     */
    void sort(int index, bool order);

    /**
     * \brief Sorts the table based on the column with the given name and the given order.
     * \param name
     * \param order If TRUE, sorts in descending order, if FALSE, sorts in ascending order.
     * 
     * If name is not found, does nothing.
     */
    void sort(string name, bool order);

    /**
     * \brief Removes the rows which do not follow the given condition at the given column index.
     * \param index The index of the column to be checked.
     * \param sign The sign of the comparison. Can be "<", ">", "<=", ">=", "==", "!=".
     * \param other The string to compare to.
     * 
     * Compares every element at the given column in the table with the other element. If the condition does not match, removes the row.
     */
    void filter(int index, string sign, string other);

    /**
     * \brief Removes the rows which do not follow the given condition at the given column index.
     * \param name The name of the column to be checked.
     * \param sign The sign of the comparison. Can be "<", ">", "<=", ">=", "==", "!=".
     * \param other The string to compare to.
     *
     * Compares every element at the given column in the table with the other element. If the condition does not match, removes the row.
     */
    void filter(string name, string sign, string other);

    /**
     * \brief Removes the first row of the table and stores it in names.
     * 
     * If the table is empty or already has names, does nothing.
     */
    void addNames();

    /**
     * \brief Checks if the table is empty.
     * \return TRUE If the table has 0 rows.
     * \return FALSE Otherwise.
     */
    bool isEmpty()const;

    friend ostream& operator<<(ostream& os, const Table& table);
};

/*!
 * \brief Overloading the operator << to print a Table.
 * \param os The stream to output to.
 * \param table The given Table.
 * \return The output stream by reference.
 */
ostream& operator<<(ostream& os, const Table& table);

/*!
 * \brief Checks if a given permutation string is correct.
 * \param perm
 * \return TRUE If the perm string is correct.
 * \return FALSE Otherwise.
 */
bool checkPerm(string perm);

/*!
 * \brief Custom function that compares two strings.
 * \param lhs
 * \param rhs
 * \return Negative value If the left string is smaller than the right.
 * \return 0 If the strings are identical.
 * \return Positive value If the left string is bigger than the right.
 * 
 * Special compare function that handles all the different data types in the table.
 */
int compare(string lhs, string rhs);
