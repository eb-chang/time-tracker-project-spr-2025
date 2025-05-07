#include "user.hpp"
#include <fstream>

using namespace std;

// === constructors === //

User::User() {
    name[0] = '\n';
    password[0] = '\n';
    
    timerTotal = 0;
    pomTotal = 0;
    //tHistory = {};
    //pHistory = {};
}
/*
User::User(string nm, string pwd) {
    name = nm;
    password = pwd;
    tHistory = {};
    pHistory = {};
}

User::User(string nm, string pwd, vector<Timer> t_hist, vector<Pomodoro> p_hist) {
    this->name = nm;
    this->password = pwd;
    this->tHistory = t_hist;
    this->pHistory = p_hist;
}
*/

// === setters === //

/*
void User::setName(string nm) {
    this->name = nm;
}

void User::setPassword(string pwd) {
    this->password = pwd;
}

void User::setTimerHist(vector<Timer> t_hist) {
    this->tHistory = t_hist;
}

// === getters === //

string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}

vector<Timer> User::getTimerHist() {
    return tHistory;
}

vector<Pomodoro> User::getPomHist() {
    return pHistory;
}
*/

// === functions === //
void User::inputName() {
    string input;

    cout << "Enter a username: ";
    cin.getline(this->name, USERDATA_SIZE);

    while (!isValidName(name)) {
        cout << "Please enter a username with only alphanumeric characters, and is less than 16 characters." << endl;
        cout << "Enter a username: ";
        cin.getline(this->name, USERDATA_SIZE);
    }
}

void User::inputPwd() {
    string input;
    
    cout << "Enter a password: ";
    cin.getline(this->password, USERDATA_SIZE);
    while (!isValidPwd(password)) {
        cout << "Please enter a password that is less than 16 characters." << endl;
        cout << "Enter a password: ";
        cin.getline(this->password, USERDATA_SIZE);
    }
}
bool User::isValidName(string name) {
    // name isn't valid if string is empty
    if (name.length() < 1) {
        return false;
    }

    // name isn't valid if name is 16 chars or longer
    if (name.length() > 16) {
        return false;
    }

    // name isn't valid if it has non-alphanumeric chars
    for (int i = 0; i < name.length(); i++) {
        if (!isalnum(name[i])) {
            return false;
        }
    }

    // name is valid.
    return true;
}

bool User::isValidPwd(string pwd) {
    // pwd isn't valid if it is 16 chars or longer
    if (pwd.length() > 16) {
        return false;
    };

    // pwd is valid
    return true;
} 

bool User::searchFor(string name, string filename) {
    char buffer[USERDATA_SIZE];
    int nUsers;

    // create file stream
    ifstream infile( filename, ios::binary | ios::in );

    // set file pointer to beginning of file
    infile.seekg(0, ios::beg);
    infile.read(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));

    // search for user byte
    cout << "nUsers = " << nUsers << endl;
    for (int i = 0; i < nUsers; i++) {
        infile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        cout << i+1 << ". " << buffer << endl;

        // if user is found, return byte at which user data is stored.
        if (buffer == name) {
            infile.seekg(-USERDATA_SIZE, ios::cur); // back it up
            
            this->pos = infile.tellg();
            cout << "user found at byte " << pos << endl;
            return true;
        }
    }

    // if user is not found, return false
    return false;
}

bool User::login() {
    string input;
    cout << "Please enter your password: ";
    getline(cin, input);

    // password must be less than length limit AND match user's recorded password.
    return(isValidPwd(input) && (input == password));
}

void User::load(string filename) {
    ifstream infile(filename, ios::binary | ios::in);
    // get username
    inputName();

    // does bin file exist?
    if (!infile) {
        cout << "Error: file does not exist." << endl;
    }

    // search binary file
    bool found;
    found = searchFor(name, filename);
    cout << "found: " << found << endl;


    // if user found, read in pwd
    if (found) {
        infile.seekg(pos + USERDATA_SIZE, ios::beg);
        infile.read(reinterpret_cast<char*>(&password), sizeof(password));
        cout << "pwd: " << this->password << endl;

        // if log-in successful, dump data into User object
        if (login()) {
            // load standard timer data
            infile.seekg(pos + 2*USERDATA_SIZE, ios::beg);
            infile.read(reinterpret_cast<char*>(&timerTotal), sizeof(timerTotal));
    
            // load pomodoro timer data
            infile.read(reinterpret_cast<char*>(&pomTotal), sizeof(pomTotal));
    
            cout << "standard timer: " << timerTotal << endl;
            cout << "pomodoro tiemr: " << pomTotal << endl;
        }
    }

    // if user not found, prompt password.
    if (!found) {
        cout << "User " << name << " not found. ";
    }

    // if user not found, prompt password
    // else:
    // "user not found, please enter a password to create an account."

}

void User::save(string filename) {
    // flags: append
    ofstream outfile(filename, ios::binary | ios::in | ios::app);

    // if file doesn't exist, create a new binary file to save data.
    if (!outfile) {
        cout << "Error: could not open user record for saving. ";
        cout << "creating a new binary file named \"" << filename << "\"" << endl;

    }

    // 
}