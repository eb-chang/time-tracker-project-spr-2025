#ifndef USER_CLASS_H
#define USER_CLASS_H

#include "timer_class.hpp"
#include "pomodoro_class.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class User {
    private:
        string name; // user's name
        string password;
        // TODO: history storage mechanism
        vector<Timer> tHistory;
        vector<Pomodoro> pHistory;  //maybe a stretch goal
    public:
        //constructor
        User();
        User(string nm, string pwd);

        //setters
        void setName(string nm);
        void setPassword(string pwd);

        //getters
        string getName();
        string getPassword();

        void login();
         // 1) get [username]
            // 2) read binary file full of users
            // 3) parse until username found
            //     a) if user not found, reprompt startMenu.
            //     b) if user found, prompt password
            // 4) get [password]
            //     a) if password does not mathc, prompt:
            //         i) try again
            //        ii) quit
            //     b) if password matches assigned user, prompt "welcome" menu.
        
        void signup();
            // 1) get [username]
            // 2) "is [username] correct?"
            //     a) if username is correct, continue
            //     b) if username is wrong, re-get [username]
            // 3) get [password]
            // 4) "is [password] correct?"
            //     a) if pwd is correct, continue
            //     b) if pwd is wrong, re-get []

        // TODO: setHistory
        //       getHistory
        //       totalTime
        //write
        //read
};

#endif //USER_CLASS_H