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

    Node *next = nullptr;
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
void SSLL<E>::insert(E element, size_t position) {
  if (position > 1 + length()) {
    throw std::runtime_error(
            "cannot insert outside of array: position > 1 + length not allowed");
    return;
  }
  else if (position == 0) {
    push_front(element);
    return;
  }
  else if (position == length()) {
    push_back(element);
    return;
  }
  else {
    Node *it = head;
    Node *prev;

    do {
      if (position == 0) {
        Node *toAdd = new Node(elememt);
        prev->next  = toAdd;
        toAdd->next = it;
        return;
      }
      position--;
      prev = it;
      it   = it->next;
    } while (it);
  }
}

template<typename E>
void SSLL<E>::push_back(E element)  {
  Node *toAdd = new Node(element);

  if (head == tail) {
    head = toAdd;
  }
  tail->next = toAdd;
  tail       = toAdd;
}

template<typename E>
void SSLL<E>::push_front(E element) {
  Node *toAdd = new Node(element);

  if (head == tail) {
    tail = toAdd;
  }
  toAdd->next = head;
  head        = toAdd;
}

template<typename E>
void SSLL<E>::replace(E      element,
                      size_t position)  {
  if (position > (length() - 1)) {
    throw std::runtime_error(
            "cannot replace outside of array: position > length-1 not allowed");
    return;
  }
  Node *it = head;

  while (it) {
    if (position == 0) {
      it->data = element;
      return;
    }
    position--;
    it = it->next;
  }
}

template<typename E>
E SSLL<E>::remove(size_t position) {
  if (position > (length() - 2)) {
    throw std::runtime_error(
            "cannot replace outside of array: position > length-1 not allowed");
    return;
  }
  else if (position == length() - 1) {
    return pop_back();
  }
  else if (position == 0) {
    return pop_front();
  }
  Node *it = head;
  Node *prev;
  Node *temp;

  while (it) {
    if (position == 0) {
      temp       = it;
      prev->next = it->next;
      return temp->data;
    }
    position--;
    it   = it->next;
    prev = it;
  }
}

template<typename E>
E SSLL<E>::pop_back(void) {
  if (is_empty()) {
    throw std::runtime_error(
            "cannot pop off empty list");
    return 0;
  }
  Node *prev = head;
  Node *temp = tail;
  Node *it   = head;

  while (it->next) {
    prev = it;
    it   = it->next;
  }
  tail = prev;
  it   = nullptr;
  return temp->data;
}

template<typename E>
E SSLL<E>::pop_front(void) {
  if (is_empty()) {
    throw std::runtime_error(
            "cannot pop off empty list");
    return 0;
  }
  Node *temp = head;
  head = head->next; // could equal nullptr
  return temp->data;
}

template<typename E>
E      SSLL<E>::item_at(size_t position) {
  if (position > (length() - 1)) {
    throw std::runtime_error(
            "cannot find outside of array: position > length-1 not allowed");
    return 0;
  }
  Node *it = head;

  while (it) {
    if (position == 0) {
      return it->data;
    }
    position--;
    it = it->next;
  }
}

template<typename E>
E      SSLL<E>::peek_back(void)  {
  return tail->data;
}

template<typename E>
E      SSLL<E>::peek_front(void) {
  return head->data;
}

template<typename E>
bool   SSLL<E>::is_empty(void)   {
  if (head == tail) {
    return true;
  }
  return false;
}

template<typename E>
bool   SSLL<E>::is_full(void) {
  return false;
}

template<typename E>
size_t SSLL<E>::length(void)          {
  size_t counter = 0;
  Node  *it      = head;

  while (it) {
    counter++;
    it = it->next;
  }
  return counter;
}

template<typename E>
void   SSLL<E>::clear(void) {}

template<typename E>
bool SSLL<E  >::contains(E element,
                         bool (*equals_to_function)(E, E))  {}

template<typename E>
void SSLL<E>::print(std::ostream& os) {}

template<typename E>
E *SSLL<E  >::contents(void)          {}

template<typename E>
SSLL<E>::~SSLL() {}
}


#endif // ifndef _SSLL_H
