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

    Table(Table&& other) noexcept;

    Table& operator=(const Table& other);

    Table& operator=(Table&& other) noexcept;

    ~Table();

    TableRow& operator[](int index);

    int rowCount() const;
};
