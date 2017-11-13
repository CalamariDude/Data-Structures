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
        E  cars[50];

        carNode() {

        }
    };

    template<typename E>
    class CDAL : public List<E> {
    public:
        int head = -2;
        int tail = -2;
        carNode<E> * root;


        //constructor
        CDAL(){
             root->next = nullptr;
              std::cout << "root->next = "<< root->next << '\n';
        }

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

      #ifdef DEBUG
     void printVector() override{
          print(std::cout);
     }
      #endif

    private:
        //helper functions
        carNode<E> * carnode_at(int index);

        int get_free_node_service();

        void first_element_insert(E element);

        E remove_last_element();

        void move_up(int position);

        void move_back(int position);

        void deallocate_unused();
        //end of helper functions
        //        ~CDAL() override;
    };

    template<typename E>
    void CDAL<E>::insert(E element, size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }
        if(position == length()){
            push_back(element);
        }
        else if(position == 0) {
            push_front(element);
        }
        else{
            move_up(position);
            carNode<E>  * node= carnode_at(position);
            node->cars[position%50] = element;
        }
    }

    template<typename E>
    void CDAL<E>::push_back(E element) {

        if(is_empty()){
            first_element_insert(element);
            return;
        }
        int indexToAdd = get_free_node_service();
        carNode<E> * carnode = carnode_at(indexToAdd);
        carnode->cars[(indexToAdd%50)] = element;
        tail = indexToAdd;
    }

    template<typename E>
    void CDAL<E>::push_front(E element) {
        if(is_empty()){
            first_element_insert(element);
        }
        move_up(0);
        carNode<E> * node = carnode_at(0);
        node->cars[0] = element;
        head = 0;
    }

    template<typename E>
    void CDAL<E>::replace(E element,
                          size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot replace in empty list or out of bounds"
            );
        }

        carNode<E> *carnode = carnode_at(position);
        carnode->cars[position % 50] = element;
    }

    template<typename E>
    E CDAL<E>::remove(size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }
        E element;
        if (position == length()) {
            element = pop_back();
        } else if (position == 0) {
            element = pop_front();
        }
        carNode<E>* node = carnode_at(position);
        element = node->cars[position%50];
        move_back(position);
        deallocate_unused();
        return element;
    }

    template<typename E>
    E CDAL<E>::pop_back(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }

        if(length() == 1){
            return remove_last_element();
        }
        std::cout<<"testing carnode_at"<<std::endl;
        carNode<E> * node = carnode_at(tail);
        E element = node->cars[tail%50];
        tail--;
        deallocate_unused();
        std::cout<<"nope"<<std::endl;
        return element;
    }

    template<typename E>
    E CDAL<E>::pop_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }
        if(length() == 1){
            return remove_last_element();
        }
        //head should always stays at 0.
        carNode<E> * node = carnode_at(head);
        E element = node->cars[head%50];
        std::cout << "debugging this" << '\n';
        move_back(head);
        std::cout << "debugging this" << '\n';
        deallocate_unused();
        return element;
    }

    template<typename E>
    E CDAL<E>::item_at(size_t position) {
        if (is_empty() || position >= length()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );

        }

        carNode<E> * node = carnode_at(position);
        return node->cars[position%50];
    }

    template<typename E>
    E CDAL<E>::peek_back(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }

        carNode<E> * node = carnode_at(tail);
        return node->cars[tail%50];

    }

    template<typename E>
    E CDAL<E>::peek_front(void) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }

        carNode<E> * node = carnode_at(head);
        return node->cars[head%50];
    }

    template<typename E>
    bool CDAL<E>::is_empty(void) {
        if(length() == 0 ){
            return true;
        }
        return false;
    }

    template<typename E>
    bool CDAL<E>::is_full(void) {
        return false;
    }

    template<typename E>
    size_t CDAL<E>::length() {
        if(head != -2  && tail != -2)
            return tail-head + 1;
        else
            return 0;
    }

    template<typename E>
    void CDAL<E>::clear(void) {
         if(!is_empty()){
              tail = head ;
              deallocate_unused();
              head = tail = -2;
         }
    }

    template<typename E>
    bool CDAL<E>::contains(E element,
                           bool (*equals_to_function)(E, E)) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }

        int it = head;
        carNode<E> * node = carnode_at(it);
        while(it != tail + 1){
            if(node->cars[it%50] == element){
                return true;
            }
            it++;
            node = carnode_at(it);
        }
        return false;
    }

    template<typename E>
    void CDAL<E>::print(std::ostream &os) {
        if (is_empty()) {
            throw std::runtime_error(
                    "cannot remove in empty list or out of bounds"
            );
        }

        int it = head;
        carNode<E> * node = carnode_at(it);
        while(it != tail + 1){
            os << node->cars[it%50] << " " ;
            it++;
            node = carnode_at(it);
        }
    }

    template<typename E>
    E* CDAL<E>::contents(void) {
        int size = length();
        int * arr = new int[size];
        size_t counter = 0;
        int it = head;
        carNode<E> * node = carnode_at(it);
        while(it != tail + 1){
            arr[counter] = node->cars[it%50];
            it++;
            counter++;
            node = carnode_at(it);
        }
        return arr;
    }


    //helper functions
    template<typename E>
    carNode<E> * CDAL<E>::carnode_at(int index){
        int timestogo = index/50;
        carNode<E> * it = root;
        while(timestogo != 0 ){
            it = it->next;
            timestogo--;
        }
        return it;
    }

    template<typename E>
    int CDAL<E>::get_free_node_service() {
        //check if next index is the first element of next array
        if(is_empty()){
         return 0;
        }
        if((tail+1) % 50 == 0 ){
            if(!carnode_at(tail)->next){
                carNode<E>* node = new carNode<E>();
                carnode_at(tail)->next = node;
            }
        }
        return tail+1;
    }


    template<typename E>
    void CDAL<E>::first_element_insert(E element){
        head = tail = 0;
        std::cout<<"bout to"<<std::endl;
        std::cout<<"inserting " << element <<std::endl;
        if(root->cars[head])
          root->cars[head] = element;
        std::cout<<"done"<<std::endl;
    }

    template<typename E>
    E CDAL<E>::remove_last_element(){
        E element = carnode_at(head)->cars[head%50];
        head = tail = -2;
        return element;
    }

    template<typename E>
    void CDAL<E>::move_up(int position){

        int it = get_free_node_service()-1; //=tail but allocates new array if needed
        carNode<E> * node = carnode_at(it);
        carNode<E> * move_up_node;


        while(it >= position){
            node = carnode_at(it);
            move_up_node[(it+1)%50] = node[it%50];
            move_up_node = node;
            it--;
        }
    }

    template<typename E>
    void CDAL<E>::move_back(int position){
        int it = position + 1;
        carNode<E>* node = carnode_at(it);
        carNode<E> * move_back_node;
        while(it <= tail){
            node = carnode_at(it);
            move_back_node[(it-1) % 50] = node[it%50];
            move_back_node = node;
            it++;
        }
        tail--;
    }

    template<typename E>
    void CDAL<E>::deallocate_unused(){
         std::cout<<"deallocate_unused"<<std::endl;
         std::cout<<"_________________________"<<std::endl;
        int used = (tail - head)/50;
        std::cout<<"used = " << used<<std::endl;
        int unused = 0;
        carNode<E> * node = carnode_at(tail);
        std::cout<<"line 443 does node even EXIST??  " << node->next <<std::endl;
        while(node->next){
            unused++;
            node = node->next;
            std::cout << "unused = " << unused << std::endl;
        }
        std::cout<<"line 447"<<std::endl;
        int todeallocate = 0;
        if(used !=0 ){
             if(unused/used >= 1){
                 todeallocate = unused/2;
               }
          }
        std::cout<<"line 453"<<std::endl;
        node = carnode_at(tail);
        std::cout<<"line 455"<<std::endl;
        while(todeallocate != 0){
            node = node->next;
            todeallocate--;
        }
        node->next = nullptr;
        std::cout<<"_________________________"<<std::endl;
    }

//end of helper functions

//    template<typename E>
//    CDAL<E>::~CDAL() {}

}






#endif //PROJECT1CLION_CDAL_H
