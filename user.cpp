#include "user.hpp"
#include "timer.hpp"
#include <fstream>

using namespace std;

// === constructors === //

User::User() {
    name[0] = '\n';
    password[0] = '\n';
    
    stdTotal = 0;
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
    */

// === getters === //

string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}

Timer User::getstdtim() {
    return timer;
}

Pomodoro User::getpomtim() {
    return pomodoro;
}


// === functions === //
void User::inputName() {
    cout << "Enter a username: ";
    cin.getline(this->name, USERDATA_SIZE);

    while (!isValidName(name)) {
        cout << "Please enter a username with only alphanumeric characters, and is less than 16 characters." << endl;
        cout << "Enter a username: ";
        cin.getline(this->name, USERDATA_SIZE);
    }
}

void User::inputPwd() {
    cout << "Enter a password: ";
    cin.getline(this->password, USERDATA_SIZE);

    while (!isValidPwd(password)) {
        cout << "Please enter a password that is less than 16 characters." << endl;
        cout << "Enter a password: ";
        cin.getline(this->password, USERDATA_SIZE);
    }
}

bool User::checkPwd() {
    string input;
    
    cout << "Enter a password: ";
    getline(cin, input);
    
    while (!isValidPwd(input)) {
        cout << "Please enter a password that is less than 16 characters." << endl;
        cout << "Enter a password: ";
        getline(cin, input);
    }

    return (input == password);
}

// TODO: Clean up return statements to logic statements
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
    return (pwd.length() < 16);
} 

