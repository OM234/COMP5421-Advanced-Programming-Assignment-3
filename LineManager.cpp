/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       7/4/2020, Summer 2020
*/

#include "LineManager.h"


LineManager::LineManager(std::size_t upper_span, std::size_t lower_span) :
        upper_span{upper_span}, lower_span{lower_span} {

    changeSinceWrite = false;
    makeMenus();
};

void LineManager::makeMenus() {

    partialMenu.set_top_message     ("Choose one of the following options");
    fullMenu.set_top_message        ("Choose one of the following options");
    partialMenu.set_bottom_message  ("Enter an option number");
    fullMenu.set_bottom_message     ("Enter an option number");

    partialMenu.push_back           ("Append input from the keyboard");
    fullMenu.push_back              ("Append input from the keyboard");
    partialMenu.push_back           ("Insert input from the keyboard");
    fullMenu.push_back              ("Insert input from the keyboard");
    partialMenu.push_back           ("Append input from text file");
    fullMenu.push_back              ("Append input from text file");
    partialMenu.push_back           ("Insert input from text file");
    fullMenu.push_back              ("Insert input from text file");
    partialMenu.push_back           ("Quit");
    fullMenu.push_back              ("Quit");
    fullMenu.push_back              ("Print a span of lines around the current position");
    fullMenu.push_back              ("Set the length of upper or lower line spans");
    fullMenu.push_back              ("Print all");
    fullMenu.push_back              ("Move the current line");
    fullMenu.push_back              ("Delete the current line");
    fullMenu.push_back              ("Write mini-database to file");
    fullMenu.push_back              ("Quit");
}

void LineManager::opt1AppKeyB() {

    std::string input{""};
    int strNumber{1};

    std::cout << "To end input, enter a single dot and press enter" << std::endl;

    while(input.compare(".") != 0) {

        std::cout << strNumber++ << "-> ";
        std::cin >> input;

        if(input.compare("." ) != 0) //TODO: inelegant
            miniDB.append(input);

        changeSinceWrite = true;
    }
}

void LineManager::opt2InpKeyB() {

    std::string input{""};
    int strNumber{1};

    std::cout << "To end input, enter a single dot and press enter" << std::endl;
    std::cin.ignore(); //flush cin buffer

    while(input.compare(".") != 0) {

        std::cout << strNumber++ << "-> ";
        std::getline(std::cin, input);
        //std::cin >> input;

        if(input.compare("." ) != 0) //TODO: inelegant
        {
            miniDB.insert(input);
            miniDB.next();
        }

        changeSinceWrite = true;
    }
    miniDB.prev();
}

void LineManager::opt3AppTextF() {

    std::string fileName;
    std::string line;

    std::cout << "Enter input filename: " << std::endl;
    std::cin >> fileName;
    std::ifstream file (fileName);

    if(file.is_open()) {

        while(getline(file,line)) {

            miniDB.append(line);

            changeSinceWrite = true;
        }
        file.close();

    } else {

        std::cout << "file not found";
    }
}

void LineManager::opt4InpTextF() {

    std::string fileName;
    std::string line;

    std::cout << "Enter input filename: " << std::endl;
    std::cin >> fileName;
    std::ifstream file (fileName);

    if(file.is_open()) {

        while(getline(file,line)) {

            miniDB.insert(line);
            miniDB.next();
            changeSinceWrite = true;
        }
        miniDB.prev();
        file.close();

    } else {

        std::cout << "file not found" << std::endl;
    }
}

void LineManager::opt5PrintCurrLine(){

    std::cout << miniDB.getValue() << std::endl;
}

void LineManager::opt6PrintSpan() {

    int currInd = miniDB.getCurrentIndex() + 1;         //To account for 0-based numbering
    int beginInd = currInd - upper_span;
    int finalInd = currInd + lower_span;

    if(beginInd <= 0) {
        std::cout << "**:   BOF" << std::endl;
    }

    for (int i = beginInd; i <= finalInd; ++i) {

        if (i <= 0 || i > miniDB.size())
            continue;
        miniDB.moveToIndex(i);
        std::cout << " " << i << ":   " << miniDB.getValue() << std::endl;
    }

    if (finalInd > miniDB.size()) {

        std::cout << "**:   EOF" << std::endl;
    }
}

void LineManager::opt7SetSpans() {

    int currInd = miniDB.getCurrentIndex() + 1;         //To account for 0-based numbering
    int input;

    std::cout << "What's the length of the span " << std::endl;
    std::cin >> input;

     if (input < 0) {

         if(abs(input) > currInd-1) {
             std::cout << "That's a large span of lines. Max is " << (currInd-1) << std::endl;
         } else {
             upper_span = abs(input);
         }

    } else if (input > 0) {

        if(input > miniDB.size() - currInd) {
            std::cout << "That's a large span of lines. Max is " << (miniDB.size() - currInd) << std::endl;
        } else {
            lower_span = input;
        }

    } else {                                //input is 0

        upper_span = lower_span = 0;
    }
}

void LineManager::opt8PrintAll() {

    for(int i = 1; i <= miniDB.size(); ++i) {

        miniDB.moveToIndex(i);
        std::cout << " " << i << ":   " << miniDB.getValue() << std::endl;
    }
}

void LineManager::opt9ToLine() {

    int input;

    std::cout << "Which line to move to?" << std::endl;
    std::cin >> input;

    if(input < 1 || input > miniDB.size()) {

        std::cout << "Can't move there";

    } else {

        miniDB.moveToIndex(input);
    }
}

void LineManager::opt10DeleteLine() {

    std::cout << "removing the current line ..." << std::endl;
    miniDB.remove();

    changeSinceWrite = true;
}

void LineManager::opt11WriteToFile() {

    std::string fileName;

    std::cout << "Enter the output filename: " << std::endl;
    std::cin >> fileName;

    std::ofstream outputFile{fileName};

    if(outputFile.is_open()) {

        for(int i = 1; i <= miniDB.size(); ++i) {

            miniDB.moveToIndex(i);
            outputFile << " " << i << ":   " << miniDB.getValue() << std::endl;
        }

        changeSinceWrite = false;
    }
}

void LineManager::opt12Quit() {

    std::string choice;

    if(changeSinceWrite) {

        std::cout << "Do you want to save changes to a file? (yes or no)" << std::endl;
        std::cin >> choice;

        if(choice.substr(0,1).compare("y") == 0 || choice.substr(0,1).compare("Y") == 0) {
            opt11WriteToFile();
        }
    }

    std::cout << "goodbye";
}

void LineManager::run() {

    int input;

    while (input != 12) {

        if(miniDB.size() == 0) {

            std::cout << partialMenu;

        } else {

            std::cout << fullMenu;
        }

        std::cin >> input;

        switch (input) {

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



