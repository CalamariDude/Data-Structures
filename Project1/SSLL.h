#ifndef _SSLL_H
#define _SSLL_H
#include "List.h"
namespace cop3530 {
template<typename E>
class SSLL : public List<E>{
  Node *head;
  Node *tail;

  template<typename E>
  struct Node {
public:

    Node *next;
    E     data;
    Node(E data) {
      this->data = data;
      next       = nullptr;
    }
  };

  // adds the specified element to the list at the specified position, shifting
  // the element originally at that and those in subsequent positions one
  // position to the ”right.“
  void insert(E   element,
              int position) override;

  // appends the specified element to the list.
  void push_back(E element)  override;

  // prepends the specified element to the list.
  void push_front(E element)  override;

  // replaces the existing element at the specified position with the specified
  // element and return the original element.
  void replace(E   element,
               int position)  override;

  // removes and returns the the element at the specified position, shifting the
  // subsequent elements one position to the ”left.“
  E remove(int position)  override;

  // removes and returns the element at the list's tail.
  E pop_back(void)  override;

  // removes and returns the element at the list's head.
  E pop_front(void)  override;

  // returns (without removing from the list) the element at the specified
  // position.
  E      item_at(int position)  override;

  // returns the element at the list's tail.
  E      peek_back(void)  override;

  // returns the element at the list's head.
  E      peek_front(void)  override;

  // returns true IFF the list contains no elements.
  bool   is_empty(void)  override;

  // returns true IFF the no more elemtns can be added to the list.
  bool   is_full(void)  override;

  // returns the number of elements in the list as a size_t.
  size_t length(void)  override;

  // removes all elements from the list.
  void   clear(void)  override;

  // returns true IFF at least one of the elements of the list matches the
  // specified element.
  bool contains(E element,
                bool (*equals_to_function)(E, E))  override;

  // If the list is empty, inserts "<empty list>" into the ostream; otherwise,
  // inserts, enclosed in square brackets, the list's elements, separated by
  // commas, in sequential order.
  void print(std::ostream& os)  override;

  // Allocates, initializes, and returns an array containing a copy of the
  // list's elements in sequential order.
  E* contents(void)  override;

  ˜SSLL() override;
};
template<typename E>
void SSLL<E>::insert(E element, int position) {}

void SSLL<E>::push_back(E element)            {}


void SSLL<E>::push_front(E element)           {}


void SSLL<E>::replace(E   element,
                      int position)  {}


E SSLL<E     >::remove(int position)  {}


E SSLL<E     >::pop_back(void)        {}


E SSLL<E     >::pop_front(void)       {}


E      SSLL<E>::item_at(int position) {}


E      SSLL<E>::peek_back(void)       {}


E      SSLL<E>::peek_front(void)      {}


bool   SSLL<E>::is_empty(void)        {}


bool   SSLL<E>::is_full(void)         {}


size_t SSLL<E>::length(void)          {}


void   SSLL<E>::clear(void)           {}


bool SSLL<E  >::contains(E element,
                         bool (*equals_to_function)(E, E))  {}


void SSLL<E>::print(std::ostream& os) {}


E *SSLL<E  >::contents(void)          {}

SSLL<E>::~SSLL() {}
}


#endif // ifndef _SSLL_H
