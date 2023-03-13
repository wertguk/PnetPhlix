#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "Recommender.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/heran/Desktop/PnetPhlix/PnetPhlix/users.txt";
const string MOVIE_DATAFILE = "/Users/heran/Desktop/PnetPhlix/PnetPhlix/movies.txt";

void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations) {
    // get up to ten movie recommendations for the user
    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, 10);
    if (recommendations.empty())
       cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i]; Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i << ". " << m->get_title() << " ("
                << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: " << mr.compatibility_score << "\n";
        }
    }
}

int main()
{
	UserDatabase udb;
    MovieDatabase mdb;
	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
    if (!mdb.load(MOVIE_DATAFILE))
    {
        cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    Recommender rec = Recommender(udb, mdb);
	for (;;)
	{
        
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
        if (u == nullptr){
			cout << "No user in the database has that email address." << endl;
        }else{
            for (int i = 0; i < u->get_watch_history().size(); i++)
                cout << mdb.get_movie_from_id(u->get_watch_history()[i])->get_title() << endl;
            findMatches(rec, mdb, email, 8);
        }
        /*
        cout << "Enter actor (or quit): ";
        string id;
        getline(cin, id);
        if (id == "quit")
            return 0;
        vector<Movie*> m = mdb.get_movies_with_actor(id);
        if (m.empty()){
            cout << "No movie in the database has that actor." << endl;
        }else{
            cout << "Acted in:\n";
            for (int i = 0; i < m.size(); i++)
                cout << m[i]->get_title() << endl;
        }
         */
        /*
        cout << "Enter movie ID (or quit): ";
        string id;
        getline(cin, id);
        if (id == "quit")
            return 0;
        Movie* m = mdb.get_movie_from_id(id);
        if (m == nullptr){
            cout << "No movie in the database has that actor." << endl;
        }else{
            for (int i = 0; i < m->get_actors().size(); i++)
                cout << m->get_actors()[i] << endl;
        }
         */
	}
}
