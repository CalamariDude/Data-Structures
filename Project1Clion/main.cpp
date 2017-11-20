#ifndef _MAIN_CPP
#define _MAIN_CPP
//#define DEBUG
#include "List.h"
#include "SSLL.h"
#include "PSLL.h"
 #include "SDAL.h"
#include "CDAL.h"
#include "CBL.h"
#include <iostream>
#include <vector>
#include <stack>

// #include <cstdio>

using namespace cop3530;
std::vector<int> a(100);
std::vector<int> b(20);
std::vector<int> c(75);

void setup(List<int> *list) {
    list->clear();
}

bool push_pop(List<int> *list) {
    setup(list);
    std::cout << "running push_pop test..." << std::endl;
    list->push_back(5);
    list->print(std::cout);
    list->push_back(5);
    list->print(std::cout);
    list->push_back(5);
    list->print(std::cout);
    int i = list->pop_back();
    int j = list->pop_front();
    std::cout<<"i = " << i << " j = " << j <<std::endl;

    return i == 5 && j == 5;
}

bool push_insert_remove(List<int> *list)    {
    setup(list);
    std::cout << "running push_insert_remove test..." << std::endl;
    list->push_back(5);
    list->push_front(5);
    list->insert(5, 1);
    int i = list->remove(1);
    return i==5;
}

bool push_peek_print(List<int> *list)       {
    setup(list);
    std::cout << "running push_peek_print test..." << std::endl;
    list->push_back(5);
    int i = list->peek_back();
    int j = list->peek_front();
    list->print(std::cout);
    return i==j;
}

bool push_clear_push(List<int> *list)       {
    setup(list);
    std::cout << "running push_clear_push test..." << std::endl;
    list->push_back(5);
    list->push_back(5);
    list->push_back(5);
    list->clear();
    return list->is_empty();
}

bool push_replace_pop(List<int> *list)      {
    setup(list);
    std::cout << "running push_replace_pop test..." << std::endl;
    list->push_back(5);
    list->push_back(5);
    list->push_back(5);
    list->replace(5, 1);
    return 5 == list->item_at(1);
}

bool push_replace_contents(List<int> *list) {
    setup(list);
    std::cout << "running push_replace_contents test..." << std::endl;
    list->push_back(5);
    list->replace(5, 0);
    int *arr = list->contents();
    return arr[0] == 5;
}

bool push_length_isempty(List<int> *list)   {
    setup(list);
    std::cout << "running push_length_isempty test..." << std::endl;
    list->clear();
    list->push_back(5);
    list->pop_back();

    return(list->is_empty() || list->length( ) == 0);
}


bool IntCompare(int a, int b){
    if (a == b){
        return true;
    }
    return false;
}

bool push_contains(List<int> *list)   {
    setup(list);
    std::cout << "running push_contains_remove test..." << std::endl;
    list->push_back(5);
    list->push_back(3);
    return list->contains(3, IntCompare);
}


bool all_pass(std::vector<bool> res){
    int len = res.size();
    for(int i = 0; i < len; i++){
        if(!res[i]){
            return false;
        }
    }
    return true;
}

std::string result(bool val){
 if(val) return "PASS";
return "FAIL";
}


int main() {
     List<int> *ssll = new SSLL<int>();
     List<int> *psll = new PSLL<int> ();
    List<int> * sdal = new SDAL<int> ();
    List<int> *cdal = new CDAL<int>();
    List<int> *cbl = new CBL<int>();
    std::vector<List<int> *> lists;
    lists.push_back(ssll);
    lists.push_back(psll );
    lists.push_back(sdal);
    lists.push_back(cdal);
    lists.push_back(cbl);
    //Hello
    //hello 2
    for (int i = 0; i < lists.size(); i++) {
        std::vector< bool > testsPassed;
        std::cout << "\n\n_________________________________________" << std::endl;
        std::cout << "\tTESTING LIST NUMBER: " << i <<
                "\n_________________________________________" <<std::endl;

//        testsPassed.push_back(push_pop(lists.at(i)));
        testsPassed.push_back(push_insert_remove(lists.at(i)));
        testsPassed.push_back(push_peek_print(lists.at(i)));
        testsPassed.push_back(push_clear_push(lists.at(i)));
        testsPassed.push_back(push_replace_pop(lists.at(i)));
        testsPassed.push_back(push_replace_contents(lists.at(i)));
        testsPassed.push_back(push_length_isempty(lists.at(i)));
        testsPassed.push_back(push_contains(lists.at(i)));

        std::cout << "RESULTS:\n";
        std::cout << "_________________________________________\n";
        std::cout << "push_pop_test = \t\t\t\t"                 << result(testsPassed[0]) << std::endl;
        std::cout << "push_insert_remove_test = \t\t"       << result(testsPassed[1])<< std::endl;
        std::cout << "push_peek_print_test = \t\t\t"          << result(testsPassed[2]) << std::endl;
        std::cout << "push_clear_push_test = \t\t\t"          << result(testsPassed[3])<< std::endl;
        std::cout << "push_replace_pop_test = \t\t"         << result(testsPassed[4])<< std::endl;
        std::cout << "push_replace_contents_test = \t"    <<  result(testsPassed[5])<< std::endl;
        std::cout << "push_length_isempty_test = \t\t"      << result(testsPassed[6])<< std::endl;
        std::cout << "push_contains_test = \t\t\t"            << result(testsPassed[7])<< std::endl;
        std::cout << "_________________________________________\n";
        std::cout << "ALL TESTS PASSING? = \t\t\t"              << result(all_pass(testsPassed)) << std::endl;
        std::cout << "_________________________________________" << std::endl;

    }
    return 0;
}
#endif // ifndef _TEST_CPP
#ifdef never
//compile only
g++ -std=c++11 main.cpp -o main
//run only
./main
//compile and run
g++ -std=c++11 main.cpp -o main && ./main
#endif
