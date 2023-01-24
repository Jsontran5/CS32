#include "CardSet.h"
#include "Set.h"
#include <iostream>


CardSet::CardSet()
{
	
}



bool CardSet::add(unsigned long cardnumber)
{
	if (m_cards.insert(cardnumber))
	{
		return true;
	}
	return false;
}

int CardSet::size() const
{
	return m_cards.size();
}

void CardSet::print() const
{
	for (int i = 0; i < this->size(); i++)
	{
		ItemType temp;
		m_cards.get(i, temp);
		std::cout << temp << std::endl;
	}

}