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

template<typename Type>                                 // template class
class MiniDB {                                          // DB for storing Type values

private:

    std::list<Type> db_store;                           // uses c++ list data structure
    typename std::list<Type>::iterator currPos;         // uses iterator to determine current position in list

public:
    MiniDB();                                           // constructor
    size_t size() const;                                // number of values in list
    void insert(const Type&);                           // insert at iterator
    void append(const Type&);                           // insert at back of list
    void prev();                                        // iterator moves 1 position to the left
    void next();                                        // iterator moves 1 position to the right
    Type remove();                                      // remove value at iterator
    void moveToFirst();                                 // moves iterator to front of list
    void moveToLast();                                  // moves iterator to end of list
    size_t getCurrentIndex() const;                     // return 0-based position of iterator in list
    void moveToIndex(size_t index);                     // moves iterator to index in list
    const Type& getValue() const;                       // get the value in the list at the iterator
};

template<typename Type>
MiniDB<Type>::MiniDB() {                                // sets the iterator to beginning of list

    currPos = db_store.begin();
}

template<typename Type>
size_t MiniDB<Type>::size() const {

    return db_store.size();
}

template<typename Type>
void MiniDB<Type>::insert(const Type &item) {           // insert value at iterator

        db_store.insert(currPos, item);
        currPos--;                                      // keep pointing at last inserted item
}

template<typename Type>
void MiniDB<Type>::append(const Type &item) {           // insert value at end of list

    db_store.push_back(item);
    currPos = db_store.end();
    --currPos;                                          // keep iterator pointing at last value
}

template<typename Type>
void MiniDB<Type>::prev() {

    if(currPos != db_store.begin()) {                   // if iterator at beginning, throw error, else move left

        --currPos;

    } else {

        throw std::logic_error("Iterator already at beginning of DB or DB empty");
    }
}

template<typename Type>
void MiniDB<Type>::next() {

    if(currPos != db_store.end()) {                     // if iterator at end, throw error, else move right

        ++currPos;

    } else {

        throw std::logic_error("Iterator already at end or DB or DB empty");
    }
}

template<typename Type>
Type MiniDB<Type>::remove() {

    if(db_store.size() != 0) {                              // erase value at iterator. If this was last value, iterator
                                                            // will point to list.end(), so --iterator
        currPos = db_store.erase(currPos);
        currPos = currPos == db_store.end() ? --currPos : currPos;

    } else {                                                // if list empty, throw error

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
size_t MiniDB<Type>::getCurrentIndex() const {              // get current iterator index. Uses a const_iterator (as
                                                            // function is const) and sets it to start of list.
                                                            // increments iterator and index until currentPos iterator reached
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
}

template<typename Type>
void MiniDB<Type>::moveToIndex(size_t index) {          // move iterator to another index

    if(db_store.size() != 0) {

        currPos = db_store.begin();
        std::advance(currPos, index -1);                // To account for 0-based numbering

    } else {

        throw std::logic_error("DB empty");
    }
}

template<typename Type>
const Type& MiniDB<Type>::getValue() const {

    if(db_store.size() != 0) {

        return *currPos;                                // returns value at iterator

    } else {

        throw std::logic_error("DB empty");
    }
}

#endif //COMP5421_ADVANCED_PROGRAMMING_ASSIGNMENT_3_MINIDB_H
