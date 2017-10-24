//
// Created by Jad Zeineddine on 10/24/17.
//

#ifndef BINARYTREE_HEAP_H
#define BINARYTREE_HEAP_H


template <typename E>
class Heap{
public:
    struct Node{
        Node * right;
        Node * left;
        E value;
        Node(E value){
            this->value = value;
        }

    };
    Heap(E * arr[], int length){
        
        }

};


#endif //BINARYTREE_HEAP_H
