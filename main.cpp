#include "user.hpp"
#include "pomodoro.hpp"
#include "timer.hpp"

#include <string>

using namespace std;

int main(){
    string filename = "userdata.bin";
    User testUser;
    testUser.startMenu( filename );
    testUser.adminMenu( filename );
    testUser.timerMenu();

    testUser.save( filename );

    cout << "===========================" << endl;
    cout << "    See you next time!     " << endl;
    cout << "===========================" << endl;
    cout << endl;
    return 0;
}