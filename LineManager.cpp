//
// Created by Oz on 7/4/2020.
//

#include "LineManager.h"
#include <iostream>

LineManager::LineManager(std::size_t upper_span, std::size_t lower_span) :
        upper_span{upper_span}, lower_span{lower_span} {

    makeMenus();
};

void LineManager::makeMenus() {

    partialMenu.set_top_message("Choose one of the following options");
    fullMenu.set_top_message("Choose one of the following options");
    partialMenu.set_bottom_message("Enter an option number");
    fullMenu.set_bottom_message("Enter an option number");

    partialMenu.push_back("Append input from the keyboard");
    fullMenu.push_back("Append input from the keyboard");
    partialMenu.push_back("Insert input from the keyboard");
    fullMenu.push_back("Insert input from the keyboard");
    partialMenu.push_back("Append input from text file");
    fullMenu.push_back("Append input from text file");
    partialMenu.push_back("Insert input from text file");
    fullMenu.push_back("Insert input from text file");
    partialMenu.push_back("Quit");
    fullMenu.push_back("Quit");
    fullMenu.push_back("Print a span of lines around the current position");
    fullMenu.push_back("Set the length of upper or lower line spans");
    fullMenu.push_back("Print all");
    fullMenu.push_back("Move the current line");
    fullMenu.push_back("Delete the current line");
    fullMenu.push_back("Write mini-database to file");
    fullMenu.push_back("Quit");
}

void LineManager::run() {

    for(int i = 0; i < 3; i++) {

        std::cout << fullMenu;
    }

}