#ifndef POMODORO_CLASS_H
#define POMODORO_CLASS_H

#include "timer_class.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Pomodoro : public Timer {
    private:
        int breakTime;  // amt of pomodoro rest time
        int numRep;     // # of timer repetitions (1 rep = 1 complete timer not including break)

    public:
        
};

#endif //POMODORO_CLASS_H