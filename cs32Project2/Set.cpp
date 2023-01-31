#include "Set.h"
#include <string>
#include <iostream>

using namespace std;

Set::Set()
{
	m_head = new Node;
	m_head->next = m_head;
	m_head->prev = m_head;
	m_tail = m_head;
	m_size = 0;

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
	/*if (contains(value) == true)
	{
		return false;
	}*/

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
	m_tail = p;
	
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


void Set::dump() const
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