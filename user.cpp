#include "user.hpp"
#include "timer.hpp"
#include <fstream>

using namespace std;

// === constructors === //

User::User() {
    name[0] = '\0';
    password[0] = '\0';
    
    stdTotal = 0;
    pomTotal = 0;

    admin = false;
}

// === getters === //

string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}

int User::getTotstdtim() {
    return stdTotal;
}

int User::getTotpomtim() {
    return pomTotal;
}

Timer User::getstdtim() {
    return timer;
}

Pomodoro User::getpomtim() {
    return pomodoro;
}


// === functions === //

/*
Gets a user-input username that is validated, then set as the User object's name.
Used in User::login() and User::signup().
*/
void User::inputName() {
    cout << "Enter a username: ";
    cin.getline(this->name, USERDATA_SIZE);

    while (!isValidName(name)) {
        cout << "Please enter a username with only alphanumeric characters, and is less than 16 characters." << endl;
        cout << "Enter a username: ";
        cin.getline(this->name, USERDATA_SIZE);
    }
}

/*
Gets a user-input password that is validated, then set as the User object's password.
Used in User::login() and User::signup().
*/
void User::inputPwd() {
    cout << "Enter a password: ";
    cin.getline(this->password, USERDATA_SIZE);

    while (!isValidPwd(password)) {
        cout << "Please enter a password that is less than 16 characters." << endl;
        cout << "Enter a password: ";
        cin.getline(this->password, USERDATA_SIZE);
    }
}

/*
Checks if a user-input password matches the password private member.
*/
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
/*
Checks if the argument string is a valid username, i.e.,
less than 16 chars, not empty, and alphanumeric
*/
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
/*
Checks if the argument string is a valid password,
i.e., less than 16 chars and not empty
*/
bool User::isValidPwd(string pwd) {
    // pwd isn't valid if it is 16 chars or longer
    return (pwd.length() < 16);

    // pwd isn't valid if it is empty
    return (pwd.length() != 0);
} 

/*
Returns true if the argument string is found in the binary file filename
*/
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
    for (int i = 0; i < nUsers; i++) {
        infile.seekg(i* (2*USERDATA_SIZE + 2*__SIZEOF_INT__ + 1) + __SIZEOF_INT__);
        infile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        cout << i+1 << ". " << buffer << endl;

        // if user is found, return byte at which user data is stored.
        if (buffer == name) {
            infile.seekg(-USERDATA_SIZE, ios::cur); // back it up
            
            this->pos = infile.tellg();
            infile.close();
            return true;
        }
    }

    // if user is not found, return false
    infile.close();
    return false;
}

/*
Output login/signup menu interface for user
*/
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
/*
Output main timer menu interface for user
*/
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

/*
Outputs user’s timer totals
*/
void User::printData() {
    cout << "===========================" << endl;
    cout << "        Focus Stats        " << endl;
    cout << "===========================" << endl;
    cout << endl;
    cout << "Total standard timer mintues: " << stdTotal/60 << "min " << stdTotal%60 << "s" << endl;
    cout << "Total pomodoro timer minutes: " << pomTotal/60 << "min " << pomTotal%60 << "s" << endl;
}

/*
Loads user data from filename
*/
bool User::login(string filename) {
    ifstream infile(filename, ios::binary | ios::in);
    
    // if file doesn't exist, user cannot log in.
    if (!infile) {
        cout << "Error: file does not exist. Please sign-up instead." << endl;
        return false;
    }
    
    // if file opens, continue on!

    // find a user in record
    inputName();
    bool isFound = searchFor(name, filename);

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
        infile.close();
        return false;
    }

    // load standard timer data
    infile.seekg(pos + 2*USERDATA_SIZE, ios::beg);
    infile.read(reinterpret_cast<char*>(&stdTotal), sizeof(stdTotal));

    // load pomodoro timer data
    infile.read(reinterpret_cast<char*>(&pomTotal), sizeof(pomTotal));

    // load admin data
    infile.read(reinterpret_cast<char*>(&admin), sizeof(admin));

    infile.close();
    return true;
}

/*
Creates new user data in filename
*/
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
        admin = true;
    }

    // write out timer data
    outfile.write(reinterpret_cast<char*>(&name), sizeof(name));
    outfile.write(reinterpret_cast<char*>(&password), sizeof(password));
    outfile.write(reinterpret_cast<char*>(&stdTotal), sizeof(stdTotal));
    outfile.write(reinterpret_cast<char*>(&pomTotal), sizeof(pomTotal));
    outfile.write(reinterpret_cast<char*>(&admin), sizeof(admin));
    outfile.close();

    // write out new nUsers
    fstream update(filename, ios::binary | ios::in | ios::out);
    nUsers++;
    update.seekp(0, ios::beg);
    update.write(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));
    update.close();

    // if you get here, sign-up successful!
    return true;
}

