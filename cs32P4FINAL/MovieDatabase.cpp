#include "MovieDatabase.h"
#include "Movie.h"
#include "utility.h"
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
        while (d != '\n') //until new line
        {
            string director;
            while (d != ',' && d != '\n') //while it is not at a comma yet add in each character to make up 1 director
            {

                director += d;
                infile.get(d);

            }

            directors.push_back(director); //push the director in

            if (d == ',') //new director
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
            while (a != ',' && a != '\n') //while it is not at a comma yet add in each character to make up 1 actor
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
            while (g != ',' && g != '\n')//while it is not at a comma yet add in each character to make up 1 genre
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

        Movie* current = new Movie(movie_id, movie_name, release_year, directors, actors, genres, rating); //make the new movie
        m_delete.push_back(current); //push into a vector to delete later
        lowerInput(movie_id); //lower everything to make it caseinsensitive
        m_id_to_mov.insert(movie_id, current);

        for (int i = 0; i < actors.size(); i++) //loop through the actor vector
        {
            lowerInput(actors[i]); //lower case
            m_actor_to_mov.insert(actors[i], current); //insert to the treemm
        }


        for (int i = 0; i < directors.size(); i++) //loop through director vector
        {
            lowerInput(directors[i]);
            m_director_to_mov.insert(directors[i], current); //insert to respective tremm
        }

      

        for (int i = 0; i < genres.size(); i++) 
        {
            lowerInput(genres[i]);
            m_genre_to_mov.insert(genres[i], current);
        }


        getline(infile, line);
    }


    return true;
}



Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string lower = id;
    lowerInput(lower);
    TreeMultimap<std::string, Movie*>::Iterator i = m_id_to_mov.find(lower);

    if (!i.is_valid())
    {
        return nullptr;
    }

    Movie* m = i.get_value();
    return m;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string lower = director;
    lowerInput(lower);
    TreeMultimap<std::string, Movie*>::Iterator i = m_director_to_mov.find(lower);

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
    string lower = actor;
    lowerInput(lower);
    TreeMultimap<std::string, Movie*>::Iterator i = m_actor_to_mov.find(lower);

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
    string lower = genre;
    lowerInput(lower);
    TreeMultimap<std::string, Movie*>::Iterator i = m_genre_to_mov.find(lower);

    vector<Movie*> movies;

    while (i.is_valid())
    {
        movies.push_back(i.get_value());
        i.advance();
    }
        

    return movies;
}
