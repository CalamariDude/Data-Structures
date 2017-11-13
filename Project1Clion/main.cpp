#ifndef _MAIN_CPP
#define _MAIN_CPP
#define DEBUG
 #include "List.h"
 #include "SSLL.h"
 #include "PSLL.h"
 // #include "SDAL.h"
#include "CDAL.h"
#include <iostream>
#include <vector>

// #include <cstdio>

using namespace cop3530;
std::vector<int> a(100);
std::vector<int> b(20);
std::vector<int> c(75);

void setup(List<int> *list) {
    list->clear();
}

bool push_pop(List<int> *list) {
     std::cout << "push_pop testing :" << std::endl;
    setup(list);
    std::cout << "push_pop" << std::endl;
    list->push_back(5);
    list->push_back(5);
    list->push_back(5);
    list->push_back(5);
    int i = list->pop_back();
    std::cout << "push_pop pushbackdone" << std::endl;
    int j = list->pop_front();
    return i == 5 && j == 5;
}

bool push_insert_remove(List<int> *list)    {
    setup(list);
    std::cout << "push_insert_remove" << std::endl;
    list->push_back(5);
    list->push_front(5);
    list->insert(5, 1);
    int i = list->remove(1);
    return i==5;
}

 bool push_peek_print(List<int> *list)       {
     setup(list);
     std::cout << "push_peek_print" << std::endl;
     list->push_back(5);
     int i = list->peek_back();
     int j = list->peek_front();
     list->print(std::cout);
     return i==j;
 }

 bool push_clear_push(List<int> *list)       {
     setup(list);
     std::cout << "push_clear_push" << std::endl;
     list->push_back(5);
     list->push_back(5);
     list->push_back(5);
     list->clear();
     return list->is_empty();
 }

 bool push_replace_pop(List<int> *list)      {
     setup(list);
     std::cout << "push_replace_pop" << std::endl;
     list->push_back(5);
     list->push_back(5);
     list->push_back(5);
     list->replace(5, 1);
     return 5 == list->item_at(1);
 }

 bool push_replace_contents(List<int> *list) {
     setup(list);
     std::cout << "push_replace_contents" << std::endl;
     list->push_back(5);
     list->replace(5, 0);
     int *arr = list->contents();
     return arr[0] == 5;
 }

 bool push_length_isempty(List<int> *list)   {
     std::cout << "push_length_isempty" << std::endl;
     setup(list);
//     std::cout<<"________________________________________________"<<std::endl;
//     list->printVector();
//     std::cout<<"________________________________________________"<<std::endl;
     list->clear();
     list->push_back(5);
     std::cout<<"__________________________________________"<<std::endl;
     list->printVector();
     list->pop_back();
     std::cout<<"__________________________________________"<<std::endl;
     list->printVector();

     return(list->is_empty() || list->length( ) == 0);
 }

int main() {
//     List<int> *ssll = new SSLL<int>();
//     List<int> *psll = new PSLL<int> ();
     // List<int> * sdal = new SDAL<int> ();
    List<int> *cdal = new CDAL<int> ();
    std::vector<List<int>  * > lists;
//    lists.push_back(ssll);
//     lists.push_back(psll);
     // lists.push_back(sdal);
    lists.push_back(cdal);
    for (int i = 0; i < lists.size(); i++) {
         bool push_pop_test           = push_pop(lists.at(i));
         // bool push_insert_remove_test = push_insert_remove(lists.at(i));
         // bool push_peek_print_test       = push_peek_print(lists.at(i));
         // bool push_clear_push_test       = push_clear_push(lists.at(i));
         // bool push_replace_pop_test      = push_replace_pop(lists.at(i));
         // bool push_replace_contents_test = push_replace_contents(lists.at(i));
         // bool push_length_isempty_test   = push_length_isempty(lists.at(i));
//        std::cout << "list num " << i << std::endl;
       std::cout << "push_pop_test = " << push_pop_test << std::endl;
//        std::cout << "push_insert_remove_test = " << push_insert_remove_test <<
//                  std::endl;
//         std::cout << "push_peek_print_test = "  << push_peek_print_test <<
//         std::endl;
//         std::cout << "push_clear_push_test = " << push_clear_push_test <<
//         std::endl;
//         std::cout << "push_replace_pop_test = " << push_replace_pop_test  <<
//           std::endl;
//         std::cout << "push_replace_contents_test = " << push_replace_contents_test
//         <<
//           std::endl;
         // std::cout << "push_length_isempty_test = " << push_length_isempty_test << std::endl;
        std::cout << std::endl;
        // if (push_pop_test && push_insert_remove_test && push_peek_print_test  && push_clear_push_test  && push_replace_pop_test  && push_replace_contents_test && push_length_isempty_test){
            std::cout << "all tests passed for list " << i << std::endl;
        // }
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
