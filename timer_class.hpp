#ifndef TIMER_CLASS_H
#define TIMER_CLASS_H

#include <chrono>
#include <iostream>
#include <thread>
#include <string>

using namespace std;

class Timer {
    private:
        int focusTime; // goal focus time in minutes
    public:
        //constructors
        Timer();
        Timer(int tFocus);

        //setters
        void setFocusTime(int tFocus);

        //getters
        int getFocusTime();

        //functions
        void start();
        void stop();
        void cancel(); //note: output amt of time actually focused: focusTime-time remaining on timer

        //destructor
        ~Timer();
};

#endif //TIMER_CLASS_H