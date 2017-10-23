//
// Created by Jad Zeineddine on 10/18/17.
//

#ifndef BINARYTREE_BINARYTT_H
#define BINARYTREE_BINARYTT_H

#include <iostream>
#include <math.h>
template <typename  E>
class binaryTT{
public:
    struct Node{
        E value;
        Node * right;
        Node * left;
        Node(E value){
            this->value = value;
        }
    };

    Node * root;
    Node * curr;
    binaryTT(E * arr[], int length){
        // child = 2n & 2n + 1
        // parent = n/2
        E * ptrarr[length];
        for(int i = 0; i < length; i++){
            Node * node;
            if(arr[i]){
                node->value = arr[i];
            }
            ptrarr[i] = arr[i];
        }
        
        root->value = arr[0];
        int counter = 0;
        while( (pow((double) 2, (double) counter)) < length ) {
            counter++;

        }

    }
    binaryTT(Node * root){
        this->root = root;
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

    void morris_solution_inorder(){
     Node * anchor = root;
        while(anchor){
            if(!anchor->left){
                process(anchor);
                anchor = anchor->right;
            }
            else {
                Node *iop = anchor->left;
                while(iop->right != nullptr && iop->right != anchor){
                    iop = iop->right;
                }
                if (iop->right == anchor) {
                    iop->right = nullptr;
                    anchor = anchor->right;
                } else {
                    process(anchor);
                    iop->right = anchor;
                    anchor = anchor->left;
                }
            }
        }
    }

    void process(Node * ptr){
        std::cout<< ptr->value << std::endl;
    }
};
#endif //BINARYTREE_BINARYTT_H
