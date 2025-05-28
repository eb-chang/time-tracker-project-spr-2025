#include "menu_class.hpp"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//constructors
Menu::Menu() {
    string prompt = "";
    optionList = {""};
}

Menu::Menu(string p) {
    prompt = p;
}

Menu::Menu(string p, vector<string> list) {
    prompt = p;
    optionList = list;
}

//setters
void Menu::setPrompt(string p) {
    prompt = p;
}

void Menu::setOptionList(vector<string> list) {
    optionList = list;
}

//getters
string Menu::getPrompt() {
    return prompt;
}

vector<string> Menu::getOptionList() {
    return optionList;
}

//functions
void Menu::addOption(string option) {
    optionList.push_back(option);
}

void Menu::print() {
    cout << prompt << endl;
    for (int i = 0; i < optionList.size(); i++) {
        cout << i+1 << ": " << optionList[i] << endl;
    }
}

// TODO: have better error handling; maybe throw-catch?
int Menu::getChoice() {
    int choice;
   
    do {
        cout << "Enter choice: ";
        cin >> choice;

        if (choice <= optionList.size() && choice >= 0) {
            return choice;
        } else {
            cout << "Invalid choice." << endl;
        }
    } while (choice > optionList.size() || choice < 0);
    return 0;
}
