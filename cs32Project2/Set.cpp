#include "Set.h"
#include <string>
#include <iostream>

using namespace std;

Set::Set()
{
	m_head = new Node;
	m_head->next = m_head;
	m_head->prev = m_head;
	
	m_size = 0;

}

Set::~Set()
{
	if (m_size == 0)
	{
		return;
	}
	if (m_size == 1) 
	{
		delete m_head;
		return;
	}

	Node* p;
	p = m_head->next;

	while (p != m_head)
	{
		Node* n = p->next;
		delete p;
		p = n;
	}

	delete m_head;

}


Set::Set(const Set& other)
{
	m_size = other.m_size;
	
	m_head = new Node;
	m_head->next = m_head;
	m_head->prev = m_head;

	Node* thisNodes = m_head->next;

	Node* otherNodes = other.m_head->next;

	while (otherNodes != other.m_head)
	{
		

		Node* copy = new Node;
		copy->m_item = otherNodes->m_item;
		copy->next = m_head;
		copy->prev = thisNodes;
		thisNodes->next = copy;
		m_head->prev = copy;

		thisNodes = thisNodes->next;
		otherNodes = otherNodes->next;
	}

}

Set& Set::operator=(const Set& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Set temp(rhs);
	swap(temp);
	return *this;

}

bool Set::empty() const
{
	if (m_head->next == m_head && m_head->prev == m_head)
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
	if (contains(value) == true)
	{
		return false;
	}

	Node* last = m_head->next;
	while (last->next != m_head)
	{
		last = last->next;
	}


	Node* p = new Node;
	p->m_item = value;
	last->next = p;
	p->next = m_head;
	p->prev = last;
	m_head->prev = p;
	
	
	m_size += 1;

	Node* sort = m_head->next;
	for (Node* sort = m_head->next; sort != m_head; sort = sort->next)
	{
		if (sort->next != m_head && (sort->m_item > sort->next->m_item))
		{
			ItemType temp = sort->m_item;
			sort->m_item = sort->next->m_item;
			sort->next->m_item = temp;
		}
	}
	return true;
}

bool Set::erase(const ItemType& value)
{
	if (contains(value) == false)
	{
		return false;
	}

	Node* killMe = m_head->next;
	while (killMe != m_head && killMe->m_item != value)
	{
		killMe = killMe->next;
	}

	killMe->prev->next = killMe->next;
	killMe->next->prev = killMe->prev;

	delete killMe;

	m_size--;

	return true;
}


bool Set::contains(const ItemType& value) const
{
	Node* find = m_head->next;

	while (find != m_head && find->m_item != value)
	{
		find = find->next;
	}

	if (find->m_item == value)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Set::get(int pos, ItemType& value) const
{
	if (0 <= pos && pos < m_size)
	{
		Node* greater = m_head->next;
		int count = 0;
		
		while (greater != m_head && count < pos)
		{
			greater = greater->next;
			count++;
		}

		value = greater->m_item;
		return true;

	}

	return false;
}

void Set::swap(Set& other)
{
	
	int tempSize = other.m_size;
	other.m_size = m_size;
	m_size = tempSize;

	Node* tempHead = other.m_head;
	other.m_head = m_head;
	m_head = tempHead;

}

void unite(const Set& s1, const Set& s2, Set& result)
{
	if (&s1 == &s2 || &s2 == &result)
	{
		return;
	}


	Set temp;


	for (int i = 0; i < s1.size(); i++)
	{
		ItemType value;
		s1.get(i, value);
		temp.insert(value);
	}

	for (int i = 0; i < s2.size(); i++)
	{
		ItemType value;
		s2.get(i, value);
		temp.insert(value);
		if (temp.contains(value) == false)
		{
			temp.insert(value);
		}

	}
	result = temp;

}

void butNot(const Set& s1, const Set& s2, Set& result)
{
	if (&s1 == &result)
	{
		return;
	}

	Set temp;

	for (int i = 0; i < s1.size(); i++)
	{
		ItemType value;
		s1.get(i, value);

		if (s2.contains(value) == false)
		{
			temp.insert(value);
		}
	}

	result = temp;

}




void Set::dump() const //delete!!
{
	cerr << "The size of the Set is: " << m_size << endl;
	cerr << "The items in the Set are: " << endl;
	Node* cur = m_head->next;
	for (; cur != m_head; cur = cur->next)
	{
		cerr << cur->m_item << " ";
	}//end for

	cerr << endl;
}//end debugging function