//
// Created by Jad Zeineddine on 12/7/17.
//

#ifndef PROJECT_2_AVL_H
#define PROJECT_2_AVL_H

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
namespace cop3530 {

    //this tree does not balance
    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>

    class AVL {
    public:
        struct Node {
            K key;
            V value;
            Node * right = nullptr;
            Node * left = nullptr;

            Node() {}

            Node(K key, V value) : key(key), value(value) {
            }

            ~Node() {
                K newkey;
                key = newkey;
                V newval;
                value = newval;
                right = nullptr;
                left = nullptr;
            }

        };

        Node * root = nullptr;

        void insert(K key, V value); //adds the specified key-value pair to the map.
        void remove(K key); //removes the specified key-value pair associated with the key.
        V &lookup(K key); //returns a reference to the value associated with the key.


        //move operators
        V& operator[](K key) {
            return lookup(key);
        }

        //move operators
        V const& operator[](K key) const {
            return lookup(key);
        }

        //default
        AVL() {}

        //copy constructor
        AVL(const AVL& avl) {
            //iterate and push back new data
            lot(avl->root);
        }

        void lot(Node * root){
            if(root){
                insert(root->key, root->value);
                lot(root->right);
                lot(root->left);
            }
        }

        //copy assigment constructor
        AVL& operator=(const AVL& avl) {
            if (&avl== this)
                return *this;
            else {
                lot(avl->root);
                return *this;
            }
        }
        void lot_del(Node * root){
            if(root){
                lot(root->right);
                lot(root->left);
                delete root;
            }
        }
        ~AVL(){
            lot_del(root);
            root = nullptr;
        }

    private:
        bool is_empty();
        Node * insert_helper(K key, Node * curr);
        V &find(K key, Node * curr);
        Node * find_min(Node * curr);
        void remover(K key, Node * curr);
        size_t size(Node * curr);
        Node * RR(Node * curr);
        Node * LL(Node * curr);
        size_t depth(Node * curr);
        void balance();
    };

    //sorry terrible insert method.
    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    void AVL<K,V,Cp,Eq>::insert(K key, V value) {
        Node * node = new Node(key, value);
        if(is_empty()){
            root = node;
            return;
        }
        Node * curr = insert_helper(key, root);
        if(Eq(curr->key, key)){
            curr->value = value; //replace
        }
        else if(Cp(curr->key, key)){
            curr->right = node;//logic might again be wrong here
        }
        else{
            curr->left = node;//logic could be wrong here
        }
        std::cout<<"balance"<<std::endl;
        balance();
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    typename AVL<K,V,Cp,Eq>::Node * AVL<K,V,Cp,Eq>::insert_helper(K key, Node * curr)
    {
        //returns pointer to most appropriate leaf to insert the element

        if(Eq(curr->key, key)){
            return curr;
        }
        if(Cp(curr->key, key)){
            if(curr->right){
                return insert_helper(key, curr->right);
            }
            return curr;
        }
        else{
            if(curr->left){
                return insert_helper(key, curr->left);
            }
            return curr;
        }
    }



    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    typename AVL<K,V,Cp,Eq>::Node * AVL<K,V,Cp,Eq>::LL(Node * curr){
        Node * temp = curr;
        curr = curr->right;
        temp->right = curr->left;
        curr->left= temp;
        return curr;
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    typename AVL<K,V,Cp,Eq>::Node *  AVL<K,V,Cp,Eq>::RR(Node * curr){
        Node * temp = curr;
        curr = curr->left;
        temp->left = curr->right;
        curr->right= temp;
        return curr;
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    void AVL<K,V,Cp,Eq>::remove(K key){
        if(is_empty()){
            throw std::runtime_error("cannot remove in empty list");
        }
        else{
            remover(key, root);
        }
        balance();
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    void AVL<K,V,Cp,Eq>::remover(K key, Node * curr)
    {
        if(!curr){
            throw std::runtime_error("cannot remove non-existing key");
        }
        if(Eq(key, curr->key)){
            Node * temp = find_min(curr->right);
            if (temp){
                curr->key= temp->key;
                curr->value= temp->value;
                delete temp;
                return;
            }
            else
            {
                delete curr;
                return;
            }
        }
        else if(Cp(curr->key, key)){
            remover(key, curr->right);//prob wrong tbh
        }
        else{
            remover(key, curr->left);//prob wrong tbh
        }
    }


    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    V& AVL<K,V,Cp,Eq>::lookup(K key) {
        if(is_empty()){
            throw std::runtime_error("cannot lookup in empty list");
        }
        return find(key, root);
    }


    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    V& AVL<K,V,Cp,Eq>::find(K key, Node * curr){
        V v;
        if(!curr){
            return v;
        }
        if(Eq(key, curr->key)){
            return curr->value;
        }
        if(Cp(key, curr->key)){
            return find(key, curr->left);//prob wrong tbh
        }
        else{
            return find(key, curr->left);//prob wrong tbh
        }
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    bool AVL<K,V,Cp,Eq>::is_empty() {
        if (root) {
            return false;
        }
        return true;
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    typename AVL<K,V,Cp,Eq>::Node * AVL<K,V,Cp,Eq>::find_min(Node * curr){
        if(!curr){
            return nullptr;
        }
        else{
            while(curr->left){
                curr = curr->left;
            }
            return curr;
        }
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    size_t AVL<K,V,Cp,Eq>::size(Node * curr){
        if (!curr) {
            return 0;
        }
        else {
            return ( size ( curr -> left ) + 1 + size(curr->right));
        }
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    size_t AVL<K,V,Cp,Eq>::depth(Node * curr){
    if (!curr) {
        return 0;
    }
    else {
        size_t left = depth(curr->left);
        size_t right = depth(curr->right);

        if (right > left)
            return (++right);
        else {
            return (++left);
            }
        }
    }



    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    void AVL<K,V,Cp,Eq>::balance(){
        size_t right = depth(root->right);
        size_t left = depth(root->left);
        if(right > left + 1 ){
            root = LL(root);
        }
        else if(left > right + 1){
            root = RR(root);
        }
      //else do nothing, balanced
    }

}





#endif //PROJECT_2_AVL_H
