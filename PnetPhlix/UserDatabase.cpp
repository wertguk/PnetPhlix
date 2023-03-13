#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
    m_called = false;
}

UserDatabase::~UserDatabase()
{
    for (int i = 0; i < m_users.size(); i++)
        delete m_users[i];
}

bool UserDatabase::load(const string& filename)
{
    if (m_called)
        return false;
    ifstream infile(filename);
    if (!infile)
        return false;
    string s, name, email;
    int i;
    int k = 0;
    while (getline(infile, s)){
        if (k > 0)
            getline(infile, s);
        vector<string> movies;
        name = s;
        getline(infile, s);
        email = s;
        infile >> i;
        infile.ignore(10000, '\n');
        k++;
        for (int j = 0; j < i; j++){
            getline(infile, s);
            movies.push_back(s);
        }
        User* u = new User(name, email, movies);
        m_users.push_back(u);
        tmm.insert(email, u);
    }
    m_called = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (!tmm.find(email).is_valid())
        return nullptr;
    return tmm.find(email).get_value();
}