/*
Saves out user data to filename
*/
void User::save(string filename) {
    // flags: append
    fstream outfile(filename, ios::binary | ios::in | ios::out);
    outfile.seekp(pos+2*USERDATA_SIZE, ios::beg);

    // move ptr to user pos & write out timer data
    outfile.write(reinterpret_cast<char*>(&stdTotal), sizeof(stdTotal));
    outfile.write(reinterpret_cast<char*>(&pomTotal), sizeof(pomTotal));
    outfile.write(reinterpret_cast<char*>(&admin), sizeof(admin));

    // done saving user data.
    outfile.close();
}

// === admin functions === //

/*
Outputs admin menu interface if a user is an admin
*/
void User::adminMenu(string filename) {
    if (!admin) {
        // not allowed to access this function if user is not an admin
        return;
    }

    string input;
    char choice;

    cout << "===========================" << endl;
    cout << "        Admin Menu         " << endl;
    cout << "===========================" << endl;
    cout << endl;
    do {
        cout << "Please choose an action: " << endl;
        cout << "   A) Edit a Record" << endl;
        cout << "   B) Continue to Timer app" << endl;

        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        if (input.size() >1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }

        choice = input[0];

        switch (choice) {
            case 'A':
                edit(filename);
                break;
            
            case 'B':
                break;
            
            default:
            cout << choice << " is not a valid choice." << endl;
            break;
        }
        cout << endl;
    } while (choice != 'B');
}

/*
Returns byte position of argument string in filename. Returns -1 if not found.
*/
int User::find(string name, string filename) {
    char buffer[USERDATA_SIZE];
    int nUsers;
    int found;

    ifstream infile(filename, ios::in | ios::binary);

    infile.seekg(0, ios::beg);
    infile.read(reinterpret_cast<char*>(&nUsers), sizeof(nUsers));

    for (int i = 0; i < nUsers; i++) {
        infile.seekg(i* (2*USERDATA_SIZE + 2*__SIZEOF_INT__ + 1) + __SIZEOF_INT__);
        infile.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));


        // if user is found, return byte at which user data is stored.
        if (buffer == name) {
            infile.seekg(-USERDATA_SIZE, ios::cur); // back it up
            found = infile.tellg();
            infile.close();

            return found;
        }
    }

    // if user not found return -1
    return -1;
}

/*
Allows an admin to edit respective total values for a user.
*/
void User::edit(string filename) {
    if (!admin) {
        // not allowed to access this function if user is not an admin
        return;
    }
    int editPos;
    char tempname[USERDATA_SIZE];

    cout << "Enter a username: ";
    cin.getline(tempname, USERDATA_SIZE);

    if (!isValidName(tempname)) {
        cout << "Invalid name." << endl;
        return;
    }
    editPos = find(tempname, filename);

    if (editPos == -1) {
        cout << "User could not be found." << endl;
        return;
    }

    char choice;
    string input;
    int temptime;

    fstream editfile(filename, ios::binary | ios::in | ios::out);

    
    do {
        cout << "What would you like to edit for " << tempname << "?" << endl;
        cout << "   A) Total standard timer time" << endl;
        cout << "   B) Total pomodoro timer time" << endl;
        cout << "   C) Quit" << endl;

        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        if (input.size() >1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }

        choice = input[0];

        switch (choice) {
            case 'A':
                cout << "Enter a new total time in seconds: ";
                cin >> temptime;
                if (!cin.fail()) {
                    int newPos;
                    newPos = editPos + 2*USERDATA_SIZE;

                    editfile.seekp(newPos, ios::beg);
                    editfile.write(reinterpret_cast<char*>(&temptime), sizeof(temptime));
                } else {
                    cout << "That was not a valid input." << endl;
                    editfile.close();
                    return;
                }
                break;
            
            case 'B':
                cout << "Enter a new total time in seconds: ";
                cin >> temptime;
                if (!cin.fail()) {
                    int newPos;
                    newPos = editPos + 2*USERDATA_SIZE + __SIZEOF_INT__;

                    editfile.seekp(newPos, ios::beg);
                    editfile.write(reinterpret_cast<char*>(&temptime), sizeof(temptime));
                } else {
                    cout << "That was not a valid input." << endl;
                    editfile.close();
                    return;
                }
                break;

            case 'C':
                break;
            
            default:
            cout << choice << " is not a valid choice." << endl;
            break;
        }
        cout << endl;
    } while (choice != 'C');
    editfile.close();
    return;
}

// in progress
void User::remove(string filename) {
    if (!admin) {
        // not allowed to access this function if user is not an admin
        return;
    }
}