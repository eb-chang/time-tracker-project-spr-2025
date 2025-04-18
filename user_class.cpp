#include "user_class.hpp"

using namespace std;

// constructors
User::User() {
    name = "";
    password = "";
}

User::User(string nm, string pwd) {
    name = nm;
    password = pwd;
}

// setters
void User::setName(string nm) {
    name = nm;
}

void User::setPassword(string pwd) {
    password = pwd;
}

// getters
string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}

// functions
void User::login() {
    string nm;
    string pwd;
    ofstream userData;

    // fix flags
    userData.open("./timer.bin", ios::out | ios::app | ios::binary);

    if (userData.is_open()) {
        // file is open!

    }





    cout << "Please enter your username: ";
    cin >> nm;

}

void User::signup() {
    string nm;
    string pwd;
    ofstream userData;

    userData.open("./timer.bin", ios::out | ios::app | ios::binary);
    if (userData.is_open()) {
        //file is open!
        cout << "binary file open." << endl;

        cout << "Enter a username: ";
        cin >> nm;
    
        cout << "Enter a password: ";
        cin >> pwd;
    
 
        userData << nm << " " << pwd;

        cout << "Data written to file.";
        userData.close();
    }
}