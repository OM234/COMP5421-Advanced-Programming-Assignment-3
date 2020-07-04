/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       7/4/2020, Summer 2020
*/

#ifndef COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_LINEMANAGER_H
#define COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_LINEMANAGER_H


#include <cstddef>
#include "Menu.h"

class LineManager {

private:
    std::size_t upper_span;
    std::size_t lower_span;
    Menu partialMenu;
    Menu fullMenu;

    void makeMenus();

public:
    LineManager(std::size_t upper_span = 2, std::size_t lower_span = 2);
    void run();

};


#endif //COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_LINEMANAGER_H
