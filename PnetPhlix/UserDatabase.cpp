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
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    return nullptr;  // Replace this line with correct code.
}
