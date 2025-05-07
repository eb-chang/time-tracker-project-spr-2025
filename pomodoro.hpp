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
        Pomodoro(int ftime, int btime, int reps);
        
        // setters
        void setBreakTime(int btime);
        void setReps(int reps);

        // getters
        int getBreakTime();
        int getReps();

        // functions
        void selectBreakTime();
};

#endif //POMODORO_H