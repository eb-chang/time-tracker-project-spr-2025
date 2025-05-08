#ifndef USER_H
#define USER_H

#include "timer.hpp"
#include "pomodoro.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int USERDATA_SIZE = 16;

class User {
    private:
        char name[USERDATA_SIZE] ; // user's name
        char password[USERDATA_SIZE]; // user's password
        int pos;    // byte position of user data
        
        int stdTotal;   // total time focused for standard timer
        int pomTotal;   // total time focused for pomodoro timer

        Timer timer;        // holds current timer info
        Pomodoro pomodoro;  // holds current pomodoro info

        // stretch goal: History storage
        /* vector<Timer> tHistory;
        vector<Pomodoro> pHistory; */
    public:
        //constructor
        User();

        //setters
        void setName(string nm);
        void setPassword(string pwd);
        void setStdTot(int stdTot);
        void setPomTot(int pomTot);

        //getters
        string getName();
        string getPassword();
        Timer getstdtim();
        Pomodoro getpomtim();

        // functions
        void inputName();
        void inputPwd();
        bool checkPwd();

        bool isValidName(string name);
        bool isValidPwd(string pwd);

        bool searchFor(string name, string filename);
        
        void startMenu(string filename);
        void timerMenu();
        void printData();

        bool login(string filename);
        bool signup(string filename);
        

        void save(string filename);

        
        

};

#endif //USER_H