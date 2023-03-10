#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
    m_called = false;
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
        return false;
    string s, name, email;
    int i;
    while (getline(infile, s)){
        int num;
        vector<string> movies;
        if (s == "")
            getline(infile, s);
        name = s;
        getline(infile, s);
        email = s;
        infile >> i;
        num = i;
        for (int j = 0; j < i; j++){
            getline(infile, s);
            movies.push_back(s);
        }
        User u = User(name, email, movies);
        tmm.insert(email, u);
    }
    m_called = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    return &tmm.find(email).get_value();
}
