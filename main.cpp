#include "user.hpp"
#include "pomodoro.hpp"
#include "timer.hpp"

#include <string>

using namespace std;

int main(){
    string filename = "test2.bin";
    User testUser;
    testUser.startMenu( filename );
    testUser.timerMenu();

    testUser.save( filename );
    return 0;
}