#define CATCH_CONFIG_MAIN
#include <iostream>
#include "BSTLEAF.h"
#include "BSTROOT.h"
#include "BSTRAND.h"
#include "AVL.h"
#include "catch.hpp"
using namespace cop3530;
bool int_compare(int x, int y){
    if(x <  y){
        return true;
    }
    return false;
}
bool int_equals(int x, int y){
    return x==y;
}

TEST_CASE( "BSTLEAF test", "testing for insertion and removal" ) {


    BSTLEAF<int, int, int_compare, int_equals> * leaf = new BSTLEAF<int, int, int_compare, int_equals>();
    leaf->insert(2,1);
    leaf->insert(3,4);
    leaf->insert(4,5);
    int value = leaf->lookup(3);
    REQUIRE(value == 4);
    leaf->remove(3);
    value = leaf->lookup(3);
    REQUIRE(value != 4);

}


TEST_CASE( "BSTROOT test", "testing for insertion and removal" ) {


    BSTROOT<int, int, int_compare, int_equals> * leaf = new BSTROOT<int, int, int_compare, int_equals>();
    leaf->insert(2,1);
    leaf->insert(3,4);
    leaf->insert(4,5);
    int value = leaf->lookup(3);
    REQUIRE(value == 4);
    leaf->remove(3);
    value = leaf->lookup(3);
    REQUIRE(value != 4);

}

TEST_CASE( "BSTRAND test", "testing for insertion and removal" ) {


    BSTRAND<int, int, int_compare, int_equals> * leaf = new BSTRAND<int, int, int_compare, int_equals>();
    leaf->insert(2,1);
    leaf->insert(3,4);
    leaf->insert(4,5);
    int value = leaf->lookup(3);
    REQUIRE(value == 4);
    leaf->remove(3);
    value = leaf->lookup(3);
    REQUIRE(value != 4);

}



TEST_CASE( "AVL test", "testing for insertion and removal" ) {


    AVL<int, int, int_compare, int_equals> * leaf = new AVL<int, int, int_compare, int_equals>();
    leaf->insert(2,1);
    leaf->insert(3,4);
    leaf->insert(4,5);
    int value = leaf->lookup(3);
    REQUIRE(value == 4);
    leaf->remove(3);
    value = leaf->lookup(3);
    REQUIRE(value != 4);

}





