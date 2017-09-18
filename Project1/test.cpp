#ifndef _TEST_CPP
#define _TEST_CPP
#include "List.h"
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include <iostream>

// #include <cstdio>
#include <vector>

using namespace cop3530;
std::vector<int> a(100);
std::vector<int> b(20);
std::vector<int> c(75);

void setup() {
  int sum = 5;

  for (size_t i = 0; i < a.size(); i++) {
    a[i] = sum;
    sum += 5;
  }
  sum = 0;

  for (size_t i = 0; i < b.size(); i++) {
    b[i] = sum;
    sum += 2;
  }
  sum = 0;

  for (size_t i = 0; i < b.size(); i++) {
    c[i] = sum;
    sum += 3;
  }
}

bool push_pop(List<int> *list) {
  list->push_back(a.at(2));
  list->push_front(a.at(3));
  int i = list->pop_back();
  int j = list->pop_front();
  return i == a.at(3) && j == a.at(2);
}

bool push_insert_remove(List<int> *list)    {}

bool push_peek_print(List<int> *list)       {}

bool push_clear_push(List<int> *list)       {}

bool push_replace_pop(List<int> *list)      {}

bool push_replace_contents(List<int> *list) {}

bool push_length_isempty(List<int> *list)   {}

int  main() {
  List<int> *ssll = new SSLL();
  List<int> *psll = new PSLL();
  List<int> *sdal = new SDAL();
  List<int> *cdal = new CDAL();

  std::vector<*List<int> > lists(4);
  lists[0] = ssll;
  lists[1] = psll;
  list[2]  = sdal;
  lists[3] = cdal;

  for (int i = 0; i < lists.size(); i++) {
    bool push_pop_test              = push_pop(list[i]);
    bool push_insert_remove_test    = push_insert_remove(list[i]);
    bool push_peek_print_test       = push_peek_print(list[i]);
    bool push_clear_push_test       = push_clear_push(list[i]);
    bool push_replace_pop_test      = push_replace_pop(list[i]);
    bool push_replace_contents_test = push_replace_contents(list[i]);
    bool push_length_isempty_test   = push_length_isempty(list[i]);
  }
  std::cout << "push_pop_test = " << push_pop_test << std::endl;
  std::cout << "push_insert_remove_test = " << push_insert_remove_test <<
    std::endl;
  std::cout << "push_peek_print_test = "  << push_peek_print_test << std::endl;
  std::cout << "push_clear_push_test = " << push_clear_push_test << std::endl;
  std::cout << "push_replace_pop_test = " << push_replace_pop_test  << std::endl;
  std::cout << "push_replace_contents_test" << push_replace_contents_test <<
    std::endl;
  std::cout << "push_length_isempty_test" << push_length_isempty_test <<
    std::endl;

  return 0;
}

#endif // ifndef _TEST_CPP
