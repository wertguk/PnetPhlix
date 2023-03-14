#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User*> tmm;   //store users in tree
    std::vector<User*> m_users; //store users to delete later
    bool m_called;
};

#endif // USERDATABASE_INCLUDED
