//
// Created by Jad Zeineddine on 9/18/17.
//

#ifndef PROJECT1CLION_PSLL_H
#define PROJECT1CLION_PSLL_H
#include "List.h"
#include <string>
#include <iostream>

namespace cop3530 {
    template <typename E>
    struct Noder {
    public:

        Noder<E> *next = nullptr;
        E     data;
        Noder(E data) {
            this->data = data;
            next       = nullptr;
        }
        Noder() {
            next       = nullptr;
        }
    };



    template<typename E>
    class PSLL : public List<E>{


    public:
        Noder<E> *head;
        Noder<E> *tail;
        Noder<E> *free;
        PSLL(){
            head = tail = nullptr;
            allocate_pool();

        }

        // adds the specified element to the list at the specified position, shifting
        // the element origin   ally at that and those in subsequent positions one
        // position to the ”right.“
        void insert(E   element,
                    size_t position) override;

        // appends the specified element to the list.
        void push_back(E element)  override;

        // prepends the specified element to the list.
        void push_front(E element)  override;

        // replaces the existing element at the specified position with the specified
        // element and return the original element.
        void replace(E   element,
                     size_t position)  override;

        // removes and returns the the element at the specified position, shifting the
        // subsequent elements one position to the ”left.“
        E remove(size_t position)  override;

        // removes and returns the element at the list's tail.
        E pop_back(void)  override;

        // removes and returns the element at the list's head.
        E pop_front(void)  override;

        // returns (without removing from the list) the element at the specified
        // position.
        E      item_at(size_t position)  override;

        // returns the element at the list's tail.
        E      peek_back(void)  override;

        // returns the element at the list's head.
        E      peek_front(void)  override;

        // returns true IFF the list contains no elements.
        bool   is_empty(void)  override;

        // returns true IFF the no more elemtns can be added to the list.
        bool   is_full(void)  override;

        // returns the number of elements in the list as a size_t.
        size_t length(void)  override;

        // removes all elements from the list.
        void   clear(void)  override;

        // returns true IFF at least one of the elements of the list matches the
        // specified element.
        bool contains(E element,
                      bool (*equals_to_function)(E, E))  override;

        // If the list is empty, inserts "<empty list>" into the ostream; otherwise,
        // inserts, enclosed in square brackets, the list's elements, separated by
        // commas, in sequential order.
        void print(std::ostream& os)  override;

        // Allocates, initializes, and returns an array containing a copy of the
        // list's elements in sequential order.
        E* contents(void)  override;

        ~PSLL() ;

    private:
        //allocate pool of size_t
        void allocate_pool();

        //corrects size of free nodes
        void correct_size();

        //push to free list
        void add_free(Noder<E>* freed);

        //pops off freeelist
        Noder<E> * get_free();

        void free_last_element();

    };
    template<typename E>
    void PSLL<E>::insert(E element, size_t position) {
        if (position > 1 + length()) {
            throw std::runtime_error(
                    "cannot insert outside of array: position > 1 + length not allowed");
        }
        else if (position == 0) {
            push_front(element);
            return;
        }
        else if (position == length()) {
            push_back(element);
            return;
        }
        else {
            Noder<E> *it = head;
            Noder<E> *prev;

            do {
                if (position == 0) {
                    Noder<E> *toAdd = get_free();
                    toAdd->data=element;
                    prev->next  = toAdd;
                    toAdd->next = it;
                    return;
                }
                position--;
                prev = it;
                it   = it->next;
            } while (it);
        }
    }

    template<typename E>
    void PSLL<E>::push_back(E element) {
        Noder<E>* toAdd = get_free();
        toAdd->data=element;
        if (is_empty()) {
            head = toAdd;
            tail = toAdd;
        } else {
            tail->next = toAdd;
            tail = toAdd;
        }
    }

    template<typename E>
    void PSLL<E>::push_front(E element) {
        Noder<E>* toAdd = get_free();
        toAdd->data=element;

        if (is_empty()) {
            tail = toAdd;
            head = toAdd;
        }
        else {
            toAdd->next = head;
            head        = toAdd;
        }
    }

    template<typename E>
    void PSLL<E>::replace(E      element,
                          size_t position)  {
        if (position > (length() - 1)) {
            throw std::runtime_error(
                    "cannot replace outside of array: position > length-1 not allowed");
        }
        Noder<E> *it = head;
        while (it) {
            if (position == 0) {
                it->data = element;
                return;
            }
            position--;
            it = it->next;
        }
    }

