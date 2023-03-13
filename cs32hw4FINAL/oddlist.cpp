

// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOdd(list<int>& li)
{

	for (list<int>::iterator i = li.begin(); i != li.end(); )
	{
		if (*i % 2 == 1)
		{
			 i = li.erase(i);
		}
		else
		{
			i++;
		}
	}


	return;

}
