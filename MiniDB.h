/*
    Author:     Osman Momoh
    Student ID: 26220150
    Course:     COMP 5421: Advanced Programming
    Date:       7/4/2020, Summer 2020
*/

#ifndef COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_MINIDB_H
#define COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_MINIDB_H

#include <list>
#include <stdexcept>

template<typename Type>
class MiniDB {

public:  //TODO: make private
    std::list<Type> db_store;
    typename std::list<Type>::iterator currPos;

public:
    MiniDB();
    size_t size() const;
    void insert(const Type&);
    void append(const Type&);
    void prev();
    void next();
    Type remove();
    void moveToFirst();
    void moveToLast();
    size_t getCurrentIndex() const;
    void moveToIndex(size_t index);
    const Type& getValue() const;

};

template<typename Type>
MiniDB<Type>::MiniDB() {

    currPos = db_store.begin();
}

template<typename Type>
size_t MiniDB<Type>::size() const {

    return db_store.size();
}

template<typename Type>
void MiniDB<Type>::insert(const Type &item) {

//    currPos++;
//    if(this->size() == 0)
//        db_store.insert(currPos++, item);
//    else
        db_store.insert(currPos, item);
        currPos--;
//
//    for(typename std::list<Type>::iterator a {db_store.begin()}; a != db_store.end(); a++) {
//        std::cout<< *a << std::endl;
//    }
//    std::cout<< std::endl;
}

template<typename Type>
void MiniDB<Type>::append(const Type &item) {

    db_store.push_back(item);
    currPos = db_store.end();
    --currPos;
}

template<typename Type>
void MiniDB<Type>::prev() {

    if(currPos != db_store.begin()) {
        --currPos;
    } else {
        throw std::logic_error("Iterator already at beginning of DB or DB empty");
    }
}

template<typename Type>
void MiniDB<Type>::next() {

    if(currPos != db_store.end()) {
        ++currPos;
    } else {
        throw std::logic_error("Iterator already at end or DB or DB empty");
    }
}

template<typename Type>
Type MiniDB<Type>::remove() {

    if(db_store.size() != 0) {

        currPos = db_store.erase(currPos);
        currPos = currPos == db_store.end() ? --currPos : currPos;
    } else {

        throw std::logic_error("DB empty");
    }

    return *currPos;
}

template<typename Type>
void MiniDB<Type>::moveToFirst() {

    if(db_store.size() != 0) {

        currPos = db_store.begin();

    } else {

        throw std::logic_error("DB empty");
    }
}

template<typename Type>
void MiniDB<Type>::moveToLast() {

    if(db_store.size() != 0) {

        currPos = db_store.end();
        --currPos;

    } else {

        throw std::logic_error("DB empty");
    }
}

template<typename Type>
size_t MiniDB<Type>::getCurrentIndex() const {

    int index = 0;

    typename std::list<Type>::const_iterator begin{db_store.begin()};

    if(db_store.size() != 0) {

        while (begin != currPos) {

            index++;
            begin++;
        }
    } else {

        throw std::logic_error("DB empty");
    }


    return index;

////    if(db_store.size() != 0) {
////
////        return distance(begin, currPos);
//
//    } else {
//
//        throw std::logic_error("DB empty");
//    }
}

template<typename Type>
void MiniDB<Type>::moveToIndex(size_t index) {

    if(db_store.size() != 0) {

        currPos = db_store.begin();
        std::advance(currPos, index -1);//To account for 0-based numbering

    } else {

        throw std::logic_error("DB empty");
    }
}

template<typename Type>
const Type& MiniDB<Type>::getValue() const {

    if(db_store.size() != 0) {

        //std::cout << "returning value" << std::endl << *currPos << std::endl;
        return *currPos;

    } else {

        throw std::logic_error("DB empty");
    }
}

#endif //COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_MINIDB_H
