#pragma once
#include "TableRow.h"

class Table
{
private:
    TableRow* rows;
    int size;
    int capacity;

    void erase();
    void copy(const TableRow* rows, int size, int capacity);
    void resize(int newCapacity);

public:
    Table();
    Table(const Table& other);
    Table& operator=(const Table& other);
    ~Table();

    Table(const TableRow* rows, int size);

    Table(Table&& other) noexcept;

    Table& operator=(Table&& other) noexcept;

    TableRow& operator[](int index);

    int rowCount() const;

    void addRow(const TableRow row);

    void addRow(TableRow&& row);

    bool copyRow(int index);

    void removeRow(int index);

    void removeColumn(int index);

    MyString findMin(int index)const;

    MyString findMax(int index)const;

    void copyMin();
    
    void copyMax();

    bool swapRows(int first, int second);

    bool swapCols(int first, int second);

    bool permutate(const MyString& perm);

    void removeDupes();

    friend ostream& operator<<(ostream& os, const Table& table);
};

ostream& operator<<(ostream& os, const Table& table);

bool checkPerm(const MyString& perm);
