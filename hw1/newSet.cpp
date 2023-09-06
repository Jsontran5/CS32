#include "newSet.h"
//#include <cstdlib>

#include <string>
#include <iostream>

using namespace std;

Set::Set(int value)
{
	if (value < 0)
	{
		exit(1);
	}

	m_size = 0;
	m_newmax = value;
	m_words = new ItemType[m_newmax];
}

Set::Set(const Set& other)
{
	this->m_size = other.m_size;
	this->m_newmax = other.m_newmax;
	this->m_words = new ItemType[m_size];

	for (int i = 0; i < m_size; i++)
	{
		m_words[i] = other.m_words[i];
	}
}

Set& Set::operator=(const Set& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	delete [] m_words;

	this->m_size = rhs.m_size;
	this->m_newmax = rhs.m_newmax;
	this->m_words = new ItemType[m_newmax];

	for (int i = 0; i < m_size; i++)
	{
		m_words[i] = rhs.m_words[i];
	}

	return *this;
}

Set::~Set()
{
	delete[] m_words;
}


bool Set::empty() const
{
	if (m_size == 0)
	{
		return true;
	}

	return false;
}


int Set::size() const
{

	return m_size;
}

bool Set::insert(const ItemType& value)
{
	if (m_size >= m_newmax)
	{
		return false;
	}

	for (int i = 0; i < m_size; i++)
	{
		if (m_words[i] == value)
		{
			return false;
		}
	}

	m_words[m_size] = value;
	m_size++;

	//sort
	for (int i = 0; i < m_size; i++) 
	{
		ItemType temp;
		
		for (int j = i + 1; j < m_size; j++) 
		{
			if (m_words[i] > m_words[j]) 
			{
				temp = m_words[i]; 
				m_words[i] = m_words[j]; 
				m_words[j] = temp; 
			}
		}
	}
	return true;

}

bool Set::erase(const ItemType& value)
{
	bool present = false;
	int loc = 0;

	for (int i = 0; i < m_size; i++)
	{

		if (m_words[i] == value)
		{
			present = true;
			break;
		}
		loc++;
	}

	if (present == true)//check out of bounds
	{
		for (int i = loc; i < m_size; i++)
		{
			if (i != m_size - 1)
			{
				m_words[i] = m_words[i + 1];
			}
		}
		m_size--;
		return true;
	}
	else
	{
		return false;
	}

}

bool Set::contains(const ItemType& value) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_words[i] == value)
		{
			return true;
		}
	}
	return false;
}

bool Set::get(int i, ItemType& value) const
{
	if (0 <= i && i < m_size)
	{
		if (i == 0)
		{
			value = m_words[0];
		}
		else if (i == m_size - 1)
		{
			value = m_words[m_size - 1];
		}
		else
		{
			value = m_words[i];
		}
		return true;
	}
	return false;
}

void Set::swap(Set& other)
{
	int temp = other.m_size;
	other.m_size = this->m_size;
	this->m_size = temp;

	int tempmax = other.m_newmax;
	other.m_newmax = m_newmax;
	this->m_newmax = tempmax;


	ItemType* tempptr = other.m_words;
	other.m_words = this->m_words;
	this->m_words = tempptr;


}