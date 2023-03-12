#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_udb = user_database;
    m_mdb = movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<string> user_movies = m_udb.get_user_from_email(user_email)->get_watch_history();
    unordered_map<Movie*, int> ratings;
    for (int i = 0; i < user_movies.size(); i++){
        Movie* m = m_mdb.get_movie_from_id(user_movies[i]);
        vector<string> directors = m->get_directors();
        for (int j = 0; j < directors.size(); j++){
            vector<Movie*> dMovies = m_mdb.get_movies_with_director(directors[j]);
            for (int k = 0; k < dMovies.size(); k++){
                ratings[dMovies[k]] += 20;
            }
        }
        vector<string> actors = m->get_actors();
        for (int j = 0; j < actors.size(); j++){
            vector<Movie*> aMovies = m_mdb.get_movies_with_actor(actors[j]);
            for (int k = 0; k < aMovies.size(); k++){
                ratings[aMovies[k]] += 30;
            }
        }
        vector<string> genres = m->get_genres();
        for (int j = 0; j < genres.size(); j++){
            vector<Movie*> gMovies = m_mdb.get_movies_with_genre(genres[j]);
            for (int k = 0; k < gMovies.size(); k++){
                ratings[gMovies[k]] += 1;
            }
        }
    }
    vector<MovieAndRank> recommendations;
    for (auto it = ratings.begin(); it != ratings.end(); it++){
        MovieAndRank movierank = MovieAndRank(it->first->get_id(), it->second);
        recommendations.push_back(movierank);
    }
    vector<MovieAndRank> result;
    for (int i = 0; i < movie_count; i++)
        result.push_back(recommendations[i]);
    return result;  // Replace this line with correct code.
}
