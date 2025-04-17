#ifndef USER_CLASS_H
#define USER_CLASS_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class User {
    private:
        string name; // user's name
        string password;
        // TODO: history storage mechanism
    public:
        //constructor
        User();
        User(string name, string password);

        //setters
        string setName();
        string setPassword();
        // TODO: setHistory
        //       getHistory
        //       totalTime
};

#endif //USER_CLASS_H