#ifndef timer_class.hpp
#define timer_class.hpp

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class User {
    private:
        string name; // user's name
        // TODO: history storage mechanism
    public:
        string setName();
        // TODO: setHistory
        //       getHistory
        //       totalTime
};

#endif