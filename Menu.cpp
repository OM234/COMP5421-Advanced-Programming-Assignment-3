/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       7/4/2020, Summer 2020
*/

#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

Menu::Menu() {}                                                 //default constructor


const std::string Menu::toString() const {                      // used to help implement << override

    std::string returnString{};                                 // return string

    returnString.append(this->top_message);                     // appends the top message

    for (int i = 0; i < option_list.size(); i++) {              // appends the options

        returnString.append("\n");
        returnString.append("\t");
        returnString.append(std::to_string(i + 1));
        returnString.append(". ");
        returnString.append(this->option_list[i]);
    }

    returnString.append("\n");
    returnString.append(this->bottom_message);                  // appends bottom message
    returnString.append("\n");

    return returnString;
}

void Menu::push_back(const std::string& str) {                  // push to back of menu

    option_list.push_back(str);
}

void Menu::set_top_message(const std::string &topMsg) {

    this->top_message = topMsg;
}

void Menu::set_bottom_message(const std::string &topMsg) {

    this->bottom_message = topMsg;
}

void Menu::clear_top_message() {

    this->top_message = "";
}

void Menu::clear_bottom_message() {

    this->bottom_message = "";
}

std::ostream &operator<<(std::ostream &sout, const Menu &menu) {  //operator << override

    sout << menu.toString();
    sout << "?? ";
    return sout;
}
