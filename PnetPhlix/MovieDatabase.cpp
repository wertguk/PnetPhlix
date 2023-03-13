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

MovieDatabase::~MovieDatabase()
{
    for (int i = 0; i < m_movies.size(); i++)
        delete m_movies[i];
}

bool MovieDatabase::load(const string& filename)
{
    if (m_called)
        return false;
    ifstream infile(filename);
    if (!infile)
        return false;
    string id, uid, name, uname, year, s;
    float rating;
    int k = 0;
    while (getline(infile, s)){
        if (k > 0)
            getline(infile, s);
        k++;
        id = s;
        uid = s;
        for (int i = 0; i < id.size(); i++)
            id[i] = tolower(id[i]);
        getline(infile, s);
        name = s;
        uname = s;
        for (int i = 0; i < name.size(); i++)
            name[i] = tolower(name[i]);
        getline(infile, s);
        year = s;
        char c = ',';
        s = "";
        string us = "";
        vector<string> directors;
        vector<string> udirectors;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                directors.push_back(s);
                udirectors.push_back(us);
                s = "";
                us = "";
            }else if (c != '\n'){
                us += c;
                s += tolower(c);
            }
        }
        directors.push_back(s);
        udirectors.push_back(us);
        c = ',';
        s = "";
        us = "";
        vector<string> actors;
        vector<string> uactors;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                actors.push_back(s);
                uactors.push_back(us);
                s = "";
                us = "";
            }else if (c != '\n'){
                us += c;
                s += tolower(c);
            }
        }
        actors.push_back(s);
        uactors.push_back(us);
        c = ',';
        s = "";
        us = "";
        vector<string> genres;
        vector<string> ugenres;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                genres.push_back(s);
                ugenres.push_back(us);
                s = "";
                us = "";
            }else if (c != '\n'){
                us += c;
                s += tolower(c);
            }
        }
        genres.push_back(s);
        ugenres.push_back(us);
        infile >> rating;
        infile.ignore(10000, '\n');
        Movie* m = new Movie(uid, uname, year, udirectors, uactors, ugenres, rating);
        m_movies.push_back(m);
        tmm_movie.insert(id, m);
        for (int i = 0; i < directors.size(); i++)
            tmm_director.insert(directors[i], m);
        for (int i = 0; i < actors.size(); i++)
            tmm_actor.insert(actors[i], m);
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
