#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"
#include "User.h"
//class User;

class UserDatabase
{
public:
    UserDatabase();
    ~UserDatabase()
    {
        for (int i = 0; i < m_delete.size(); i++)
        {
            delete m_delete[i];
        }
        m_delete.clear();
    }
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

private:

    TreeMultimap<std::string, User*> m_email_to_user;
    bool m_loaded;
    std::vector<User*> m_delete;
};

#endif // USERDATABASE_INCLUDED
