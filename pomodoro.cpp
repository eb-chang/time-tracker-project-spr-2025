#include "pomodoro.hpp"
#include <iomanip>

using namespace std;

// === constructors === //

Pomodoro::Pomodoro() {
    setFocusTime(0);
    this->breakTime = 0;
    this->nReps = 0;
}

// === setters === //

void Pomodoro::setBreakTime(int btime) {
    this->breakTime = btime;
}

void Pomodoro::setReps(int reps) {
    this->nReps = reps;
}

// === getters === //

int Pomodoro::getBreakTime() {
    return this->breakTime;
}

int Pomodoro::getReps() {
    return this->nReps;
}

// === functions === //

/*
Overloads Timer::confirm().
Allows user to confirm that their chosen pomodoro timer parameters are correct.
To be used in the Pomodoro::run() function
*/
bool Pomodoro::confirm() {
    string input;
    char choice;

    int minutes = getFocusTime()/60;
    int seconds = getFocusTime()%60;

    int bMinutes = breakTime/60;
    int bSeconds = breakTime%60;

    cout << "Would you like to start a timer for " << minutes << "min " << seconds << "s," << endl;
    cout << "with a " << bMinutes << "min " << bSeconds << "s break" << endl;
    cout << "for " << nReps << " repetitions?" << endl;
    cout << "   A) Start" << endl;
    cout << "   B) Cancel" << endl;
    do {
        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        if (input.size() >1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }
        
        choice = input[0];
        
        switch (choice) {
            case 'A':
            return true;
            break;

            case 'B':
            break;

            default:
            cout << choice << " is not a valid choice." << endl;
        }
        cout << endl;
    } while (choice != 'B');
    return false;
}

/*
Displays a timer that counts down break time for the user.
To be used in the run() function
*/
void Pomodoro::displayBreak() {
    for (int i = getBreakTime(); i>=0; --i) {
        int bmin = i/60;
        int bsec = i%60;
        cout << "\rBreak time remaining: "
        << setw(2) << setfill('0') << bmin << ":" // minutes left
        << setw(2) << setfill('0') << bsec       // seconds left
        << flush;                                    // flush output
        // sleep for 1 second, then update.
        this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "\rBreak time's up!             " << endl;
}

/*
Overloads Timer::run().
Runs the timer for the user.
Returns true if all timer repetitions have been completed. 
*/
bool Pomodoro::run() {
    // reset done flag
    setDone(false);
    selectFocusTime();
    selectBreakTime();
    selectReps();
    if (!this->confirm()) {
        return isDone();
    }

    for(int i = 0; i < nReps; i++) {
        display();
        displayBreak();
    }
    return isDone();
}

/*
Displays menu to grab user input
to select from preset values for break timer lengths
*/
void Pomodoro::selectBreakTime() {
    string input;
    char choice;
    bool valid = false;

    // set this->breakTime in seconds depending on choice
    do {
        // output menu for user choice
        cout << "Please select an amount of time to rest:" << endl;
        cout << "   A) 5 minutes" << endl;
        cout << "   B) 10 minutes" << endl;
        cout << "   C) 15 minutes" << endl;
        cout << "   D) Custom break time" << endl;

        // get user choice
        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        // check if input is a single char
        if (input.size() > 1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }

        choice = input[0];

        switch (choice) {
            case 'A':
                valid = true;
                this->breakTime = 300;
                break;

            case 'B':
                valid = true;
                this->breakTime = 600;
                break;
            
            case 'C':
                valid = true;
                this->breakTime = 900;
                break;

            case 'D':
                valid = true;
                this->breakTime = customTime();
                break;
            
            case 'E':
                valid = true;
                break;
            
            default:
                cout << choice << " is not a valid choice." << endl;
                break;
        }
        cout << endl;
    } while (!valid);

    return;
}

void Pomodoro::selectReps() {
    string input;
    char choice;
    bool valid = false;

    // set this->reps depending on choice
    do {
        // output menu for user choice
        cout << "Please select number of repititions:" << endl;
        cout << "   A) 1 rep" << endl;
        cout << "   B) 2 reps" << endl;
        cout << "   C) 3 reps" << endl;
        cout << "   D) Custom reps" << endl;

        // get user choice
        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        // check if input is a single char
        if (input.size() > 1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }

        choice = input[0];

        switch (choice) {
            case 'A':
                valid = true;
                this->nReps = 1;
                break;

            case 'B':
                valid = true;
                this->nReps = 2;
                break;
            
            case 'C':
                valid = true;
                this->nReps = 3;
                break;

            case 'D':
                valid = true;
                this->nReps = customReps();
                break;
            
            case 'E':
                valid = true;
                break;
            
            default:
                cout << choice << " is not a valid choice." << endl;
                break;
        }
        cout << endl;
    } while (!valid);

    return;
}

/*
Takes user input to grab a user-input integer number of repetitions
*/
int Pomodoro::customReps() {
    int customReps;
    bool valid = false;

    while (!valid) {
        try {

            cout << "Enter a custom number of repititions: ";
            cin >> customReps;

            // check if input is integer
            if (cin.fail()) {
                cout << "That is not a valid input." << endl;
                cin.clear();    // clear error flag
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // flush buffer
                
                continue;
            }

            // double check for characters after parsed int
            if (cin.peek() != '\n') {
                cout << "That is not a valid input." << endl;

                // flush buffer for new input since NaN
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            // if we got this far, input is valid.
            valid = true;

        } catch (out_of_range const&) {
            cout << "catch" << endl;
        }
    }

    // debug: cout << "reps: " << customTime << endl;
    return customReps;
}