    template<typename E>
    E PSLL<E>::remove(size_t position) {
        if (position < 0 || position > (length() - 1)) {
            throw std::runtime_error(
                    "cannot replace outside of array: position > length-1 not allowed");
        }
        else if (position == length() - 1) {
            return pop_back();
        }
        else if (position == 0) {
            return pop_front();
        }
        Noder<E> *it   = head;
        position--;//we want node before the position
        while (position!=0) {
            position--;
            it = it->next;
        }

        E element = it->next->data;
        Noder<E>* temp = it->next->next;
        add_free(it->next);
        it->next = temp;
        return element;
    }

    template<typename E>
    E PSLL<E>::pop_back(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }

        E element = tail->data;

        if(length() == 1){
            free_last_element();
            return element;
        }

        Noder<E> *prev = head;
        while (prev ->next && prev->next != tail) {
            prev = prev->next;
        }

        add_free(tail);
        tail = prev;

        return element;
    }

    template<typename E>
    E PSLL<E>::pop_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        E element = head->data;

        if(length() == 1){
            free_last_element();
            return element;
        }
        Noder<E>* temp = head->next;
        add_free(head);
        head = temp;

        return element;
    }

    template<typename E>
    E      PSLL<E>::item_at(size_t position) {
        if (position > (length() - 1)) {
            throw std::runtime_error(
                    "cannot find outside of array: position > length-1 not allowed");
        }
        Noder<E> *it = head;

        while (it) {
            if (position == 0) {
                return it->data;
            }
            position--;
            it = it->next;
        }
        return 0;
    }

    template<typename E>
    E      PSLL<E>::peek_back(void)  {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return tail->data;
    }

    template<typename E>
    E      PSLL<E>::peek_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return head->data;
    }

    template<typename E>
    bool   PSLL<E>::is_empty(void)   {
        if (!head && !tail) {
            return true;
        }
        return false;
    }

    template<typename E>
    bool   PSLL<E>::is_full(void) {
        return false;
    }

    template<typename E>
    size_t PSLL<E>::length(void)          {
        size_t counter = 0;
        Noder<E>  *it      = head;

        while (it) {
            counter++;
            it = it->next;
        }
        return counter;
    }

    template<typename E>
    void   PSLL<E>::clear(void) {
        // could cause memory leak
        head = nullptr;
        tail = nullptr;
    }

    template<typename E>
    bool PSLL<E>::contains(E element,
                           bool (*equals_to_function)(E, E))  {
        Noder<E> *it = head;

        while (it) {
            if (equals_to_function(it->data, element)) {
                return true;
            }
            it = it->next;
        }
        return false;
    }

    template<typename E>
    void PSLL<E>::print(std::ostream& os) {
        Noder<E> *it = head;

        std::string str = "";

        while (it) {
            str += std::to_string(it->data) + " ";
            it   = it->next;
        }
        os << str << std::endl;
    }

    template<typename E>
    E *PSLL<E>::contents(void) {
        size_t len = length();
        Noder<E>  *it  = head;

        E elements[len] ;
        size_t counter = 0;

        while (it) {
            elements[counter] = it->data;
            it          = it->next;
            counter++;
        }

        return elements;
    }

    template<typename E>
    PSLL<E>::~PSLL() {
        head = nullptr;
        tail = nullptr;
    }

    //allocate pool of size_t
    template<typename E>
    void PSLL<E>::allocate_pool(){
        size_t length = this->length();
        size_t newlength = .5 * length;
        if(newlength<50) {
            newlength=50;
        }
            Noder<E> *start = new Noder<E>();
            free = start;
            for (int i = 0; i < newlength; i++) {
                Noder<E> *toadd = new Noder<E>();
                free->next = toadd;
                free = toadd;
            }
            free = start;
    }

    //corrects size of free nodes
    template<typename E>
    void PSLL<E>::correct_size(){
        size_t length = this->length();

        size_t counter = 0;
        Noder<E>  *it      = free;

        while (it) {
            counter++;
            it = it->next;
        }
        if (length >= 100 && counter > (.5*length)){
                 size_t nodestofree = (length-counter);
            for(size_t i = 0; i < nodestofree; i++){
                get_free();
            }
        }
        return;
    }

    //push to free list
    template<typename E>
    void PSLL<E>::add_free(Noder<E>* freed){
        freed->data=NULL;
        freed->next=free;
        free=freed;
        correct_size();
    }

    //pops off freeelist
    template<typename E>
    Noder<E> * PSLL<E>::get_free(){
        if(free){
            Noder<E>* alloc = free;
            free=free->next;
            alloc->next = nullptr;
            return alloc;
        }
        else{
            allocate_pool();
        }

        return get_free();
    }

    template<typename E>
    void PSLL<E>::free_last_element(){
        add_free(head);
        head = nullptr;
        tail = nullptr;
    }
}



#endif //PROJECT1CLION_PSLL_H
