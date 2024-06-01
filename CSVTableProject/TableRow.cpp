#include "TableRow.h"

void TableRow::copy(const MyString* data, int size)
{
	this->size = size;
	this->data = new(nothrow) MyString[size];

	if (!this->data)
	{
		cout << "Problem with memory!\n";
		return;
	}

	for (int i = 0; i < size; i++)
		this->data[i] = data[i];
}

void TableRow::erase()
{
	delete[] data;
}

TableRow::TableRow()
{
	data = nullptr;
	size = 0;
}

TableRow::TableRow(const TableRow& other)
{
	copy(other.data, other.size);
}

TableRow& TableRow::operator=(const TableRow& other)
{
	if (this != &other)
	{
		erase();
		copy(other.data, other.size);
	}

	return *this;
}

TableRow::~TableRow()
{
	erase();
}

TableRow::TableRow(const MyString* data, int size)
{
	copy(data, size);
}

TableRow::TableRow(TableRow&& other) noexcept : size(other.size), data(other.data)
{
	other.size = 0;
	other.data = nullptr;
}

TableRow& TableRow::operator=(TableRow&& other) noexcept
{
	if (this != &other)
	{
		erase();
		size = other.size;
		data = other.data;
		other.size = 0;
		other.data = nullptr;
	}

	return *this;
}

MyString& TableRow::operator[](int index)
{
	if (index < 0 || index >= size) 
		throw out_of_range("Index out of range");

	return data[index];
}

int TableRow::getSize() const
{
	return size;
}

ostream& operator<<(ostream& os, const TableRow& row)
{
	for (int i = 0; i < row.size; i++)
		os << row.data[i] << " ";

	os << endl;
	
	return os;
}
