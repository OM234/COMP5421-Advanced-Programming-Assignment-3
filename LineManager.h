/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       7/4/2020, Summer 2020
*/

#ifndef COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_LINEMANAGER_H
#define COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_LINEMANAGER_H


#include <cstddef>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "MiniDB.h"

class LineManager {

private:
    std::size_t upper_span;
    std::size_t lower_span;
    Menu partialMenu;
    Menu fullMenu;
    MiniDB<std::string> miniDB;
    bool changeSinceWrite;
    void makeMenus();
    void opt1AppKeyB();
    void opt2InpKeyB();
    void opt3AppTextF();
    void opt4InpTextF();
    void opt5PrintCurrLine();
    void opt6PrintSpan();
    void opt7SetSpans();
    void opt8PrintAll();
    void opt9ToLine();
    void opt10DeleteLine();
    void opt11WriteToFile();
    void opt12Quit();

public:
    LineManager(std::size_t upper_span = 2, std::size_t lower_span = 2);
    void run();

};


#endif //COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_LINEMANAGER_H
