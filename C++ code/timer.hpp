#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <thread>
#include <string>

using namespace std;

class Timer {
    private:
        int focusTime; // goal focus time in SECONDS
        bool done;  // flag for if timer finishes or not
    public:
        //constructors
        Timer();

        //setters
        void setFocusTime(int tFocus);
        void setDone(bool flag);

        //getters
        int getFocusTime();
        bool isDone();

        //functions
        bool confirm();
        void display();
        bool run();

        void selectFocusTime(); // let user select a focus time for timer
        int customTime();      // allow user to set a custom time
};

#endif //TIMER_H