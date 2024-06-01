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

    friend ostream& operator<<(ostream& os, const Table& table);
};

ostream& operator<<(ostream& os, const Table& table);
