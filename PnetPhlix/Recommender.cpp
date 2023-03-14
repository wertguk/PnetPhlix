#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_udb = &user_database; //set pointers to databases
    m_mdb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<string> user_movies = m_udb->get_user_from_email(user_email)->get_watch_history();
    unordered_map<Movie*, int> ratings;
    //store user movies in vector and ratings of movies in hash map
    for (int i = 0; i < user_movies.size(); i++){
        Movie* m = m_mdb->get_movie_from_id(user_movies[i]);    //get movies in watch history
        //find movies from database with same director and add rating to hashmap
        vector<string> directors = m->get_directors();
        for (int j = 0; j < directors.size(); j++){
            vector<Movie*> dMovies = m_mdb->get_movies_with_director(directors[j]);
            for (int k = 0; k < dMovies.size(); k++){
                ratings[dMovies[k]] += 20;
            }
        }
        //find movies from database with same actor and add rating to hashmap
        vector<string> actors = m->get_actors();
        for (int j = 0; j < actors.size(); j++){
            vector<Movie*> aMovies = m_mdb->get_movies_with_actor(actors[j]);
            for (int k = 0; k < aMovies.size(); k++){
                ratings[aMovies[k]] += 30;
            }
        }
        //find movies from database with same genre and add rating to hashmap
        vector<string> genres = m->get_genres();
        for (int j = 0; j < genres.size(); j++){
            vector<Movie*> gMovies = m_mdb->get_movies_with_genre(genres[j]);
            for (int k = 0; k < gMovies.size(); k++){
                ratings[gMovies[k]] += 1;
            }
        }
    }
    //add all movie and rank pairs to recommendation vector
    vector<MovieAndRank> recommendations;
    for (auto it = ratings.begin(); it != ratings.end(); it++){
        MovieAndRank movierank = MovieAndRank(it->first->get_id(), it->second);
        recommendations.push_back(movierank);
    }
    //sort recommendations using custom comparator
    sort(recommendations.begin(), recommendations.end(), [this] (const MovieAndRank& a, const MovieAndRank& b){
            if (a.compatibility_score != b.compatibility_score)
                return a.compatibility_score > b.compatibility_score;
            else
                return m_mdb->get_movie_from_id(a.movie_id)->get_title() < m_mdb->get_movie_from_id(b.movie_id)->get_title();
        }
    );
    //take recommendations and add first movie_count non watched movie and ranks
    vector<MovieAndRank> result;
    int inserted = 0;
    int i = 0;
    while (inserted < movie_count){
        bool watched = false;
        for (int j = 0; j < user_movies.size(); j++){
            if (recommendations[i].movie_id == user_movies[j]){
                watched = true;
            }
        }
        if (!watched){
            result.push_back(recommendations[i]);
            inserted++;
        }
        i++;
    }
    return result; 
}
