#pragma once
#include "MyString.h"

class TableRow
{
private:
    MyString* data;
    int size;

    void copy(const MyString* data, int size);
    void erase();

public:

    TableRow();
    TableRow(const TableRow& other);
    TableRow& operator=(const TableRow& other);
    ~TableRow();

    TableRow(const MyString* data, int size);

    TableRow(TableRow&& other) noexcept;

    TableRow& operator=(TableRow&& other) noexcept;

    TableRow(int size);

    MyString& operator[](int index);

    const MyString& operator[](int index)const;

    void removeElement(int index);

    void parseFromFile(const MyString& data, int size);

    int getSize()const;

    bool swapElement(int index, const MyString& newElement);

    bool swap(int first, int second);

    void reset();

    bool isEmpty()const;

    friend ostream& operator<<(ostream& os, const TableRow& row);
};

ostream& operator<<(ostream& os, const TableRow& row);
bool operator==(const TableRow& lhs, const TableRow& rhs);