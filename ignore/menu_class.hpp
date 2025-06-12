#ifndef MENU_CLASS_H
#define MENU_CLASS_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Menu {
    private:
        string prompt;
        vector<string> optionList;
    public:
        //constructors
        Menu();
        Menu(string p);
        Menu(string p, vector<string> list);

        //setters
        void setPrompt(string p);
        void setOptionList(vector<string> list);


        //getters
        int getNumOptions();
        string getPrompt();
        vector<string> getOptionList();

        //functions
        void addOption(string option); // must also increment numOptions by 1
        void print(); // print out menu
        int getChoice(); // get user choice & validate
};

#endif //MENU_CLASS_H