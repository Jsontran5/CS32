#include "Set.h"

#include <iostream>

using namespace std;

Set::Set()
{
	m_head = new Node; //create dummy node
	m_head->next = m_head; //circular so set the next/prev poitners to itself right now
	m_head->prev = m_head;
	
	m_size = 0;

}

Set::~Set()
{
	if (m_size == 0) //if size is 0 delete the dummy node only
	{
		delete m_head;
		return;
	}
	

	Node* p;
	p = m_head->next; //make a pointer to the first real node

	while (p != m_head)
	{
		Node* n = p->next; //set a pointer to the next node
		delete p; //delete p
		p = n; //set p to the next node
	}

	delete m_head; //finally delete the head

}


Set::Set(const Set& other)
{
	m_size = other.m_size;  //copy the other size
	
	m_head = new Node; //make a new linked list circular with dummy
	m_head->next = m_head;
	m_head->prev = m_head;

	Node* thisNodes = m_head->next; //ptr to the first real node

	Node* otherNodes = other.m_head->next; //ptr to the other ones first real node

	while (otherNodes != other.m_head) //while it didn't loop fully
	{
		

		Node* copy = new Node; //create the new node u want to add in
		copy->m_item = otherNodes->m_item; //set its values
		copy->next = m_head; //since its at the rear, the next will be the head(circular)
		copy->prev = thisNodes; //its previous is the node right before it
		thisNodes->next = copy; //the traversal nodes next is now this new node
		m_head->prev = copy; //update dummy previous ptr

		thisNodes = thisNodes->next; //continue down the lists
		otherNodes = otherNodes->next;
	}

	for (Node* sort = m_head->next; sort != m_head; sort = sort->next) //sort the new list by looping through each node
	{
		if (sort->next != m_head && (sort->m_item > sort->next->m_item)) //check if not head and if the adjacent node is smaller
		{
			ItemType temp = sort->m_item;
			sort->m_item = sort->next->m_item; //swap the items
			sort->next->m_item = temp;
		}
	}


}

Set& Set::operator=(const Set& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Set temp(rhs); //create a temp set for the right hand side
	swap(temp); //swap this set with the temp

	return *this;

}

bool Set::empty() const
{
	if (m_head->next == m_head && m_head->prev == m_head) //if it is the dummy node return true
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
	if (contains(value) == true) //first check if value is in already
	{
		return false;
	}

	Node* last = m_head->next; //traverse to the last node
	while (last->next != m_head)
	{
		last = last->next;
	}


	Node* p = new Node; //make new node
	p->m_item = value;
	last->next = p; //update the former last nodes ptr.
	p->next = m_head; //new nodes next will be the head (last item)
	p->prev = last; //new nodes previous will point to the former last node
	m_head->prev = p; //update dummy node ptrs.
	
	
	m_size += 1; //increase the size


	for (Node* sort = m_head->next; sort != m_head; sort = sort->next) //same sorting algo as in copy contructor
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
	if (contains(value) == false) //make sure its in the lsit first
	{
		return false;
	}

	Node* killMe = m_head->next; //traverse to the target node
	while (killMe != m_head && killMe->m_item != value)
	{
		killMe = killMe->next;
	}

	killMe->prev->next = killMe->next; //update the nodes adjacent to it, by changing ptrs
	killMe->next->prev = killMe->prev;

	delete killMe; //delete the ndoe

	m_size--;
	//decrease the size
	return true;
}


bool Set::contains(const ItemType& value) const
{
	Node* find = m_head->next; //start at the first node

	while (find != m_head && find->m_item != value) //traverse through the list until u reach back to the head or find the value
	{
		find = find->next;
	}

	if (find->m_item == value) //if value is found return true
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
	if (0 <= pos && pos < m_size) //check correct bounds
	{
		Node* greater = m_head->next; //traverse through the list
		int count = 0; //counter to count how many times you looped
		
		while (greater != m_head && count < pos) //loop pos-1 times
		{
			greater = greater->next;
			count++;
		}

		value = greater->m_item; //since it is sorted we know it will be the greater item next.
		return true;

	}

	return false;
}

void Set::swap(Set& other)
{
	
	int tempSize = other.m_size; //swap the sizes
	other.m_size = m_size;
	m_size = tempSize;

	Node* tempHead = other.m_head; //swap the head ptrs
	other.m_head = m_head;
	m_head = tempHead;

}

void unite(const Set& s1, const Set& s2, Set& result)
{
	if (&s1 == &result) //if the first set is same as the result set
	{
		Set temp1 = result;
		for (int i = 0; i < s2.size(); i++) //add in the second set only
		{
			ItemType value;
			s2.get(i, value); //use get function to actually capture each value of the second set
			if (temp1.contains(value) == false) //make sure it is unique and insert it
			{
				temp1.insert(value);
			}
		}

		result = temp1; //update result
		return;
	}
	else if (&s2 == &result) //if the second set is same as the result set
	{
		Set temp2 = result;
		for (int i = 0; i < s1.size(); i++) //basically do the same thing as above
		{
			ItemType value;
			s1.get(i, value);
			if (temp2.contains(value) == false)
			{
				temp2.insert(value);
			}
		}

		result = temp2;
		return;
	}

	Set temp; //if all sets are unique


	for (int i = 0; i < s1.size(); i++) //loops through set 1 and add it to result
	{
		ItemType value;
		s1.get(i, value);
		temp.insert(value);
	}

	for (int i = 0; i < s2.size(); i++) //loop through set 2 but only add the unique items
	{
		ItemType value;
		s2.get(i, value);
		if (temp.contains(value) == false)
		{
			temp.insert(value);
		}

	}
	result = temp;

}

void butNot(const Set& s1, const Set& s2, Set& result)
{
	if (&s1 == &s2) //if set1 and set2 are the same, the resulting set should be empty
	{
		Set temp;
		result = temp;
		return;
	}
	else if (&s1 == &result) //if set1 is the same as result
	{
		for (int i = 0; i < s2.size(); i++)
		{
			ItemType value;
			s2.get(i, value);

			if (result.contains(value) == true) //just check if any values in the second set are in here and erase them
			{
				result.erase(value);
			}
		}
		return;

	}

	Set temp;

	for (int i = 0; i < s1.size(); i++) //loop through first set and insert it to the temp
	{
		ItemType value;
		s1.get(i, value);

		if (s2.contains(value) == false) //make sure the value isnt contained in the second set then insert
		{
			temp.insert(value);
		}
	}

	result = temp; //update the result

}




