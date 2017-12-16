//
// Created by Jad Zeineddine on 9/19/17.
//

#ifndef PROJECT1CLION_SDAL_H
#define PROJECT1CLION_SDAL_H
#define DEBUG
#include "List.h"
#include <vector>
namespace cop3530 {

    template<typename E>
    class SDAL : public List<E>{

    private:
        size_t tail = SIZE_T_MAX;
        E* vec;
    public:


    public:
        class SDAL_Iter
        {
        public:
            //--------------------------------------------------
            // type aliases
            //--------------------------------------------------
            using value_type = E;
            using difference_type = std::ptrdiff_t;
            using reference = E&;
            using pointer = E*;
            using iterator_category = std::forward_iterator_tag;
            using self_type = SDAL_Iter;
            using self_reference = SDAL_Iter&;

        private:
            const SDAL* sdal;
            E* here;

        public:
            explicit SDAL_Iter(E * start = nullptr, SDAL * vector = nullptr): // diff
                    here(start), sdal(vector) {
            }
            SDAL_Iter(const SDAL_Iter& src) :
                    here(src.here) , sdal(src.sdal){
            }

            reference operator*() const {
                if (!here) {
                    throw std::runtime_error("null node");
                }
                return *here;
            }
            //pointer operator
            pointer operator->() const {
                if (!here) {
                    throw std::runtime_error("null node");
                }
                return here;
            }
            //pointer operator
            self_reference operator=(const SDAL_Iter& src) {
                if (*this == src) {
                    return *this;
                }
                sdal = src.sdal;
                here = src.here;
                return *this;
            }
            //preinc
            self_reference operator++() {
                if (!here ) {
                    throw std::runtime_error("null node");
                }
                here++;
                return *this;
            }
            //post inc
            self_type operator++(int) {
                if (!here) {
                    throw std::runtime_error("null node");
                }
                SDAL_Iter iter(*this);
                here++;
                return iter;
            }
            //equals operator
            bool operator==(const SDAL_Iter& rhs) const {
                return here  == rhs.here;
            }
            //not equals operator
            bool operator!=(const SDAL_Iter& rhs) const {
                return here != rhs.here;
            }
        };

        class SDAL_Const_Iter
        {
        public:
            //--------------------------------------------------
            // type aliases
            //--------------------------------------------------
            using value_type = E ;
            using difference_type = std::ptrdiff_t ;
            using reference = const E& ;
            using pointer = const E* ;
            using self_type = SDAL_Const_Iter ;
            using self_reference = SDAL_Const_Iter&;
            using iterator_category = std::forward_iterator_tag;

        private:
            const SDAL* sdal;
            const E* here;

        public:
            explicit SDAL_Const_Iter(E * start = nullptr, SDAL * sdal = nullptr) : // diff
                    here(start) {
            }

            SDAL_Const_Iter(const SDAL_Const_Iter& src) :
                    here(!here) {
            }
            //pointer operator
            reference operator*() const {
                if (!here) {
                    throw std::runtime_error("null node");
                }
                return *here;
            }
            //pointer operator
            pointer operator->() const {
                if (!here) {
                    throw std::runtime_error("null node");
                }
                return here;
            }

            self_reference operator=(const SDAL_Const_Iter& src) {
                if (*this == src) {
                    return *this;
                }
                sdal = src.sdal;
                here = src.here;
                return *this;
            }
            //pre inc
            self_reference operator++() {
                if (!here) {
                    throw std::runtime_error("null node");
                }
                here++;
                return *this;
            }
            //post inc
            self_type operator++(int) {
                if (!here) {
                    throw std::runtime_error("null node");
                }
                SDAL_Const_Iter iter(*this);
                here++;
                return iter;
            }
            //equals operator
            bool operator==(const SDAL_Const_Iter& rhs) const {
                if(here != rhs.here){
                    return true;
                }
                return false;
            }
            //not equals operator
            bool operator!=(const SDAL_Const_Iter& rhs) const {
                if(here != rhs.here){
                    return true;
                }
                return false;
            }
        };

        using size_t = std::size_t ;
        using value_type = E ;
        using iterator = SDAL_Iter ;
        using const_iterator = SDAL_Const_Iter ;

        // iterators over a non-const List
        iterator begin() {
            return SDAL_Iter(0);
        }
        iterator end() {
            return SDAL_Iter();
        }

        // iterators over a const List
        const_iterator begin() const {
            return SDAL_Const_Iter(0);
        }
        const_iterator end() const {
            return SDAL_Const_Iter();
        }

        //move operators
        E& operator[](size_t position) {
            if (position > length() - 1) {
                throw std::runtime_error("out of bounds");
            }
            return vec[position];
        }

        //move operators
        E const& operator[](size_t position) const {
            if (position > length() - 1) {
                throw std::runtime_error("out of bounds");
            }
            size_t it = 0;

            return vec[position];
        }


        //copy constructor
        SDAL(const SDAL& sdal) {
            //don't need to clear since this is new ssll
            tail = SIZE_T_MAX;
            size_t it = 0;

            size_t size = sdal.length();
            vec = new E[size];

            //iterate and push back new data
            while (it != sdal.tail) {
                push_back(sdal.vec[it]);
                it = it + 1;
            }
        }

        //copy assigment constructor
        SDAL& operator=(const SDAL& sdal) {
            if (&sdal== this)
                return *this;
            //clear before adding new
            clear();

            //iterate and push back new data
            size_t it = 0;
            while (it != sdal.tail) {
                push_back(sdal.vec[it]);
                it = it+1;
            }
            return *this;
        }


