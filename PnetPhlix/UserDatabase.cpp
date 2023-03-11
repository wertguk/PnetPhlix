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
    int k = 0;
    while (getline(infile, s)){
        if (k > 0)
            getline(infile, s);
        int num;
        vector<string> movies;
        name = s;
        getline(infile, s);
        email = s;
        infile >> i;
        infile.ignore(10000, '\n');
        num = i;
        k++;
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
    if (!tmm.find(email).is_valid())
        return nullptr;
    return &tmm.find(email).get_value();
}
