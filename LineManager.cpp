/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       7/4/2020, Summer 2020
*/

#include "LineManager.h"


LineManager::LineManager(std::size_t upper_span, std::size_t lower_span) :      // constructor
        upper_span{upper_span}, lower_span{lower_span} {

    changeSinceWrite = false;
    makeMenus();
};

void LineManager::makeMenus() {

    partialMenu.set_top_message     ("Choose one of the following options");    // set top and bottom messages
    fullMenu.set_top_message        ("Choose one of the following options");
    partialMenu.set_bottom_message  ("Enter an option number");
    fullMenu.set_bottom_message     ("Enter an option number");

    partialMenu.push_back           ("Append input from the keyboard");         // sets the options 1-12 in the menus
    fullMenu.push_back              ("Append input from the keyboard");
    partialMenu.push_back           ("Insert input from the keyboard");
    fullMenu.push_back              ("Insert input from the keyboard");
    partialMenu.push_back           ("Append input from text file");
    fullMenu.push_back              ("Append input from text file");
    partialMenu.push_back           ("Insert input from text file");
    fullMenu.push_back              ("Insert input from text file");
    partialMenu.push_back           ("Quit");
    fullMenu.push_back              ("Print the current line");
    fullMenu.push_back              ("Print a span of lines around the current position");
    fullMenu.push_back              ("Set the length of upper or lower line spans");
    fullMenu.push_back              ("Print all");
    fullMenu.push_back              ("Move the current line");
    fullMenu.push_back              ("Delete the current line");
    fullMenu.push_back              ("Write mini-database to file");
    fullMenu.push_back              ("Quit");
}

void LineManager::opt1AppKeyB() {                            // option 1: Append input from the keyboard

    std::string input{""};                                // for user input
    int strNumber{1};                                       // for numbering user input

    std::cout << "To end input, enter a single "
                 "dot and press enter" << std::endl;

    while (input.compare(".") != 0) {                     // while user input is not "."

        std::cout << strNumber++ << "-> ";                  // display user input string number, get input
        getline(std::cin,input);

        miniDB.append(input);                               // add input to DB

        changeSinceWrite = true;                            // for option 12 (write before quitting)
    }

    miniDB.remove();                                        // removes final "." in DB
}

void LineManager::opt2InpKeyB() {                           // option 2: Insert input from the keyboard

    std::string input{""};
    int strNumber{1};

    std::cout << "To end input, enter a single "
                 "dot and press enter" << std::endl;

    while(input.compare(".") != 0) {

        std::cout << strNumber++ << "-> ";
        std::getline(std::cin, input);

        miniDB.insert(input);
        miniDB.next();                                  // advances iterator forward to ensure insert is in right order

        changeSinceWrite = true;
    }

    miniDB.prev();                                      // for iterator to point to last inserted value
    miniDB.remove();                                    // remove last "."
}

void LineManager::opt3AppTextF() {                          // option 2: Append input from text file

    std::string fileName;                                   // file name of file
    std::string line;                                       // contains information on a line

    std::cout << "Enter input filename: " << std::endl;     // prompts user for filename
    std::cin >> fileName;
    std::ifstream file (fileName);                          // for file input

    if(file.is_open()) {                                    // if the file is open

        while(getline(file,line)) {                   // get line and append to DB

            miniDB.append(line);

            changeSinceWrite = true;
        }

        file.close();                                       // close file once done

    } else {

        std::cout << "file not found" << std::endl;         // display message if file not found
    }
}

void LineManager::opt4InpTextF() {                          // option 4 : Insert input from text file

    std::string fileName;
    std::string line;

    std::cout << "Enter input filename: " << std::endl;
    std::cin >> fileName;
    std::ifstream file (fileName);

    if(file.is_open()) {

        while(getline(file,line)) {

            miniDB.insert(line);
            miniDB.next();                             // advances iterator forward to ensure insert is in right order
            changeSinceWrite = true;
        }

        miniDB.prev();                                 // for iterator to point to last inserted value
        file.close();

    } else {

        std::cout << "file not found" << std::endl;
    }
}

void LineManager::opt5PrintCurrLine(){                  // option 5: Print the current line

    std::cout << miniDB.getValue() << std::endl;
}

