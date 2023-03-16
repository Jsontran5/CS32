#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>


#include <iostream>
#include <fstream>
using namespace std;

MovieDatabase::MovieDatabase()
{

}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);


    if (!infile)// Did opening the file fail?
    {
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        string movie_id = line;

        getline(infile, line);
        string movie_name = line;


        getline(infile, line);
        string release_year = line;

        vector<string> directors;

        char d;
        infile.get(d);
        while (d != '\n')
        {
            string director;
            while (d != ',' && d != '\n')
            {

                director += d;
                infile.get(d);

            }

            directors.push_back(director);

            if (d == ',')
            {
                infile.get(d);
            }
               

        }

        vector<string> actors;
        char a;
        infile.get(a);
        while (a != '\n')
        {
            string actor;
            while (a != ',' && a != '\n')
            {

                actor += a;
                infile.get(a);

            }
            actors.push_back(actor);

            if (a == ',')
            {
                infile.get(a);
            }
                

        }

        vector<string> genres;
        char g;
        infile.get(g);
        while (g != '\n')
        {
            string genre;
            while (g != ',' && g != '\n')
            {

                genre += g;
                infile.get(g);

            }
            genres.push_back(genre);

            if (g == ',')
            {
                infile.get(g);
            }
                

        }

        float rating;
        infile >> rating;
        infile.ignore(100000, '\n');

        m_id_to_mov.insert(movie_id, new Movie(movie_id, movie_name, release_year, directors, actors, genres, rating));

        for (int i = 0; i < directors.size(); i++)
        {
            m_director_to_mov.insert(directors[i], new Movie(movie_id, movie_name, release_year, directors, actors, genres, rating));
        }

        for (int i = 0; i < actors.size(); i++)
        {
            m_actor_to_mov.insert(actors[i], new Movie(movie_id, movie_name, release_year, directors, actors, genres, rating));
        }

        for (int i = 0; i < genres.size(); i++)
        {
            m_genre_to_mov.insert(genres[i], new Movie(movie_id, movie_name, release_year, directors, actors, genres, rating));
        }


        getline(infile, line);
    }


    return true;
}



Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie*>::Iterator i = m_id_to_mov.find(id);

    if (!i.is_valid())
    {
        return nullptr;
    }

    Movie* m = i.get_value();
    return m;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    TreeMultimap<std::string, Movie*>::Iterator i = m_director_to_mov.find(director);

    vector<Movie*> movies;

    while (i.is_valid())
    {
        movies.push_back(i.get_value());
        i.advance();
    }
        

    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    TreeMultimap<std::string, Movie*>::Iterator i = m_actor_to_mov.find(actor);

    vector<Movie*> movies;

    while (i.is_valid())
    {
        movies.push_back(i.get_value());
        i.advance();
    }
        

    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<std::string, Movie*>::Iterator i = m_genre_to_mov.find(genre);

    vector<Movie*> movies;

    while (i.is_valid())
    {
        movies.push_back(i.get_value());
        i.advance();
    }
        

    return movies;
}
