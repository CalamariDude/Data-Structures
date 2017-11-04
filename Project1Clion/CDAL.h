//
// Created by Jad Zeineddine on 9/19/17.
//

#ifndef PROJECT1CLION_CDAL_H
#define PROJECT1CLION_CDAL_H

#include "List.h"
namespace cop3530 {
    template<typename E>


    struct carNode {
    public:
        carNode *next;
        node *cars[50];
        size_t number;

        carNode() {
            next == nullptr;
        }
    };

    template<typename E>
    class CDAL : public List<E> {
    public:
        int head = -2;
        int tail = -2;
        static carNode *carHead = nullptr;
        static carNode *carTail = nullptr;

        // adds the specified element to the list at the specified position, shifting
        // the element originally at that and those in subsequent positions one
        // position to the ”right.“
        void insert(E element,
                    size_t position) override;

        // appends the specified element to the list.
        void push_back(E element) override;

        // prepends the specified element to the list.
        void push_front(E element) override;

        // replaces the existing element at the specified position with the specified
        // element and return the original element.
        void replace(E element,
                     size_t position) override;

        // removes and returns the the element at the specified position, shifting the
        // subsequent elements one position to the ”left.“
        E remove(size_t position) override;

        // removes and returns the element at the list's tail.
        E pop_back(void) override;

        // removes and returns the element at the list's head.
        E pop_front(void) override;

        // returns (without removing from the list) the element at the specified
        // position.
        E item_at(size_t position) override;

        // returns the element at the list's tail.
        E peek_back(void) override;

        // returns the element at the list's head.
        E peek_front(void) override;

        // returns true IFF the list contains no elements.
        bool is_empty(void) override;

        // returns true IFF the no more elemtns can be added to the list.
        bool is_full(void) override;

        // returns the number of elements in the list as a size_t.
        size_t length(void) override;

        // removes all elements from the list.
        void clear(void) override;

        // returns true IFF at least one of the elements of the list matches the
        // specified element.
        bool contains(E element,
                      bool (*equals_to_function)(E, E)) override;

        // If the list is empty, inserts "<empty list>" into the ostream; otherwise,
        // inserts, enclosed in square brackets, the list's elements, separated by
        // commas, in sequential order.
        void print(std::ostream &os) override;

        // Allocates, initializes, and returns an array containing a copy of the
        // list's elements in sequential order.
        E *contents(void) override;

    private:
        carNode *get_car_for_index(carNode *carnode, int next);

        node *get_node_at_index(int index);

        int index_maker(carNode *carnode, int i) {
            return (carnode->number * 50 + i);
        }

        void free_node_servie(node *it);

        void adjustSize();


        int get_free_node_service() {
            carNode *carnode = carHead;
            while (carnode) {
                for (int i = 0; i < 50; i++) {
                    if (carnode->cars[i]->next == -1) {
                        return (index_maker(carnode, i));
                    }
                }
                carnode = carnode->next;
            }
            adjustSize();
            return get_free_node_service();
        }




//        ~CDAL() override;
    };

    template<typename E>
    CDAL<E>::CDAL() {

    }

    template<typename E>
    void CDAL<E>::insert(E element, size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }

    }

    template<typename E>
    void CDAL<E>::push_back(E element) {

    }

    template<typename E>
    void CDAL<E>::push_front(E element) {

    }

    template<typename E>
    void CDAL<E>::replace(E element,
                          size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }
    }

    template<typename E>
    E CDAL<E>::remove(size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }

    }

    template<typename E>
    E CDAL<E>::pop_back(void) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }

    }

    template<typename E>
    E CDAL<E>::pop_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }
    }

    template<typename E>
    E CDAL<E>::item_at(size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }

    }

    template<typename E>
    E CDAL<E>::peek_back(void) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }
    }

    template<typename E>
    E CDAL<E>::peek_front(void) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }
    }

    template<typename E>
    bool CDAL<E>::is_empty(void) {}

    template<typename E>
    bool CDAL<E>::is_full(void) {}

    template<typename E>
    size_t CDAL<E>::length(void) {}

    template<typename E>
    void CDAL<E>::clear(void) {}

    template<typename E>
    bool CDAL<E>::contains(E element,
                           bool (*equals_to_function)(E, E)) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }
    }

    template<typename E>
    void CDAL<E>::print(std::ostream &os) {}

    template<typename E>
    E *CDAL<E>::contents(void) {}

    template<typename E>
    carNode *CDAL<E>::get_car_for_index(carNode *carnode, int next) {

    }

}

//    template<typename E>
//    CDAL<E>::~CDAL() {}





#endif //PROJECT1CLION_CDAL_H
