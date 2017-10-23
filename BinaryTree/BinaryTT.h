//
// Created by Jad Zeineddine on 10/18/17.
//

#ifndef BINARYTREE_BINARYTT_H
#define BINARYTREE_BINARYTT_H

#include <iostream>

template <typename  E>
class binaryTT{
private:
    struct Node{
        E value;
        Node * right;
        Node * left;
        Node(E value){
            this->value = value;
        }
    };


public:
    Node * root;
    Node * curr;
    binaryTT(int arr[], int length){

    }

    void traverse_right(){
        if(curr->right){
            curr = curr->right;
        }
    }
    void traverse_left(){
        if(curr->left){
            curr = curr->right;
        }
    }
    void remove_left(){
        if(curr->left){
            delete curr->left;
            curr->left = nullptr;
            }
    }
    void remove_right(){
        if(curr->right){
            delete curr->right;
            curr->right= nullptr;
        }
    }
    void insert_left(E value){
        if(!curr->left){
            Node * toInsert(value);
            curr->left = toInsert;
        }

    }
    void insert_right(E value){
        if(!curr->right){
            Node * toInsert(value);
            curr->right= toInsert;
        }
    }

    void Morris_Solution(){
     Node * anchor = root;
        while(anchor){
            if(!anchor->left){
                process(anchor);
                anchor = anchor->right;
            }
            else
                //find iop
            if(iop->right == anchor){
                iop->right = nullptr;
                anchor = anchor->right;
            }
            else{
                process(anchor);
                iop->right = anchor;
                anchor = anchor->left;
            }
        }
    }

    void process(Node * ptr){
        std::cout<< ptr->value << std::endl;
    }
};
#endif //BINARYTREE_BINARYTT_H
