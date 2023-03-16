//#include "UserDatabase.h"
//#include "User.h"
//
//#include <string>
//#include <vector>
//#include <iostream>
//#include <fstream>
//using namespace std;
//
//UserDatabase::UserDatabase()
//{
//    m_loaded = false;
//}
//
//bool UserDatabase::load(const string& filename)
//{
//    if (m_loaded) //already loaded
//    {
//        return false;
//    }
//    
//    ifstream infile(filename);
//    if (!infile)		        // Did opening the file fail?
//    {
//        return false;
//    }
//    else
//    {
//
//    }
//
//
//
//    return false;  // Replace this line with correct code.
//}
//
//User* UserDatabase::get_user_from_email(const string& email) const
//{
//    return nullptr;  // Replace this line with correct code.
//}

#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
   
}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);

    
    if (!infile)// Did opening the file fail?
    {
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        string full_name = line;

        getline(infile, line);
        string email = line;

        int movie_count;
        infile >> movie_count;
        infile.ignore(10000, '\n');

        vector<string> watch_history;

        for (int i = 0; i < movie_count; i++)
        {
            getline(infile, line);


            watch_history.push_back(line);
        }



        m_email_to_user.insert(email, new User(full_name, email, watch_history));
        getline(infile, line);

    }


    return true;  
}

User* UserDatabase::get_user_from_email(const string& email) const
{

    TreeMultimap<std::string, User*>::Iterator i = m_email_to_user.find(email);
    User* user = i.get_value();


    return user;

}