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
    std::size_t upper_span;             // upper span when printing span
    std::size_t lower_span;             // lower span when printing span
    Menu partialMenu;                   // small menu when DB is empty. Uses Menu.h
    Menu fullMenu;                      // full menu when DB is not empty. Uses Menu.h
    MiniDB<std::string> miniDB;         // DB for storing std::strings. Uses MiniDB.h
    bool changeSinceWrite;              // true if DB changed since write to file, false otherwise
    void makeMenus();                   // make the small and full menus at startup
    void opt1AppKeyB();                 // Methods to handle user input for menu options (1-12)
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
    LineManager(std::size_t upper_span = 2, std::size_t lower_span = 2);   // constructor, sets upper/lower spans
    void run();                                                            // for running program
};

#endif //COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_LINEMANAGER_H
