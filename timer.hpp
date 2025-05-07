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
    public:
        //constructors
        Timer();
        Timer(int tFocus);

        //setters
        void setFocusTime(int tFocus);

        //getters
        int getFocusTime();

        //functions
        void displayTimer();    
        void selectFocusTime(); // let user select a focus time for timer
        int customTime();      // allow user to set a custom time
        void start();
        void stop();
        void cancel(); //note: output amt of time actually focused: focusTime-time remaining on timer

        //destructor
        //~Timer();
};

#endif //TIMER_H