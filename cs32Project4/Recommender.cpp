#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
    const MovieDatabase& movie_database)
{
    m_udb = user_database;

    m_mdb = movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<Movie> movies = m_udb.get_user_from_email(user_email)





    return vector<MovieAndRank>();  // Replace this line with correct code.
}
