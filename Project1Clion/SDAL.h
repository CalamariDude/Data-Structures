//
// Created by Jad Zeineddine on 9/19/17.
//

#ifndef PROJECT1CLION_SDAL_H
#define PROJECT1CLION_SDAL_H
#define DEBUG
#include "List.h"
#include <vector>
namespace cop3530 {template<typename E>
    struct node {
    public:

        int next;
        E      data;
        node(E data) {
            this->data = data;
            next       = -1 ;
        }

        node() {
            next       = -1;
//            std::cout<<"Making: ("<<data<<","<<next<<")"<<std::endl;
        }
    };
    template<typename E>
    class SDAL : public List<E>{

        
    public:
        int head = -2;
        int tail = -2;
        std::vector<node<E> * > v;

        // no ur stupid
        // constructor
        SDAL() {
            head = -2;
            tail = -2;
            for (size_t i = 0; i < 50; i++) {
                node<E> *add = new node<E>();
                //change
                v.push_back(add);
            }
        }

        SDAL(size_t size) {
            // errors
            std::vector<node<E> *> a(size);
            v = a;

            head = 0;
            tail = 0;

            for (size_t i = 0; i < size; i++) {
                node<E> *add = new node<E>();
                //change
                v.push_back(add);
            }
        }

        // adds the specified element to the list at the specified position, shifting
        // the element originally at that and those in subsequent positions one
        // position to the ”right.“
        void insert(E      element,
                    size_t position) override;

        // appends the specified element to the list.
        void push_back(E element)  override;

        // prepends the specified element to the list.
        void push_front(E element)  override;

        // replaces the existing element at the specified position with the specified
        // element and return the original element.
        void replace(E      element,
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
        E    * contents(void)  override;

//        ~SDAL();
        void   make_bigger();
        size_t find_free_node_service();
        void   free_node(size_t position);

        #ifdef DEBUG
        void printVector(void) override;
        #endif
    };

    // tbd
    template<typename E>
    void SDAL<E>::insert(E element, size_t position) {
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
            size_t it = head;
            size_t prev;
            size_t positionToAdd = find_free_node_service();

            do {
                if (position == 0) {
                    v.at(prev)->next          = positionToAdd;
                    v.at(positionToAdd)->next = it;
                    v.at(positionToAdd)->data = element;
                    return;
                }
                position--;
                prev = it;
                it   = v.at(it)->next;
            } while (it != -2);
        }
    }

    // tbd
    template<typename E>
    void SDAL<E>::push_back(E element)               {
        size_t positionToAdd = find_free_node_service();
        if (is_empty()) {
            head = positionToAdd;
            tail = positionToAdd;
            v.at(positionToAdd)->next = -2;
            v.at(positionToAdd)->data = element;
            return;
        }

        // prob wrong
        v.at(positionToAdd)->next = -2;
        v.at(positionToAdd)->data = element;
        v.at(tail)->next = positionToAdd;
        tail                      = positionToAdd;
    }

    template<typename E>
    void SDAL<E>::push_front(E element) {
        size_t positionToAdd = find_free_node_service();

        if (is_empty()) {
            head = positionToAdd;
            tail = positionToAdd;
            v.at(positionToAdd)->next = -2;
            v.at(positionToAdd)->data = element;
            std::cout<<"first node added("<< v.at(positionToAdd)->data<< "," <<v.at(positionToAdd)->next<< ")"<<std::endl;
            return;
        }

        v.at(positionToAdd)->next = head;
        v.at(positionToAdd)->data = element;
        head                      = positionToAdd;
    }

    template<typename E>
    void SDAL<E>::replace(E      element,
                          size_t position)  {
        if (position > (length() - 1)) {
            throw std::runtime_error(
                    "cannot replace outside of array: position > length-1 not allowed");

        }
        size_t it = head;

        while (it != -2) {
            if (position == 0) {
                v.at(it)->data = element;
                return;
            }
            position--;
            it = v.at(it)->next;
        }
    }

    template<typename E>
    E SDAL<E>::remove(size_t position)  {
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
        size_t it   = head;
        size_t prev = head;
        size_t temp;

        while (it != -2) {
            if (position == 0) {
                temp             = it;
                v.at(prev)->next = v.at(it)->next;
                E data = v.at(temp)->data;
                free_node(temp);
                return data;
            }
            position--;
            it   = v.at(it)->next;
            prev = it;
        }
    }

