#include "timer_class.hpp"

//constructors
Timer::Timer() {
    focusTime = 0;
}

Timer::Timer(int tFocus) {
    focusTime = tFocus;
}

//setters
void Timer::setFocusTime(int tFocus) {
    focusTime = tFocus;
}

//getters
int Timer::getFocusTime() {
    return focusTime;
}

//functions