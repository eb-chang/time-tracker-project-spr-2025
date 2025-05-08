#include "timer.hpp"
#include <iomanip>
#include <climits>

using namespace std;

// === constructors === //

Timer::Timer() {
    focusTime = 0;
    done = false;
}

// === setters === //
void Timer::setDone(bool flag) {
    done = flag;
}

void Timer::setFocusTime(int tFocus) {
    focusTime = tFocus;
}

// === getters === //

bool Timer::isDone() {
    return done;
}

int Timer::getFocusTime() {
    return focusTime;
}

// === functions === //
bool Timer::confirm() {
    string input;
    char choice;

    int minutes = focusTime/60;
    int seconds = focusTime%60;
    cout << "Would you like to start a timer for " << minutes << " min " << seconds << "s?" << endl;
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

void Timer::display() {
    for (int i = this->focusTime; i >= 0; --i) {
        // update minutes and seconds for display
        int minutes = i / 60;
        int seconds = i % 60;

        // display timer on console.
        cout << "\rTime remaining: " 
        << setw(2) << setfill('0') << minutes << ":" // minutes left
        << setw(2) << setfill('0') << seconds        // seconds left
        << flush;                                    // flush output

        // sleep for 1 second, then update.
        this_thread::sleep_for(std::chrono::seconds(1));  
    }

    // extra spaces to overwrite time remaining text
    cout << "\rTime's up!           " << endl;
    done = true;
}

bool Timer::run() {
    // reset done flag
    done = false;

    selectFocusTime();
    if (!confirm()) {
        return done;
    }
    display();
    return done;
}

void Timer::selectFocusTime() {
    string input;
    char choice;
    bool valid = false;

    // set this->focusTime in seconds depending on choice
    do {
        // output menu for user choice
        cout << "Please select an amount of time to focus:" << endl;
        cout << "   A) 15 minutes" << endl;
        cout << "   B) 30 minutes" << endl;
        cout << "   C) 45 minutes" << endl;
        cout << "   D) Custom focus time" << endl;
        cout << "   E) Quit" << endl;

        // get user choice
        cin >> input;
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        // check if input is a single char
        if (input.size() >1) {
            cout << input << " is not a valid choice." << endl;
            continue;
        }

        choice = input[0];
    
        switch (choice) {
            case 'A':
                valid = true;
                this->focusTime = 900;
                break;
            
            case 'B':
                valid = true;
                this->focusTime = 1800;
                break;

            case 'C':
                valid = true;
                this->focusTime = 2700;
                break;

            case 'D':
                valid = true;
                this->focusTime = customTime();
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

// returns a user-input custom time in seconds
int Timer::customTime() {
    int customTime;
    bool valid = false;

    while (!valid) {
        try {

            cout << "Enter a custom time in seconds: ";
            cin >> customTime;

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

    // debug: cout << "time: " << customTime << endl;
    return customTime;
}