        // constructor
        SDAL() {
            size_t size = 50;
            vec = new E[size];
            tail = SIZE_T_MAX;
        }

        SDAL(size_t size) {
            vec = new E[size];
            tail = SIZE_T_MAX;
        }

        ~SDAL();

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


        //helper functions
        size_t make_bigger();
        void make_smaller(size_t length);
        size_t find_free_node_service();
        void move_up(size_t position);
        void move_back(size_t position);
        void balance();
        void insert_first_element(E element);
        void remove_last_element(E element);

        #ifdef DEBUG
        void printVector(void) ;
        #endif
    };

    // tbd
    template<typename E>
    void SDAL<E>::insert(E element, size_t position) {
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
            vec[position] = element;
        }
    }

    // tbd
    template<typename E>
    void SDAL<E>::push_back(E element) {
        if(is_empty()){
            insert_first_element(element);
        }
        else{
            size_t insert = find_free_node_service();
            vec[insert] = element;
            tail++;
        }
    }

    template<typename E>
    void SDAL<E>::push_front(E element) {
        if(is_empty()){
            insert_first_element(element);
        }
        else{
            move_up(0);
            vec[0] = element;
        }
    }

    template<typename E>
    void SDAL<E>::replace(E      element,
                          size_t position)  {
        if (position > (length() - 1) || position < 0) {
            throw std::runtime_error(
                    "cannot replace outside of array: position > length-1 not allowed");
        }
        vec[position] = element;
    }

    template<typename E>
    E SDAL<E>::remove(size_t position)  {
        if (position > (length() - 1) || position < 0) {
            throw std::runtime_error(
                    "cannot remove outside of array: position > length-1 not allowed");
        }
        E element = vec[position];
        move_back(position);
        return element;
    }

    template<typename E>
    E SDAL<E>::pop_back(void)           {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        E element = vec[tail];
        remove(tail);
        return element;
    }


    template<typename E>
    E SDAL<E>::pop_front(void)          {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot pop off empty list");
        }
        E element = vec[0];
        move_back(0);
        return element;
    }

    template<typename E>
    E      SDAL<E>::item_at(size_t position) {
        if (position > (length() - 1) || position < 0 ) {
            throw std::runtime_error(
                    "cannot find outside of array: position > length-1 not allowed");
        }
        return vec[position];
    }

    template<typename E>
    E      SDAL<E>::peek_back(void)  {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return vec[tail];
    }

    template<typename E>
    E      SDAL<E>::peek_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot peek empty list");
        }
        return vec[0];
    }

    template<typename E>
    bool   SDAL<E>::is_empty(void) {
        if (length() == 0) {
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
        if(tail != SIZE_T_MAX){
            return tail+1;
        }
        return 0;
    }

    template<typename E>
    void   SDAL<E>::clear(void) {
        tail = 0;
        balance();
    }

    template<typename E>
    bool SDAL<E>::contains(E element,
                           bool (*equals_to_function)(E, E))  {
        if(is_empty()){
            return false;
        }
        size_t it = 0;
        while(it <= tail){
            if(equals_to_function( vec[it] , element ) ){
                return true;
            }
            it++;
        }
        return false;
    }

    template<typename E>
    void SDAL<E>::print(std::ostream& os) {
        size_t it = 0;
        while(it <= tail){
            os << vec[it] << " ";
            it++;
        }
    }

    template<typename E>
    E *SDAL<E>::contents(void) {
        size_t size = length();

        //don't send them the original array
        E * arr = new E[size];

        for(int i = 0; i < size; i++ ){
            arr[i] = vec[i];
        }

        return arr;
    }

    template<typename E>
    SDAL<E>::~SDAL() {
        delete vec;
        tail = -2;
    }


    template<typename E>
    size_t SDAL<E>::make_bigger(){
        size_t size = length();//right here
        size_t new_length = size * 1.5;
        E* new_vec = new E[new_length];
        for(int i = 0; i < size; i++){
            new_vec[i] = vec[i];
        }
        //could cause problems
        vec = new_vec;
        return new_length;
    }

    template<typename E>
    void SDAL<E>::make_smaller(size_t size){
        size_t len = length();
        size = (int) ((double)size* 0.75);
        E* new_vec = new E[size];

        for(int i = 0; i < len; i++){
            new_vec[i] = vec[i];
        }
        vec = new_vec;
    }

    template<typename E>
    size_t SDAL<E>::find_free_node_service(){
        if(tail+1 > length()-1){
            make_bigger();
        }

        return tail+1;
    }

    template<typename E>
    void SDAL<E>::move_up(size_t position){
        size_t it = find_free_node_service();
        while(it > position){
            vec[it] = vec[it-1];
            it--;
        }

        tail++;
    }

    template<typename E>
    void SDAL<E>::move_back(size_t position){
        size_t it = position;
        while(it < tail){
            vec[it] = vec[it+1];
            it++;
        }

        balance();
        tail--;
    }

    template<typename E>
    void SDAL<E>::balance(){
        size_t length_of_array = make_bigger();
        if(length() > 0) {
            if (length_of_array / length() > 2) {
                make_smaller(length_of_array);
            }
        }
    }

    template<typename E>
    void SDAL<E>::insert_first_element(E element){
        vec[0] = element;
        tail = 0;
    }

    template<typename E>
    void SDAL<E>::remove_last_element(E element){
        tail = SIZE_T_MAX;
    }

#ifdef DEBUG
    template<typename E>
    void SDAL<E>::printVector(){

    }
#endif
}
#endif //PROJECT1CLION_SDAL_H
