#include "MovieDatabase.h"
#include "Movie.h"
#include <cctype>
#include <string>
#include <vector>
using namespace std;

MovieDatabase::MovieDatabase()
{
    m_called = false;   //set called to false
}

MovieDatabase::~MovieDatabase()
{
    for (int i = 0; i < m_movies.size(); i++)   //delete all dynamically allocated movies
        delete m_movies[i];
}

bool MovieDatabase::load(const string& filename)
{
    if (m_called)   //only load if not loaded before
        return false;
    ifstream infile(filename);
    if (!infile)
        return false;
    string id, uid, name, uname, year, s;   //store both lower case and upper case strings
    float rating;
    int k = 0;
    while (getline(infile, s)){ //read in line while not finished reading file
        if (k > 0)  //skip empty line between movies
            getline(infile, s); //read in id
        k++;
        id = s;
        uid = s;
        for (int i = 0; i < id.size(); i++) //make id lower case
            id[i] = tolower(id[i]);
        getline(infile, s); //read in name
        name = s;
        uname = s;
        for (int i = 0; i < name.size(); i++)   //make name lower case
            name[i] = tolower(name[i]);
        getline(infile, s); //read in year
        year = s;
        char c = ',';
        s = "";
        string us = "";
        vector<string> directors;   //lower case directors
        vector<string> udirectors;
        while (c != '\n'){  //get each director between commas
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
        vector<string> actors;  //lower case actors
        vector<string> uactors;
        while (c != '\n'){  //get each actor between commas
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
        vector<string> genres;  //lower case genres
        vector<string> ugenres;
        while (c != '\n'){  //get each genre between commas
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
        infile >> rating;   //get rating
        infile.ignore(10000, '\n');
        Movie* m = new Movie(uid, uname, year, udirectors, uactors, ugenres, rating);   //create new movie
        m_movies.push_back(m);  //insert movies into vector
        tmm_movie.insert(id, m);
        for (int i = 0; i < directors.size(); i++)  //insert movies into trees
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
    for (int i = 0; i < id.size(); i++) //make id lowercase
        nId += tolower(id[i]);
    if (!tmm_movie.find(nId).is_valid())    //if movie not found return null
        return nullptr;
    return tmm_movie.find(nId).get_value(); //if movie found return pointer to movie
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string nDirector = "";
    for (int i = 0; i < director.size(); i++)   //make director lowercase
        nDirector += tolower(director[i]);
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = tmm_director.find(nDirector);   //get iterator to director
    while (it.is_valid()){  //add director movies to vector
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string nActor = "";
    for (int i = 0; i < actor.size(); i++)  //make actor lowercase
        nActor += tolower(actor[i]);
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = tmm_actor.find(nActor); //get iterator to actors
    while (it.is_valid()){  //add actor movies to vector
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string nGenre = "";
    for (int i = 0; i < genre.size(); i++)  //make genre lowercase
        nGenre += tolower(genre[i]);
    vector<Movie*> movies;
    TreeMultimap<string, Movie*>::Iterator it = tmm_genre.find(nGenre); //get iterato to genres
    while (it.is_valid()){  //add genre movies to vector
        movies.push_back(it.get_value());
        it.advance();
    }
    return movies;
}
