#ifndef POMODORO_H
#define POMODORO_H

#include "timer.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Pomodoro : public Timer {
    private:
        int breakTime;  // amt of pomodoro rest time in seconds
        int nReps;     // number of timer repetitions (1 rep = 1 complete timer not including break)

    public:
        // constructors
        Pomodoro();
        
        // setters
        void setBreakTime(int btime);
        void setReps(int reps);

        // getters
        int getBreakTime();
        int getReps();

        // functions
        bool confirm();
        void displayBreak();
        bool run();

        void selectBreakTime();
        void selectReps();
        int customReps();
};

#endif //POMODORO_H