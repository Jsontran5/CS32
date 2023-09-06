#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

#include <iostream>
using namespace std;


bool comp(pair<string, int> left, pair<string, int> right);

Recommender::Recommender(const UserDatabase& user_database,
    const MovieDatabase& movie_database)
{
    m_udb = user_database;

    m_mdb = movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{

    User* u = m_udb.get_user_from_email(user_email);
    
    vector<string> movies = u->get_watch_history();

    unordered_map<string, int> movie_compatibility;

    for (int i = 0; i < movies.size(); i++)
    {
        Movie* current = m_mdb.get_movie_from_id(movies[i]); //get a movie from the watch history

        vector<string> actors = current->get_actors(); //get all its actors
        for (int j = 0; j < actors.size(); j++)
        {
            vector<Movie*> movies_with_matched_actors = m_mdb.get_movies_with_actor(actors[j]); //from the movie database get all movies that had that actor
            for (int k = 0; k < movies_with_matched_actors.size(); k++)
            {
                if (find(movies.begin(), movies.end(), movies_with_matched_actors[k]->get_id()) == movies.end())
                {
                    movie_compatibility[movies_with_matched_actors[k]->get_id()] += 30; //give that movie 30 poitns
                }

            }

        }

         vector<string> directors = current->get_directors();//get all the directors
         for (int j = 0; j < directors.size(); j++) //each director
         {
             vector<Movie*> movies_with_matched_directors = m_mdb.get_movies_with_director(directors[j]); //find movies that matched with it
             for (int k = 0; k < movies_with_matched_directors.size(); k++)
             {
                 if (find(movies.begin(), movies.end(), movies_with_matched_directors[k]->get_id()) == movies.end())
                 {
                     movie_compatibility[movies_with_matched_directors[k]->get_id()] += 20; //give 20 points
                 }
                    
             }

         }

         vector<string> genres = current->get_genres(); //get all the genres
         for (int j = 0; j < genres.size(); j++) //for each genre
         {
             vector<Movie*> movies_with_matched_genres = m_mdb.get_movies_with_genre(genres[j]); //find movies that matched its genre
             for (int k = 0; k < movies_with_matched_genres.size(); k++)
             {
                 if (find(movies.begin(), movies.end(), movies_with_matched_genres[k]->get_id()) == movies.end())
                 {
                     movie_compatibility[movies_with_matched_genres[k]->get_id()] += 1; //add 1 point to the movie
                 }

             }

         }

    }
    
    vector<pair<string, int>> scores(movie_compatibility.begin(), movie_compatibility.end());



    sort(scores.begin(), scores.end(), comp);

    vector<MovieAndRank> final_rankings;
    for (int i = 0; i < movie_count; i++)
    {
        final_rankings.push_back(MovieAndRank(scores[i].first, scores[i].second));
    }



    return final_rankings;  


}

bool comp(pair<string, int> left, pair<string, int> right)
{
    return left.second > right.second;
}