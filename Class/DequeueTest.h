#ifndef DEQUEUETEST_H
#define DEQUEUETEST_H
#include "Bounded_Dequeue.h"
#include <iostream>
#include <stdexcept>

using namespace std;


bool test_enqueue(){
        dequeue::Bounded_Dequeue <int> deck(5);
        deck.push_front(3);
        cout << deck.pop_front() << endl;
        return true;
}

int main(){
        test_enqueue();
        return 0;
}

#endif
