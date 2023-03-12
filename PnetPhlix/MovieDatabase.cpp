#include "MovieDatabase.h"
#include "Movie.h"
#include <cctype>
#include <string>
#include <vector>
using namespace std;

MovieDatabase::MovieDatabase()
{
    m_called = false;
}

bool MovieDatabase::load(const string& filename)
{
    if (m_called)
        return false;
    ifstream infile(filename);
    if (!infile)
        return false;
    string id, name, year, s;
    float rating;
    int k = 0;
    while (getline(infile, s)){
        if (k > 0)
            getline(infile, s);
        k++;
        id = s;
        for (int i = 0; i < id.size(); i++)
            id[i] = tolower(id[i]);
        getline(infile, s);
        name = s;
        for (int i = 0; i < name.size(); i++)
            name[i] = tolower(name[i]);
        getline(infile, s);
        year = s;
        char c = ',';
        s = "";
        vector<string> directors;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                directors.push_back(s);
                s = "";
            }else if (c != '\n'){
                s += tolower(c);
            }
        }
        directors.push_back(s);
        c = ',';
        s = "";
        vector<string> actors;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                actors.push_back(s);
                s = "";
            }else if (c != '\n'){
                s += tolower(c);
            }
        }
        actors.push_back(s);
        c = ',';
        s = "";
        vector<string> genres;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                genres.push_back(s);
                s = "";
            }else if (c != '\n'){
                s += tolower(c);
            }
        }
        genres.push_back(s);
        infile >> rating;
        infile.ignore(10000, '\n');
        Movie* m = new Movie(id, name, year, directors, actors, genres, rating);
        tmm_movie.insert(id, m);
        for (int i = 0; i < directors.size(); i++)
            tmm_director.insert(directors[i], m);
        for (int i = 0; i < actors.size(); i++){
            tmm_actor.insert(actors[i], m);
        }
        for (int i = 0; i < genres.size(); i++)
            tmm_genre.insert(genres[i], m);
    }
    m_called = true;
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string nId = "";
    for (int i = 0; i < id.size(); i++)
        nId += tolower(id[i]);
    if (!tmm_movie.find(nId).is_valid())
        return nullptr;
    return tmm_movie.find(nId).get_value();
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string nDirector = "";
    for (int i = 0; i < director.size(); i++)
        nDirector += tolower(director[i]);
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = tmm_director.find(nDirector);
    while (it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string nActor = "";
    for (int i = 0; i < actor.size(); i++)
        nActor += tolower(actor[i]);
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = tmm_actor.find(nActor);
    while (it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string nGenre = "";
    for (int i = 0; i < genre.size(); i++)
        nGenre += tolower(genre[i]);
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = tmm_genre.find(nGenre);
    while (it.is_valid()){
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}
