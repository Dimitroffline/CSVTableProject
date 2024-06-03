#include "Table.h"

void Table::erase()
{
    delete[] rows;
}

void Table::copy(const TableRow* rows, int size, int capacity)
{
    this->size = size;
    this->capacity = capacity;

    if (capacity == 0)
    {
        rows = nullptr;
        this->size = 0;
        return;
    }

    this->rows = new(nothrow) TableRow[capacity];

    if (!this->rows)
    {
        cout << "Problem with memory!\n";
        return;
    }

    for (int i = 0; i < size; i++)
        this->rows[i] = rows[i];
}

void Table::resize(int newCapacity)
{
    TableRow* newRows = new TableRow[newCapacity];
    for (int i = 0; i < size; ++i)
    {
        newRows[i] = move(rows[i]);
    }
    erase();
    rows = newRows;
    capacity = newCapacity;
}

Table::Table()
{
    rows = nullptr;
    size = 0;
    capacity = 0;
}

Table::Table(const Table& other)
{
    copy(other.rows, other.size, other.capacity);
}

Table::Table(Table&& other) noexcept : rows(other.rows), size(other.size), capacity(other.capacity)
{
    other.rows = nullptr;
    other.size = 0;
    other.capacity = 0;
}

Table& Table::operator=(const Table& other)
{
    if (this != &other)
    {
        erase();
        copy(other.rows, other.size, other.capacity);
    }

    return *this;
}

Table& Table::operator=(Table&& other) noexcept
{
    if (this != &other)
    {
        erase();
        rows = other.rows;
        size = other.size;
        capacity = other.capacity;
        other.rows = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    return *this;
}

Table::~Table()
{
    erase();
}

Table::Table(const TableRow* rows, int size)
{
    copy(rows, size, size);
}

TableRow& Table::operator[](int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    return rows[index];
}

int Table::rowCount() const
{
    return size;
}

void Table::addRow(const TableRow& row)
{
    if (size == capacity)
    {
        resize(capacity == 0 ? 1 : capacity * 2);
    }

    rows[size++] = row;
}

void Table::addRow(TableRow&& row)
{
    if (size == capacity)
    {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    rows[size++] = std::move(row);
}

ostream& operator<<(ostream& os, const Table& table)
{
    for (int i = 0; i < table.size; i++)
    {
        os << table.rows[i];
    }

    return os;
}
