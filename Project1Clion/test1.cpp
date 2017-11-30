#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CBL.h"
#include "List.h"
using namespace cop3530;
bool IntCompare(int a, int b){
    if (a == b){
        return true;
    }
    return false;
}

TEST_CASE( "push_pop test", "popping 5 " ) {
    List<int> *list = new CBL<int>;
    list->push_back(3);
    list->push_front(5);
    std::cout << " here1234 + " << list->length() << std::endl;
    REQUIRE(list->pop_back() == 3);
    list->clear();
    list->push_back(5);
    list->insert(5, 0);
    REQUIRE(list->remove(0) == 5);
    list->clear();
    list->replace(5, 1);
    REQUIRE(5 == list->item_at(1));
    list->clear();
    list->push_back(5);
    list->replace(5, 0);
    int *arr = list->contents();
    REQUIRE(arr[0] == 5);
    list->clear();
    list->push_back(5);
    list->pop_back();
    REQUIRE(list->is_empty());
    list->clear();
    list->push_back(0);
    list->push_front(3);
    list->push_back(9);
    REQUIRE(list->contains(3, IntCompare));
}



