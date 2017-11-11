//
// Created by Jad Zeineddine on 9/18/17.
//

#ifndef PROJECT1CLION_SSLL_H
#define PROJECT1CLION_SSLL_H
#include "List.h"
#include <string>
#include <iostream>
namespace cop3530 {
    template <typename E>
    struct Node {
    public:

        Node<E> *next = nullptr;
        E     data;
        Node(E data) {
            this->data = data;
            next       = nullptr;
        }
    };

    template<typename E>
    class SSLL : public List<E>{


        Node<E> *head;
        Node<E> *tail;

        // adds the specified element to the list at the specified position, shifting
        // the element originally at that and those in subsequent positions one
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

        ~SSLL() ;
    };
    template<typename E>
    void SSLL<E>::insert(E element, size_t position) {
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
            Node<E> *it = head;
            Node<E> *prev;

            do {
                if (position == 0) {
                    Node<E> *toAdd = new Node<E>(element);
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
    void SSLL<E>::push_back(E element) {
        Node<E> *toAdd = new Node<E>(element);
        if (is_empty()) {
            head = toAdd;
            tail = toAdd;
        } else {
            tail->next = toAdd;
            tail = toAdd;
        }
    }

    template<typename E>
    void SSLL<E>::push_front(E element) {
        Node<E> *toAdd = new Node<E>(element);

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
    void SSLL<E>::replace(E      element,
                          size_t position)  {
        if (position > (length() - 1)) {
            throw std::runtime_error(
                    "cannot replace outside of array: position > length-1 not allowed");
        }
        Node<E> *it = head;

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
    E SSLL<E>::remove(size_t position) {
        if (position > (length() - 2)) {
            throw std::runtime_error(
                    "cannot replace outside of array: position > length-1 not allowed");
        }
        else if (position == length() - 1) {
            return pop_back();
        }
        else if (position == 0) {
            return pop_front();
        }
        Node<E> *it   = head;
        Node<E> *prev = head;
        Node<E> *temp;

        while (it) {
            if (position == 0) {
                temp       = it;
                prev->next = it->next;
                return temp->data;
            }
            position--;
            it   = it->next;
            prev = it;
        }
    }

    template<typename E>
    E SSLL<E>::pop_back(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        Node<E> *prev = nullptr;
        Node<E> *temp = tail;
        Node<E> *it   = head;

        while (it->next) {
            prev = it;
            it   = it->next;
        }
        tail = prev;

        if (prev) {
            tail->next = nullptr;
        }
        else{
            head = nullptr;
        }
        return temp->data;
    }

    template<typename E>
    E SSLL<E>::pop_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        Node<E> *temp = head;

        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next; // could equal nullptr
        }
        return temp->data;
    }

    template<typename E>
    E      SSLL<E>::item_at(size_t position) {
        if (position > (length() - 1)) {
            throw std::runtime_error(
                    "cannot find outside of array: position > length-1 not allowed");
        }
        Node<E> *it = head;

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
    E      SSLL<E>::peek_back(void)  {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return tail->data;
    }

    template<typename E>
    E      SSLL<E>::peek_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return head->data;
    }

    template<typename E>
    bool   SSLL<E>::is_empty(void)   {
        if (!head && !tail) {
            return true;
        }
        return false;
    }

    template<typename E>
    bool   SSLL<E>::is_full(void) {
        return false;
    }

    template<typename E>
    size_t SSLL<E>::length(void)          {
        size_t counter = 0;
        Node<E>  *it      = head;

        while (it) {
            counter++;
            it = it->next;
        }
        return counter;
    }

    template<typename E>
    void   SSLL<E>::clear(void) {
        // could cause memory leak
        head = nullptr;
        tail = nullptr;
    }

    template<typename E>
    bool SSLL<E>::contains(E element,
                           bool (*equals_to_function)(E, E))  {
        Node<E> *it = head;

        while (it) {
            if (equals_to_function(it->data, element)) {
                return true;
            }
            it = it->next;
        }
        return false;
    }

    template<typename E>
    void SSLL<E>::print(std::ostream& os) {
        Node<E> *it = head;

        std::string str = "";

        while (it) {
            str += std::to_string(it->data) + " ";
            it   = it->next;
        }
        os << str << std::endl;
    }

    template<typename E>
    E *SSLL<E>::contents(void) {
        size_t len = length();
        Node<E>  *it  = head;

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
    SSLL<E>::~SSLL() {
        head = nullptr;
        tail = nullptr;
    }
}



#endif //PROJECT1CLION_SSLL_H
