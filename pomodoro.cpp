#include "pomodoro.hpp"

using namespace std;

// === constructors === //

Pomodoro::Pomodoro() {
    setFocusTime(0);
    this->breakTime = 0;
    this->nReps = 0;
}

Pomodoro::Pomodoro(int ftime, int btime, int reps) {
    setFocusTime(ftime);
    this->breakTime = btime;
    this->nReps = reps;
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
        cout << "   D) Custom focus time";
        cout << "   E) Quit" << endl;

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