void LineManager::opt6PrintSpan() {                     // option 6: Print a span of lines around the current position

    int currInd = miniDB.getCurrentIndex() + 1;         // +1 To account for 0-based numbering
    int beginInd = currInd - upper_span;                // how high to start
    int finalInd = currInd + lower_span;                // how low to go

    if(beginInd <= 0) {                                 // if starting at <= 0, display BOF message

        std::cout << "**:   BOF" << std::endl;
    }

    for (int i = beginInd; i <= finalInd; ++i) {

        if (i <= 0 || i > miniDB.size())                // continue if index above or below DB valid indices
            continue;

        miniDB.moveToIndex(i);                          // if valid index, move DB to that index and print the value
        std::cout << " " << i << ":   " << miniDB.getValue() << std::endl;
    }

    if (finalInd > miniDB.size()) {                     // in index too large, display EOF message

        std::cout << "**:   EOF" << std::endl;
    }
}

void LineManager::opt7SetSpans() {                      // option 7: Set the length of upper or lower line spans

    int currInd = miniDB.getCurrentIndex() + 1;         // +1 To account for 0-based numbering
    int input;                                          // for user input

    std::cout << "What's the length of the span " << std::endl;
    std::cin >> input;

     if (input < 0) {                                   // if input less than 0 (going up) check distance between
                                                        // current index and first index. If valid, accept. Else display error
         if(abs(input) > currInd-1) {

             std::cout << "That's a large span of lines. "
                          "Max is " << (currInd-1) << std::endl;

         } else {

             upper_span = abs(input);
         }

    } else if (input > 0) {                             // if input greater than 0 (going down) check distance between
                                                        // current index and last index. If valid, accept. Else display error

        if(input > miniDB.size() - currInd) {

            std::cout << "That's a large span of lines. Max is " << (miniDB.size() - currInd) << std::endl;

        } else {

            lower_span = input;
        }

    } else {                                            // input is 0, set both spans to 0

        upper_span = lower_span = 0;
    }
}

void LineManager::opt8PrintAll() {                      // option 8: Print all

    for(int i = 1; i <= miniDB.size(); ++i) {

        miniDB.moveToIndex(i);
        std::cout << " " << i << ":   " << miniDB.getValue() << std::endl;
    }
}

void LineManager::opt9ToLine() {                        // option 9: Move the current line

    int input;

    std::cout << "Which line to move to?" << std::endl;
    std::cin >> input;

    if(input < 1 || input > miniDB.size()) {            // check for valid user input

        std::cout << "Can't move there";

    } else {

        miniDB.moveToIndex(input);
    }
}

void LineManager::opt10DeleteLine() {                   // option 10: Delete the current line

    std::cout << "removing the current line ..." << std::endl;
    miniDB.remove();

    changeSinceWrite = true;
}

void LineManager::opt11WriteToFile() {                  // option 11: Write mini-database to file

    std::string fileName;

    std::cout << "Enter the output filename: " << std::endl;
    std::cin >> fileName;

    std::ofstream outputFile{fileName};                 // output file stream

    if(outputFile.is_open()) {                          // if file open, output to file

        for(int i = 1; i <= miniDB.size(); ++i) {

            miniDB.moveToIndex(i);
            outputFile << " " << i << ":   " << miniDB.getValue() << std::endl;
        }

        changeSinceWrite = false;
    }
}

void LineManager::opt12Quit() {                         // option 12: quit

    std::string choice;                                 // for user input (save to DB or not)

    if(changeSinceWrite) {                              // if DB changed since last write to file

        std::cout << "Do you want to save changes to a file? (yes or no)" << std::endl;
        std::cin >> choice;

        if(choice.substr(0,1).compare("y") == 0 || choice.substr(0,1).compare("Y") == 0) {

            opt11WriteToFile();
        }
    }

    std::cout << "goodbye";
}

void LineManager::run() {                               // function that keeps looping to get menu selections from user

    int input;

    while (input != 12) {                               // keep looping until user selects 12

        if(miniDB.size() == 0) {                        // if DB empty, display small menu, else display large menu

            std::cout << partialMenu;

        } else {

            std::cout << fullMenu;
        }

        std::cin >> input;                              // get user input
        std::cin.ignore();                              // flush cin buffer (otherwise user input may be skipped)

        switch (input) {                                // switch over the input, go to appropriate function

            case 1:
                opt1AppKeyB();
                break;
            case 2:
                opt2InpKeyB();
                break;
            case 3:
                opt3AppTextF();
                break;
            case 4:
                opt4InpTextF();
                break;
            case 5:
                opt5PrintCurrLine();
                break;
            case 6:
                opt6PrintSpan();
                break;
            case 7:
                opt7SetSpans();
                break;
            case 8:
                opt8PrintAll();
                break;
            case 9:
                opt9ToLine();
                break;
            case 10:
                opt10DeleteLine();
                break;
            case 11:
                opt11WriteToFile();
                break;
            case 12:
                opt12Quit();
                break;
        }
    }

}



