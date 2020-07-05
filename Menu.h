/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       7/4/2020, Summer 2020
*/
#ifndef COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_MENU_H
#define COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_MENU_H


#include <string>
#include <vector>

class Menu {                                        // Menu class for displaying menu. Similar to Ass. 1 but with less
                                                    // functionality. Uses std::string rather Text. Uses vector<> rather
                                                    // than Text*
private:

    std::vector<std::string> option_list;           // The numbered options in the menu
    std::string top_message;
    std::string bottom_message;

public:

    Menu();                                         // same functionality as assignment 1, just different data types/
                                                    // structures. Reading user input is moved from Menu to LineManager run()
    void insert(int, const std::string&);
    void remove(int);
    void pop_back();
    void push_back(const std::string&);
    const std::string getText(int) const;
    const std::string toString() const;
    void read_option_number();
    void set_top_message (const std::string&);
    void set_bottom_message(const std::string&);
    void clear_top_message();
    void clear_bottom_message();
    bool isEmpty() const;
};

std::ostream& operator << (std::ostream& sout, const Menu& menu);

#endif //COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_MENU_H
