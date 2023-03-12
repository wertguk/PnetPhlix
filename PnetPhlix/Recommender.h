#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "UserDatabase.h"
#include "MovieDatabase.h"

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}
    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    MovieDatabase m_mdb;
    UserDatabase m_udb;
    struct cmp {
        bool operator()(const MovieAndRank& a, const MovieAndRank& b){
            if (a.compatibility_score != b.compatibility_score)
                return a.compatibility_score > b.compatibility_score;
            else
                return a.movie_id < b.movie_id;
        }
    };
};

#endif // RECOMMENDER_INCLUDED
