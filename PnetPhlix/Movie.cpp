#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating)
{
    m_id = id;  //copy variables passed in constructor to member variables
    m_title = title;
    m_year = release_year;
    m_rating = rating;
    vector<string>::const_iterator it;
    for (it = directors.begin(); it != directors.end(); it++)
        m_directors.push_back(*it);
    for (it = actors.begin(); it != actors.end(); it++)
        m_actors.push_back(*it);
    for (it = genres.begin(); it != genres.end(); it++)
        m_genres.push_back(*it);
}

string Movie::get_id() const
{
    return m_id;    //return id
}

string Movie::get_title() const
{
    return m_title; //return title
}

string Movie::get_release_year() const
{
    return m_year;  //return year
}

float Movie::get_rating() const
{
    return m_rating;    //return rating
}

vector<string> Movie::get_directors() const
{
    return m_directors; //return directors
}

vector<string> Movie::get_actors() const
{
    return m_actors;    //return actors
}

vector<string> Movie::get_genres() const
{
    return m_genres;    //return genres
}
