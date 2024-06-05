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

TableRow::TableRow(int size)
{
	if (!size)
		return;

	data = new(nothrow) MyString[size];

	if (!data)
	{
		cout << "Problem with memory!\n";
		this->size = 0;
		return;
	}

	this->size = size;
}

MyString& TableRow::operator[](int index)
{
	if (index < 0 || index >= size) 
		throw out_of_range("Index out of range");

	return data[index];
}

const MyString& TableRow::operator[](int index) const
{
	if (index < 0 || index >= size)
		throw out_of_range("Index out of range");

	return data[index];
}

void TableRow::removeElement(int index)
{
	if (index < 0 || index >= size)
		return;

	for (int i = index; i < size - 1; i++)
		data[i] = data[i + 1];

	--size;
}

void TableRow::parseFromFile(const MyString& data, int size)
{
	erase();

	this->data = new(nothrow) MyString[size];

	if (!this->data)
	{
		cout << "Trouble with memory.\n";
		this->size = 0;
		return;
	}

	this->size = size;

	int len = data.size();
	int ind = 0;
	MyString buff("");

	for (int i = 0; i < len; i++)
	{
		if (data[i] == ' ' && !buff.isEmpty())
		{
			this->data[ind++] = buff;
			buff = "";
		}
		else
			buff = buff + data[i];
	}

	if (!buff.isEmpty())
		this->data[ind] = buff;
}

int TableRow::getSize() const
{
	return size;
}

bool TableRow::swapElement(int index, const MyString& newElement)
{
	if (index < 0 || index >= size)
		return 0;

	data[index] = newElement;
	return true;
}

ostream& operator<<(ostream& os, const TableRow& row)
{
	for (int i = 0; i < row.size; i++)
	{
		os << row.data[i];

		if (i < row.size - 1)
			os << ' ';
	}
	
	return os;
}
