#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
    m_loaded = false;
}

bool UserDatabase::load(const string& filename)
{
    if (m_loaded == true)
    {
        return false;
    }
    ifstream infile(filename);

    
    if (!infile)// Did opening the file fail?
    {
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        string full_name = line; //first line is the name

        getline(infile, line); //go next line for email
        string email = line;

        int movie_count;
        infile >> movie_count;

        infile.ignore(100000, '\n');

        vector<string> history;

        for (int i = 0; i < movie_count; i++) //loop throught the lines and push the name of movie in
        {
            getline(infile, line);


            history.push_back(line);
        }

        cout << full_name << endl;
        cout << email << endl;
        for (int i = 0; i < history.size(); ++i)
            cout << history[i] << endl;
        User* current = new  User(full_name, email, history); //make the new user
        m_delete.push_back(current); //push it to a vector to delete

        m_email_to_user.insert(email, current); 
        getline(infile, line);

    }

    m_loaded = true;
    return true;  
}

User* UserDatabase::get_user_from_email(const string& email) const
{

    TreeMultimap<std::string, User*>::Iterator i = m_email_to_user.find(email);

    if (!i.is_valid())
    {
        return nullptr;
    }

    User* user = i.get_value();


    return user;

}