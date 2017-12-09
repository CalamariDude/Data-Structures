#define CATCH_CONFIG_MAIN
#include <iostream>
#include "BSTLEAF.h"
#include "BSTROOT.h"
#include "BSTRAND.h"
#include "AVL.h"
#include "catch.hpp"
using namespace cop3530;
bool IntCompare(int a, int b){
    if (a == b){
        return true;
    }
    return false;
}

bool int_equals(int x, int y){
    return x==y;
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

    return 0;
}



