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