#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
    m_called = false;   //set called to false
}

UserDatabase::~UserDatabase()
{
    for (int i = 0; i < m_users.size(); i++)    //delete all dynamically allocated user objects
        delete m_users[i];
}

bool UserDatabase::load(const string& filename)
{
    if (m_called)   //load if not called before
        return false;
    ifstream infile(filename);
    if (!infile)
        return false;
    string s, name, email;
    int i;
    int k = 0;
    while (getline(infile, s)){ //continue reading file if end not reached
        if (k > 0) //skip empty line between users
            getline(infile, s); //read in name
        vector<string> movies;
        name = s;
        getline(infile, s); //read in email
        email = s;
        infile >> i;    //read in number of movies
        infile.ignore(10000, '\n');
        k++;
        for (int j = 0; j < i; j++){    //store movie ids
            getline(infile, s);
            movies.push_back(s);
        }
        User* u = new User(name, email, movies);    //create new user and add to tree and vector
        m_users.push_back(u);
        tmm.insert(email, u);
    }
    m_called = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (!tmm.find(email).is_valid())    //return nullptr if email not found
        return nullptr;
    return tmm.find(email).get_value(); //return iterator to found user
}
