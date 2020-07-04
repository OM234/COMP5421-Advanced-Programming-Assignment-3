/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       5/14/2020, Summer 2020
*/

#include "Menu.h"
#include <iostream>
#include <cstring> //for strcmp()
#include <string> //exclusively for use of to_string to convert numbers to string (allowed by professor)

using namespace std;

Menu::Menu() {  //default constructor
    this->bottom_message;
    this->top_message;
    this->option_list = new Text[1];
    this->count = 0;
    this->capacity = 1;
}

Menu::Menu(const Menu &mnu) {   //copy constructor
    this->bottom_message = mnu.bottom_message;
    this->top_message = mnu.top_message;
    this->count = mnu.count;
    this->capacity = mnu.capacity;
    this->option_list = new Text[this->capacity];

    for (int i = 0; i < count; i++) {
        this->option_list[i] = mnu.option_list[i];
    }
}

Menu::~Menu() {     // destructor
    delete[] option_list;
}

Menu &Menu::operator=(const Menu &mnu) { //operator = override

    this->bottom_message = mnu.bottom_message;
    this->top_message = mnu.top_message;
    this->count = mnu.count;
    this->capacity = mnu.capacity;
    this->option_list = new Text[this->capacity];

    for (int i = 0; i < count; i++) {
        this->option_list[i] = mnu.option_list[i];
    }

    return *this;
}

void Menu::insert(int index, const Text &option) {  //insert into index

    if (this->count == this->capacity) {  //if full, double the capacity
        double_capacity();
    }

    for (int i = this->count - 1; i >= index - 1; i--) {  //copy values over to the right of index
        this->option_list[i + 1] = this->option_list[i];
    }

    this->option_list[index - 1] = option.getCstring(); //insert value at index
    this->count++;  //increment count
}

void Menu::double_capacity() { //doubles the capacity

    Text *new_option_list{this->option_list};
    this->option_list = new Text[this->capacity * 2]; //new_option_list with twice the capacity

    for (int i = 0; i < this->capacity; i++) { //copy over old values
        this->option_list[i] = new_option_list[i];
    }

    this->capacity = this->capacity * 2; //double the capacity
}

void Menu::insert(int index, const char *option) {

    this->insert(index, Text(option)); //code reuse for insert overloading
}

void Menu::push_back(const Text &option) {

    this->insert(count + 1, option); //code reuse to insert at back of list. Index to insert is count of values
}

void Menu::push_back(const char *option) {

    this->insert(count + 1, option); //code reuse to insert at back of list. Index to insert is count of values
}

void Menu::remove(int index) {

    for (int i = index - 1; i < this->count; i++) {  //shift values to the left of index
        this->option_list[i] = this->option_list[i + 1];
    }

    this->count--;  //decrement count
}

void Menu::pop_back() {

    this->remove(this->count); //code reuse to remove last index value
}

int Menu::getCount() const {

    return this->count;
}

int Menu::getCapacity() const {

    return this->capacity;
}

const Text Menu::getText(int option) const {

    return this->option_list[option - 1];  //return option list
}

const Text Menu::toString() const {

    Text str{}; //return string

    if (strcmp(top_message.getCstring(), "") != 0) //for newline formatting
        str.append("\n");

    str.append(this->top_message); //adds the top message

    for (int i = 0; i < count; i++) { //adds the options
        str.append("\n");
        str.append("\t");
        str.append(std::to_string(i + 1).c_str()); //to convert option number to cstring
        str.append(". ");
        str.append(this->option_list[i]);
    }
    if (strcmp(bottom_message.getCstring(), "") != 0) //for newline formatting
        str.append("\n");
    str.append(this->bottom_message); //adds bottom message
    str.append("\n");

    return str;
}

void Menu::read_option_number() { //for reading user input

    cout << *this;  //display menu

    int choice{};
    cin >> choice;  //get choice

    if (this->count == 0) { //if no options, accept any integer
        cout << "you entered: " << choice << endl;
        return;
    }

    while (choice < 1 || choice > this->count) { //if choice is less than 1, or more than count, invalid
        cout << "invalid choice " << choice << ". It must be in the range"
             << "[1, " << this->count << "]" << endl;
        cout << *this;
        cin >> choice;
    }

    cout << "you entered: " << choice << endl;
}

void Menu::set_top_message(const Text &topMsg) {
    this->top_message = topMsg;
}

void Menu::set_bottom_message(const Text &topMsg) {
    this->bottom_message = topMsg;
}

void Menu::clear_top_message() {
    this->top_message = "";
}

void Menu::clear_bottom_message() {
    this->bottom_message = "";
}

bool Menu::isEmpty() const {
    return (count == 0);
}

std::ostream &operator<<(std::ostream &sout, const Menu &mnu) {  //operator << override
    sout << mnu.toString();
    sout << "?? ";
    return sout;
}
