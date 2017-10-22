#ifndef _BOUNDED_DEQUEUE_H
#define _BOUNDED_DEQUEUE_H
#include "Dequeue.h"
#include <stdexcept>

namespace dequeue {
template <typename E>
class Bounded_Dequeue : public Dequeue<E> {
public:
Bounded_Dequeue(int size);
~Bounded_Dequeue();

bool is_empty() override;
bool is_full() override;
int length() override;
void clear() override;
void push_front(E data) override;
void push_back(E data) override;
E pop_front() override;
E pop_back() override;
E peek_front() override;
E peek_back() override;

  #ifdef DEBUG
E * to_array() override;
  #endif

private:
E * array;
int size;

int head = 0;
int tail = 0;

//for push_front() and pop_back() operations
int headprime = 0;
int tailprime = 0;

int nextNum(int index);
int prevNum(int index);

};
/*_____________Constructor and Destructor___________________*/
/**
 * Constructor Definition
 * Creates array one bigger than requested size
 */
template <typename E>
Bounded_Dequeue<E>::Bounded_Dequeue(int size){
        this->size = 1 + size;
        array = new E[1+size];
}

/**
 * Destructor Definition
 * Deletes array of data to which array points
 */
template <typename E>
Bounded_Dequeue<E>::~Bounded_Dequeue(){
        delete [] array;
}

/*_____________Operations___________________*/
/**
 * Definition for IsEmpty
 *
 */
template <typename E>
bool Bounded_Dequeue<E>::is_empty(){
        return (head==tail);
}

/**
 * Definition for is_full
 *
 */
template <typename E>
bool Bounded_Dequeue<E>::is_full(){
        return (head==nextNum(tail));
}

/**
 * Definition for length
 *
 */
template <typename E>
int Bounded_Dequeue<E>::length(){
        if((tail-head) <= 0 ) {
                return (tail-head);
        }
        else{
                return (head-tail);
        }
}

/**
 * Definition for clear
 *
 */
template <typename E>
void Bounded_Dequeue<E>::clear(){
        tail = 0;
        head = 0;
        tailprime = 0;
        headprime = 0;
}

/**
 * Definition for push_front
 *
 */
template <typename E>
void Bounded_Dequeue<E>::push_front(E data){
        if (is_full()) {
                throw std::runtime_error("Cannot enqueue: full dequeue");
        }
        tail = data;
        tail = nextNum(tail);
        headprime = prevNum(tail);
}



/**
 * Definition for push_back
 *
 */
template <typename E>
void Bounded_Dequeue<E>::push_back(E data){
        if (is_full()) {
                throw std::runtime_error("Cannot enqueue: full dequeue");
        }
        tailprime = data;
        tailprime = prevNum(tail);
        head = nextNum(tail);
}


/**
 * Definition for pop_front
 *
 */
template <typename E>
E Bounded_Dequeue<E>::pop_front(){
        if (is_empty()) {
                throw std::runtime_error("Cannot pop: empty dequeue");
        }
        E* element = head;
        head = nextNum(head);
        tailprime = prevNum(head);
        return *element;
}



/**
 * Definition for pop_back
 *
 */
template <typename E>
E Bounded_Dequeue<E>::pop_back(){
        if (is_empty()) {
                throw std::runtime_error("Cannot pop: empty dequeue");
        }
        E* element = headprime;
        headprime = prevNum(headprime);
        tail = nextNum(headprime);
        return *element;
}

/**
 * Definition for peek_front
 *
 */
template <typename E>
E Bounded_Dequeue<E>::peek_front(){
        if (is_empty()) {
                throw std::runtime_error("Cannot peek: empty dequeue");
        }
        E* element = head;
        return *element;
}


/**
 * Definition for peek_back
 *
 */
template <typename E>
E Bounded_Dequeue<E>::peek_back(){
        if (is_empty()) {
                throw std::runtime_error("Cannot peek: empty dequeue");
        }
        E* element = headprime;
        return *element;
}

#ifdef DEBUG
E* Bounded_Dequeue<E>::to_array(){
        int length = length();
        E* data = new E[length];

        E* contents = data;
        E* arraydata = head;
        for ( int i = 0; i != len; ++i ) {
                *contents = *arraydata;
                ++contents;
                arraydata = nextNum(arraydata);
        }
        return contents;
}

#endif

/*_____________Helper Functions___________________*/
/**
 *  Definition for nextNum
 * Needed for incrementation safeley
 */
template <typename E>
int Bounded_Dequeue<E>::nextNum(int index){
        index++;
        if(index == (array + size)) {
                index = array;
        }
        return index;
}


/**
 *  Definition for Prevnum
 * Needed for incrementing safely
 */
template <typename E>
int Bounded_Dequeue<E>::prevNum(int index){
        if(index == array) {
                index = array + size;
                index--;
                return index;
        }
        else{
                --index;
                return index;
        }
}
}
 #endif
