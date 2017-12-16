//
// Created by Jad Zeineddine on 12/7/17.
//

#ifndef PROJECT_2_BSTROOT_H
#define PROJECT_2_BSTROOT_H


#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
namespace cop3530 {

    //this tree does not balance
    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>

    class BSTROOT {
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
        BSTROOT() {}

        //copy constructor
        BSTROOT(const BSTROOT& bstroot) {
            //iterate and push back new data
            lot(bstroot->root);
        }

        void lot(Node * root){
            if(root){
                insert(root->key, root->value);
                lot(root->right);
                lot(root->left);
            }
        }

        //copy assigment constructor
        BSTROOT& operator=(const BSTROOT& bstleaf) {
            if (&bstleaf== this)
                return *this;
            else {
                lot(bstleaf->root);
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
        ~BSTROOT(){
            lot_del(root);
            root = nullptr;
        }

    private:
        bool is_empty();
        Node * insert_at_root(K key, V value, Node * curr);
        V &find(K key, Node * curr);
        Node * find_min(Node * curr);
        void remover(K key, Node * curr);
        Node * RR(Node * curr);
        Node * LL(Node * curr);
    };

    //sorry terrible insert method.
    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    void BSTROOT<K,V,Cp,Eq>::insert(K key, V value) {
        Node * node = new Node(key, value);
        if(is_empty()){
            root = node;
            return;
        }
        root = insert_at_root(key, value, root); //changes root and adds the node
    }


    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    typename BSTROOT<K,V,Cp,Eq>::Node * BSTROOT<K,V,Cp,Eq>::insert_at_root(K key, V value, Node * curr){
        if(!curr){
            return new Node(key,value);
        }
        else if(Eq(curr->key, key )){
            curr->value = value;
            return RR(root);
        }
        else if(Cp(key , curr->key)){
            curr->left = insert_at_root(key,value,curr->left);
            return RR(root);
        }
        else{
            curr->right = insert_at_root(key,value, curr->right);
            return LL(root);
        }
    }



    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    void BSTROOT<K,V,Cp,Eq>::remove(K key){
        if(is_empty()){
            throw std::runtime_error("cannot remove in empty list");
        }
        else{
            remover(key, root);
        }
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    void BSTROOT<K,V,Cp,Eq>::remover(K key, Node * curr)
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
    V& BSTROOT<K,V,Cp,Eq>::lookup(K key) {
        if(is_empty()){
            throw std::runtime_error("cannot lookup in empty list");
        }
        return find(key, root);
    }


    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    V& BSTROOT<K,V,Cp,Eq>::find(K key, Node * curr){
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
    bool BSTROOT<K,V,Cp,Eq>::is_empty(){
        if(root){
            return false;
        }
        return true;
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    typename BSTROOT<K,V,Cp,Eq>::Node * BSTROOT<K,V,Cp,Eq>::find_min(Node * curr){
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
    typename BSTROOT<K,V,Cp,Eq>::Node * BSTROOT<K,V,Cp,Eq>::LL(Node * curr){
        Node * temp = curr;
        curr = curr->right;
        temp->right = curr->left;
        curr->left= temp;
        return curr;
    }

    template<typename K, typename V, bool (*Cp)(K,K), bool (*Eq)(K,K)>
    typename BSTROOT<K,V,Cp,Eq>::Node *  BSTROOT<K,V,Cp,Eq>::RR(Node * curr){
        Node * temp = curr;
        curr = curr->left;
        temp->left = curr->right;
        curr->right= temp;
        return curr;
    }

}





#endif //PROJECT_2_BSTROOT_H
