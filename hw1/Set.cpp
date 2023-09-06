#include "Set.h"
#include <string>
#include <iostream>

using namespace std;

Set::Set()
{
	m_size = 0;
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
	if (m_size >= 160)
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


	for (int i = 0; i < m_size; i++) //loop through the array
	{
		ItemType temp;
		//will prevent out of bounds
		for (int j = i + 1; j < m_size; j++) //will be the value ahead of the array by one.
		{
			if (m_words[i] > m_words[j]) //if the element before is greater
			{
				temp = m_words[i]; //store the greater element
				m_words[i] = m_words[j]; //swap the element to the one next to it because it will be smaller.
				m_words[j] = temp; //the one next to it will now have the greater value
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
	int other_size = other.size();

	if (m_size > other.size())
	{
		for (int i = 0; i < m_size; i++)
		{
			ItemType temp = m_words[i];
			m_words[i] = other.m_words[i];
			other.m_words[i] = temp;
		}
		int temp = other.m_size;
		other.m_size = m_size;
		m_size = temp;

	}
	else
	{
		for (int i = 0; i < other.m_size; i++)
		{
			ItemType temp = other.m_words[i];
			other.m_words[i] = m_words[i];
			m_words[i] = temp;
		}
		int temp = other.m_size;
		other.m_size = m_size;
		m_size = temp;
	}
}