    template<typename E>
    E SDAL<E>::pop_back(void)           {

        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        int prev = -2;
        int temp = tail;
        int it   = head;
        while (v.at(it)->next != -2) {
            prev = it;
            it   = v.at(it)->next;
        }
        tail = prev;
        if (prev != -2) {
            v.at(tail)->next = -2;
        }
        if (tail == -2) {
            head = -2;
            tail = -2;
        }
        E data = v.at(temp)->data;
        free_node(temp);
        return data;
    }


    template<typename E>
    E SDAL<E>::pop_front(void)          {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        int temp = head;
        head = v.at(head)->next;

        if (head == -2) {
            head = tail = -2;
        }
        E data = v.at(temp)->data;
        free_node(temp);
        return data;
    }

    template<typename E>
    E      SDAL<E>::item_at(size_t position) {
        if (position > (length() - 1)) {
            throw std::runtime_error(
                    "cannot find outside of array: position > length-1 not allowed");
        }
        int it = head;

        while (it != -2) {
            if (position == 0) {
                return v.at(it)->data;
            }
            position--;
            it = v.at(it)->next;
        }
        return 0;
    }

    template<typename E>
    E      SDAL<E>::peek_back(void)  {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return v.at(tail)->data;
    }

    template<typename E>
    E      SDAL<E>::peek_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return v.at(head)->data;
    }

    template<typename E>
    bool   SDAL<E>::is_empty(void) {
        if (head==-2 && tail ==-2) {
            return true;
        }
        return false;
    }

    template<typename E>
    bool   SDAL<E>::is_full(void) {
        return false;
    }

    template<typename E>
    size_t SDAL<E>::length(void) {
        size_t counter = 0;
        int it      = head;
        std::cout<<"tail = "<< tail <<std::endl;
        std::cout<<"it "<< it <<std::endl;
//        std::cout<<"length() head = "<< head <<std::endl;
        while (it != -2 && it != -1) {
            std::cout<<"it next = "<< v.at(it)->next <<std::endl;
            counter++;
            it = v.at(it)->next;
        }
        std::cout<<"length = " << counter <<std::endl;
//        std::cout<<"counter = " << counter <<std::endl;
        return counter;
    }

    template<typename E>
    void   SDAL<E>::clear(void) {
        for(size_t i = 0; i < v.size(); i++){
            v.at(i)->next = -1;
        }
        head = -2;
        tail = -2;
    }

    template<typename E>
    bool SDAL<E>::contains(E element,
                           bool (*equals_to_function)(E, E))  {
        int it = head;

        while (it != -2) {
            if (equals_to_function(v.at(it)->data, element)) {
                return true;
            }
            it = v.at(it)->next;
        }
        return false;
    }

    template<typename E>
    void SDAL<E>::print(std::ostream& os) {
        std::string str = "";
        int it = head;
        while (it != -2) {
            str += std::to_string(v.at(it)->data) + " ";
            it   = v.at(it)->next;
        }
        os << str << std::endl;
    }

    template<typename E>
    E *SDAL<E>::contents(void) {
        size_t len = length();

        E elements[len];
        size_t counter = 0;
        int it      = head;

        while (it != -2) {
            elements[counter] = v.at(it)->data;
            it         = v.at(it)->next;
            counter++;
        }
        return elements;
    }

//    template<typename E>
//    SDAL<E>::~SDAL() {
//        head = -2;
//        tail = -2;
//    }

    template<typename E>
    void SDAL<E>::make_bigger() {
        size_t newlength = v.size() * 1.5;

        std::vector<node<E> *>  newvec(newlength);

        // copy elements over
        for (size_t i = 0; i < v.size(); i++) {
            newvec[i] = v.at(i);
        }

        for (size_t i = v.size(); i < newlength; i++) {
            node<E> *toAdd = new node<E>();
            toAdd->next=-1;
            newvec[i] = toAdd;
        }
        v = newvec;
    }
    template<typename E>
    size_t SDAL<E>::find_free_node_service() {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i)->next == -1) {
                return i;
            }
        }
        make_bigger();
        return find_free_node_service();
    }
    template<typename E>
    void SDAL<E>::free_node(size_t position) {
        v.at(position)->next = -1;
        if(is_empty()){
            head = -2;
            tail = -2;
        }
    }
#ifdef DEBUG
    template<typename E>
    void SDAL<E>::printVector(){
        for(int i = 0; i < v.size(); i++ ){
            std::cout<<i<<" ("<<v.at( i)->data<<","<<v.at(i)->next<<")";
            std::cout<< "" <<std::endl;
        }
        std::cout<<""<<std::endl;
    }
#endif
}
#endif //PROJECT1CLION_SDAL_H
