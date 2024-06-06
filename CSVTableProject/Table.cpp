#include "Table.h"

bool checkPerm(const MyString& perm)
{
    bool isFound;
    int permSize = perm.size();

    for (int i = 1; i <= permSize; i++)
    {
        isFound = false;

        for (int j = 0; j < permSize; j++)
        {
            if (perm.cstr()[j] - '0' == i)
            {
                isFound = true;
                break;
            }
        }

        if (!isFound)
            return false;
    }

    return true;
}

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
    TableRow* newRows = new(nothrow) TableRow[newCapacity];

    if (!newRows)
    {
        cout << "Problem with memory!\n";
        return;
    }

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

void Table::addRow(const TableRow row)
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

bool Table::copyRow(int index)
{
    if (index < 0 || index >= size)
        return 0;

    addRow(rows[index]);
    return 1;
}

void Table::removeRow(int index)
{
    if (rows == nullptr)
        return;

    if (index < 0 || index >= size)
        return;

    for (int i = index; i < size - 1; i++)
    {
        rows[i] = rows[i + 1];
    }

    --size;
}

void Table::removeColumn(int index)
{
    if (rows == nullptr)
        return;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return;

    for (int i = 0; i < size; i++)
        rows[i].removeElement(index);
}

MyString Table::findMin(int index) const
{
    MyString result;

    if (rows == nullptr)
        return result;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return result;

    result = rows[0][index];

    for (int i = 1; i < size; i++)
    {
        if (compare(result, rows[i][index]) > 0)
        {
            result = rows[i][index];
        }
    }

    return result;
}

MyString Table::findMax(int index) const
{
    MyString result;

    if (rows == nullptr)
        return result;

    int cols = rows[0].getSize();

    if (index < 0 || index >= cols)
        return result;

    result = rows[0][index];

    for (int i = 1; i < size; i++)
    {
        if (compare(result, rows[i][index]) < 0)
        {
            result = rows[i][index];
        }
    }

    return result;
}

void Table::copyMin()
{
    if (!rows)
        return;

    int cols = rows[0].getSize();

    if (!cols)
        return;

    TableRow newRow(cols);

    for (int i = 0; i < cols; i++)
        newRow.swapElement(i, findMin(i));

    addRow(newRow);
}

void Table::copyMax()
{
    if (!rows)
        return;

    int cols = rows[0].getSize();

    if (!cols)
        return;

    TableRow newRow(cols);

    for (int i = 0; i < cols; i++)
        newRow.swapElement(i, findMax(i));

    addRow(newRow);
}

bool Table::swapRows(int first, int second)
{
    if (first < 0 || first >= size)
    {
        return false;
    }

    if (second < 0 || second >= size)
    {
        return false;
    }

    if (first == second)
    {
        return true;
    }

    TableRow temp = rows[first];

    rows[first] = rows[second];
    rows[second] = temp;

    return true;
}

bool Table::swapCols(int first, int second)
{
    for (int i = 0; i < size; i++)
    {
        if (!rows[i].swap(first, second))
            return false;
    }

    return true;
}

bool Table::permutate(const MyString& perm)
{
    if (!rows)
        return true;

    int cols = rows[0].getSize();

    if (!cols)
        return true;

    if (cols != perm.size())
        return false;

    if (!checkPerm(perm))
        return false;

    Table newTable;

    TableRow newRow(cols);

    for (int i = 0; i < size; i++)
        newTable.addRow(newRow);

    for (int i = 0; i < cols; i++)
        for (int j = 0; j < size; j++)
            newTable[j].swapElement(i, rows[j][perm.cstr()[i] - '1']);

    *this = newTable;

    return true;
}

void Table::removeDupes()
{
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (rows[i] == rows[j])
            {
                removeRow(j);
                --j;
            }
}

ostream& operator<<(ostream& os, const Table& table)
{
    for (int i = 0; i < table.size; i++)
    {
        os << table.rows[i];
        
        if (i < table.size - 1)
            os << '\n';
    }

    return os;
}