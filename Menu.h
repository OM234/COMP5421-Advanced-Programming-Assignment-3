/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       5/14/2020, Summer 2020
*/

#ifndef COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_1_MENU_H
#define COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_1_MENU_H
#include "Text.h"


class Menu
{
private:
	
	Text* option_list;
	int capacity;
	int count;
	Text top_message;
	Text bottom_message;
	void double_capacity();

public:
	
	Menu();
	Menu(const Menu&);
	virtual ~Menu();
	Menu& operator=(const Menu&);
	void insert(int, const Text&); //added const to &Text parameter
	void insert(int, const char*);
	void push_back(const char*);
	void push_back(const Text&);
	void remove(int);
	void pop_back();
	int getCount() const; //replaces size()
	int getCapacity() const;
	const Text getText(int) const; // replaces get()
	const Text toString() const;
	void read_option_number(); //made void to facilitate demo
	void set_top_message (const Text&);
	void set_bottom_message(const Text&);
	void clear_top_message();
	void clear_bottom_message();
	bool isEmpty() const;
};

std::ostream& operator<<(std::ostream&, const Menu&); //operator << override

#endif //COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_1_MENU_H
