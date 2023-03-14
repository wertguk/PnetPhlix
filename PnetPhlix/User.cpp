#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    m_name = full_name; //copy name, email, and watch history into User member variables
    m_email = email;
    for (vector<string>::const_iterator it = watch_history.begin(); it != watch_history.end(); it++)
        m_movieList.push_back(*it);
}

string User::get_full_name() const
{
    return m_name;  //return name
}

string User::get_email() const
{
    return m_email; //return email
}

vector<string> User::get_watch_history() const
{
    return m_movieList; //return watch history
}
