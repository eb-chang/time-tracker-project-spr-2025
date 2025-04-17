#include "menu_class.hpp"

#include <string>

using namespace std;

int main(){
    Menu startMenu("Welcome! Please select an option:");
    startMenu.addOption("Log-in");
    startMenu.addOption("Sign-up");

    startMenu.print();
    int choice;
    choice = startMenu.getChoice();
    cout << choice;
}