#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User> tmm;
    bool m_called;
};

#endif // USERDATABASE_INCLUDED
