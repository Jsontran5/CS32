#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"
#include "Movie.h"
//class Movie;

class MovieDatabase
{
public:
    MovieDatabase();
    ~MovieDatabase()
    {
        for (int i = 0; i < m_delete.size(); i++)
        {
            delete m_delete[i];
        }
        m_delete.clear();
    }
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

private:

    TreeMultimap<std::string, Movie*> m_id_to_mov;
    TreeMultimap<std::string, Movie*> m_director_to_mov;
    TreeMultimap<std::string, Movie*> m_actor_to_mov;
    TreeMultimap<std::string, Movie*> m_genre_to_mov;

    std::vector<Movie*> m_delete;


};

#endif // MOVIEDATABASE_INCLUDED
