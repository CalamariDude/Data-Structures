//
// Created by Jad Zeineddine on 9/19/17.
//

#ifndef PROJECT1CLION_CBL_H
#define PROJECT1CLION_CBL_H
#define DEBUG
#include "List.h"
#include <vector>
namespace cop3530 {

    template<typename E>
    class CBL : public List<E>{


    public:
        size_t tail = 0;
        size_t head = 0;
        // constructor
        E* vec;
        size_t vecSize; // maintains size of backing array, not length

        CBL() {
            size_t size = 50;
            vecSize = size;
            vec = new E[size];
            tail = 0;
        }

        CBL(size_t size) {
            vecSize = size;
            vec = new E[size];
            tail = 0;
        }

        // adds the specified element to the list at the specified position, shifting
        // the element originally at that and those in subsequent positions one
        // position to the ”right.“
        void insert(E element,
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

//        ~CBL();

        //helper functions
        size_t make_bigger();
        void make_smaller(size_t length);
        size_t find_free_node_service(int isfront);
        void move_up(size_t position);
        void move_back(size_t position);
        void balance();
        void insert_first_element(E element);
        void remove_last_element(E element);
        size_t increment(size_t &pos);
        size_t decrement(size_t &pos);
        size_t position_at(size_t pos);

#ifdef DEBUG
        void printVector(void) ;
#endif
    };

    // tbd
    template<typename E>
    void CBL<E>::insert(E element, size_t position) {
        if (position < 0 || position > length()) {
            throw std::runtime_error(
                    "cannot insert outside of array: position > 1 + length not allowed");
        }
        else if(position == 0){
            push_front(element);
        }
        else if(position == length()+1){
            push_back(element);
        }
        else{
            move_up(position);
            size_t insert = find_free_node_service(0);
            vec[insert] = element;
        }
    }

    // tbd
    template<typename E>
    void CBL<E>::push_back(E element) {
        if(is_empty()){
            insert_first_element(element);
        }
        else{
            size_t insert = find_free_node_service(0);
            vec[insert] = element;
        }
    }

    template<typename E>
    void CBL<E>::push_front(E element) {
        if(is_empty()){
            insert_first_element(element);
        }
        else{
            size_t insert = find_free_node_service(1);
            vec[insert] = element;
        }
    }

    template<typename E>
    void CBL<E>::replace(E      element,
                          size_t position)  {
        if (position > (length() - 1) || position < 0) {
            throw std::runtime_error(
                    "cannot replace outside of array: position > length-1 not allowed");
        }
        vec[head] = element;

    }

    template<typename E>
    E CBL<E>::remove(size_t position)  {
        if (position > (length() - 1) || position < 0) {
            throw std::runtime_error(
                    "cannot remove outside of array: position > length-1 not allowed");
        }
        if(position == 0){
            return pop_front();
        }

        if(position - length()-1){
            return pop_back();
        }

        E element = vec[position_at(position)];
        move_back(position);
        return element;
    }

    template<typename E>
    E CBL<E>::pop_back(void)           {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        E element = vec[tail];
        decrement(tail);
        return element;
    }


    template<typename E>
    E CBL<E>::pop_front(void)          {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        E element = vec[head];
        increment(head);
        return element;
    }

    template<typename E>
    E      CBL<E>::item_at(size_t position) {
        if (position > (length() - 1) || position < 0 ) {
            throw std::runtime_error(
                    "cannot find outside of array: position > length-1 not allowed");
        }
        return vec[position_at(position)];
    }

    template<typename E>
    E      CBL<E>::peek_back(void)  {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return vec[tail];
    }

    template<typename E>
    E      CBL<E>::peek_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return vec[head];
    }

    template<typename E>
    bool   CBL<E>::is_empty(void) {
        if (length() == 0) {
            return true;
        }
        return false;
    }

    template<typename E>
    bool   CBL<E>::is_full(void) {
        return false;
    }

