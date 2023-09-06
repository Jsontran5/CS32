
// Remove the movies in v with a rating below 50 and destroy them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original vector.
void removeBad(vector<Movie*>& v)
{
	vector<Movie*>::iterator i = v.begin();
	while (i != v.end())
	{
		if ((*i)->rating() <50)
		{
			delete* i;
			i = v.erase(i);
		}
		else
		{
			i++;
		}

	}


	return;
}