bool User::searchFor(string name, string filename) {
    char buffer[USERDATA_SIZE];
    int nUsers;

    // create file stream
    ifstream infile( filename, ios::binary | ios::in );

    // set file pointer to beginning of file
    infile.seekg(0, ios::beg);
    infile.read(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));

    // if byte 0 is eof, return false
    if (infile.eof()) {
        return false;
    }

    // search for user byte
    cout << "nUsers = " << nUsers << endl;
    for (int i = 0; i < nUsers; i++) {
        infile.seekg(i* (2*USERDATA_SIZE + 2*__SIZEOF_INT__) + __SIZEOF_INT__);
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

void User::startMenu(string filename) {
    cout << "===========================" << endl;
    cout << " Welcome to the Timer App! " << endl;
    cout << "===========================" << endl;
    cout << endl;

    string input;
    char choice;

    do {
        cout << "To continue to the timer app, please log-in or sign-up:" << endl;
        cout << "   A) Log-in" << endl;
        cout << "   B) Sign-up" << endl;
        cout << "   C) Quit" << endl;

        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        if (input.size()>1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }

        choice = input[0];
    
        // retry main menu if login/signup attempt is unsuccessful.
        switch (choice) {
            case 'A':
                if (!login(filename)) {
                    cout << "Log-in unsuccessful." << endl;
                    continue;
                } else {
                    return;
                }
                break;
            
            case 'B':
                if (!signup(filename)) {
                    cout << "Sign-up unsuccessful." << endl;
                    continue;
                } else {
                    return;
                }
                break;

            case 'C':
                return;
                break;

            default:
                cout << choice << " is not a valid choice." << endl;
                break;
        }
        cout << endl;
    } while (choice != 'C');
    
    return;
    
}

void User::timerMenu() {
    string input;
    char choice;

    cout << "Welcome, " << name << "!" << endl;
    cout << endl;
    cout << "===========================" << endl;
    cout << "        Timer Menu         " << endl;
    cout << "===========================" << endl;
    cout << endl;

    do {
        cout << "Please choose a timer to start: " << endl;
        cout << "   A) Start a Standard Timer" << endl;
        cout << "   B) Start a Pomodoro Timer" << endl;
        cout << "   C) View Stats" << endl;
        cout << "   D) Quit" << endl;

        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        if (input.size() >1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }

        choice = input[0];

        switch (choice) {
            case 'A':
                if (timer.run()) {
                    stdTotal += timer.getFocusTime();
                };
                break;
            
            case 'B':
                if (pomodoro.run()) {
                    pomTotal += (pomodoro.getReps() * pomodoro.getFocusTime()); 
                }
                break;

            case 'C':
                printData();
                break;
            
            case 'D':
                break;

            default:
            cout << choice << " is not a valid choice." << endl;
            break;
        }
        cout << endl;
    } while (choice != 'D');
    return;
}

void User::printData() {
    cout << "===========================" << endl;
    cout << "        Focus Stats        " << endl;
    cout << "===========================" << endl;
    cout << endl;
    cout << "Total standard timer mintues: " << stdTotal/60 << "min " << stdTotal%60 << "s" << endl;
    cout << "Total pomodoro timer minutes: " << pomTotal/60 << "min " << pomTotal%60 << "s" << endl;
}

bool User::login(string filename) {
    ifstream infile(filename, ios::binary | ios::in);
    
    // if file doesn't exist, user cannot log in.
    if (!infile) {
        cout << "Error: file does not exist. Please sign-up instead." << endl;
        return !infile;
    }
    
    // if file opens, continue on!

    // find a user in record
    inputName();
    bool isFound = searchFor(name, filename);
    cout << "found: " << isFound << endl;

    // if user is found, grab password from record.
    if (isFound) {
        infile.seekg(pos + USERDATA_SIZE, ios::beg);
        infile.read(reinterpret_cast<char*>(&password), sizeof(password));
    } else {
        infile.close();
        return isFound;
    }

    // if passwords match, dump record data into user object
    if (!checkPwd()) {
        cout << "login unsuccessful";
        infile.close();
        return false;
    }

    // load standard timer data
    infile.seekg(pos + 2*USERDATA_SIZE, ios::beg);
    infile.read(reinterpret_cast<char*>(&stdTotal), sizeof(stdTotal));

    // load pomodoro timer data
    infile.read(reinterpret_cast<char*>(&pomTotal), sizeof(pomTotal));

    cout << "standard timer: " << stdTotal << endl;
    cout << "pomodoro timer: " << pomTotal << endl;
    cout << "Login successful." << endl;
    infile.close();
    return true;
}

bool User::signup(string filename) {
    int nUsers;
    ifstream infile(filename, ios::binary | ios::in);
    
    // if file doesn't exist, # users is 0
    if (!infile) {
        nUsers = 0;
    
    // otherwise, read in # users.
    } else {
        infile.read(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));
    }
    infile.close();

    // since a sign-up will create a new record, use append flag.
    fstream outfile(filename, ios::binary | ios::out | ios::app);

    // input username
    cout << "Sign up for a timer account!" << endl;
    inputName();

    // if username exists, exit.
    if (searchFor(this->name, filename)) {
        cout << "Username already exists. Please log-in instead." << endl;
        outfile.close();
        return false;
    }


    // set valid password for user.
    inputPwd();
    
    // if the user is first in file, make sure they are an admin.
    outfile.seekp(0, ios::end);
    pos = outfile.tellp();

    if(outfile.tellp() == 0) {
        outfile.write(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));
    }

    // write out timer data
    outfile.write(reinterpret_cast<char*>(&name), sizeof(name));
    outfile.write(reinterpret_cast<char*>(&password), sizeof(password));
    outfile.write(reinterpret_cast<char*>(&stdTotal), sizeof(stdTotal));
    outfile.write(reinterpret_cast<char*>(&pomTotal), sizeof(pomTotal));
    outfile.close();

    // write out new nUsers
    fstream update(filename, ios::binary | ios::in | ios::out);
    nUsers++;
    update.seekp(0, ios::beg);
    update.write(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));
    cout << "nusers is now " << nUsers << endl;
    update.close();

    // if you get here, sign-up successful!
    return true;
}

void User::save(string filename) {
    // flags: append
    fstream outfile(filename, ios::binary | ios::in | ios::out);
    
    outfile.seekp(pos+2*USERDATA_SIZE, ios::beg);

    cout << "do we get here?" << endl;
    // move ptr to user pos & write out timer data
    cout << outfile.tellp();
    outfile.write(reinterpret_cast<char*>(&stdTotal), sizeof(stdTotal));
    outfile.write(reinterpret_cast<char*>(&pomTotal), sizeof(pomTotal));

    // done saving user data.
    outfile.close();
}