    template<typename E>
    size_t CBL<E>::length(void) {
        if(tail > head){
            return tail-head;
        }
        else if (tail < head){
            return head-tail;
        }
        return 0;
    }

    template<typename E>
    void   CBL<E>::clear(void) {
        head = tail = 0;
        balance();
    }

    template<typename E>
    bool CBL<E>::contains(E element,
                           bool (*equals_to_function)(E, E))  {
        if(is_empty()){
            return false;
        }
        size_t it = head;
        while(it != tail){
            if(equals_to_function( vec[it] , element ) ){
                return true;
            }
            increment(it);
        }
        return false;
    }

    template<typename E>
    
    void CBL<E>::print(std::ostream& os) {
        size_t it = head;
        while(it != tail){
            os << vec[it] << " ";
            increment(it);
        }
    }

    template<typename E>
    E *CBL<E>::contents(void) {
        //don't send them the original array
        size_t size = length();
        E * arr = new E[size];

        for(size_t i = head, j = 0; i != tail; increment(i), j++){
            arr[j] = vec[i];
        }

        return arr;
    }

//    template<typename E>
//    CBL<E>::~CBL() {
//        head = -2;
//        tail = -2;
//    }


    template<typename E>
    size_t CBL<E>::make_bigger(){
        size_t size = length();
        size_t new_length = size * 1.5;
        E* new_vec = new E[new_length];
        for(size_t i = head, j = 0; i < size; increment(i), j ++){
            new_vec[j] = vec[i];
        }
        //could cause problems
        vec = new_vec;
        head = 0;
        tail = size;
        return new_length;
    }

    template<typename E>
    void CBL<E>::make_smaller(size_t size){
        size_t len = vecSize;
        size_t newsize = (size_t) ((double)len* 0.75);
        E* new_vec = new E[newsize];

        for(size_t i = head, j = 0; i < len; increment(i), j++){
            new_vec[j] = vec[i];
        }
        head = 0;
        tail = length();
    }

    template<typename E>
    size_t CBL<E>::find_free_node_service(int isFront){
        size_t it;
        if(isFront){
             it = head;
            if(decrement(it) == tail){
                make_bigger();
                it = 0;
                decrement(it);

            }
        }
        else{
            it = tail;
            if(increment(it) == head){
                make_bigger();
                it = length()-1;
                increment(it);
            }
        }
        return it;
    }

    template<typename E>
    void CBL<E>::move_up(size_t position){
        size_t it = find_free_node_service(0);
        while(it > position){
            vec[it] = vec[decrement(it)];
        }

        increment(tail);
    }

    template<typename E>
    void CBL<E>::move_back(size_t position){
        size_t it = position;
        while(it < tail){
            vec[it] = vec[increment(it)];
        }

        decrement(it);
        balance();
    }

    template<typename E>
    void CBL<E>::balance(){
        size_t length_of_array = vecSize;
        if(length() > 0) {
            if (length_of_array / length() > 2) {
                make_smaller(length_of_array);
            }
        }
    }

    template<typename E>
    void CBL<E>::insert_first_element(E element){
        vec[head] = element;
        tail = 1;
    }

    template<typename E>
    void CBL<E>::remove_last_element(E element){
        head = tail = 0;
    }

    template<typename E>
    size_t CBL<E>::increment(size_t &pos){
        size_t size = vecSize;
        if(pos+1 % size == 0 ){
            pos = 0;
        }
        return pos;
    }
    template<typename E>
    size_t CBL<E>::decrement(size_t &pos){
        if( pos -1 < 0 ){
            pos = vecSize-1;
        }
        return pos;
    }
    template<typename E>
    size_t CBL<E>::position_at(size_t pos){
        return (pos + head)%vecSize;
    }

#ifdef DEBUG
    template<typename E>
    void CBL<E>::printVector(){

    }
#endif
}
#endif //PROJECT1CLION_CBL_H
