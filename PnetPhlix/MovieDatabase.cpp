#include "MovieDatabase.h"
#include "Movie.h"

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
        getline(infile, s);
        id = s;
        getline(infile, s);
        name = s;
        getline(infile, s);
        year = s;
        char c = ',';
        string s = "";
        vector<string> directors;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                s = "";
                directors.push_back(s);
            }else{
                s += c;
            }
        }
        c = ',';
        s = "";
        vector<string> actors;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                s = "";
                actors.push_back(s);
            }else{
                s += c;
            }
        }
        c = ',';
        s = "";
        vector<string> genres;
        while (c != '\n'){
            infile.get(c);
            if (c == ','){
                s = "";
                genres.push_back(s);
            }else{
                s += c;
            }
        }
        infile >> rating;
        infile.ignore(10000, '\n');
        Movie m = Movie(id, name, year, directors, actors, genres, rating);
        tmm_movie.insert(id, m);
        for (int i = 0; i < directors.size(); i++)
            tmm_director.insert(directors[i], m);
        for (int i = 0; i < actors.size(); i++)
            tmm_actor.insert(actors[i], m);
        for (int i = 0; i < genres.size(); i++)
            tmm_genre.insert(genres[i], m);
    }
    return true;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    return nullptr;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}
