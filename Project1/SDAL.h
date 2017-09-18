#ifndef _SDAL_H
#define _SDAL_H
#include "List.h"
namespace cop3530 {
template<typename E>
class SDAL : public List<E>{
  size_t head;
  size_t tail;
  std::vector<Node<E> >v(50);
  template<typename E>
  struct Node {
public:

    size_t next;
    E      data;
    Node(E data) {
      this->data = data;
      next       = -1;
    }
  };

  // no ur stupid
  // construcot
  SDAL() {
    head = 0;
    tail = 0;

    for (size_t i = 0; i < 50; i++) {
      Node *add = new Node(nullptr);
      v[i] = add;
    }
  }

  SDAL(size_t size) {
    // errors
    std::vector<Node<E> > a(size);
    v = a;
    delete a;

    head = 0;
    tail = 0;

    for (size_t i = 0; i < size; i++) {
      Node *add = new Node(nullptr);
      v[i] = add;
    }
  }

  // adds the specified element to the list at the specified position, shifting
  // the element originally at that and those in subsequent positions one
  // position to the ”right.“
  void insert(E      element,
              size_t position) override;

  // appends the specified element to the list.
  void push_back(E element)  override;

  // prepends the specified element to the list.
  void push_front(E element)  override;

  // replaces the existing element at the specified position with the specified
  // element and return the original element.
  void replace(E      element,
               size_t position)  override;

  // removes and returns the the element at the specified position, shifting the
  // subsequent elements one position to the ”left.“
  E remove(size_t position)  override;

  // removes and returns the element at the list's tail.
  E pop_back(void)  override;

  // removes and returns the element at the list's head.
  E pop_front(void)  override;

  // returns (without removing from the list) the element at the specified
  // position.
  E      item_at(size_t position)  override;

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

  ˜SDAL() override;

  bool inUse(Node *ptr);
};

// tbd
template<typename E>
void SDAL<E>::insert(E element, size_t position) {
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

// tbd
template<typename E>
void SDAL<E>::push_back(E element)               {
  Node *toAdd = new Node(element);

  if (head == tail) {
    head = toAdd;
  }
  tail->next = toAdd;
  tail       = toAdd;
}

template<typename E>
void SDAL<E>::push_front(E element) {
  Node *toAdd = new Node(element);

  if (head == tail) {
    tail = toAdd;
  }
  toAdd->next = head;
  head        = toAdd;
}

template<typename E>
void SDAL<E>::replace(E      element,
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
E SDAL<E>::remove(size_t position)  {
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
  Node *it   = head;
  Node *prev = head;
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
E SDAL<E>::pop_back(void)           {
  if (is_empty()) {
    throw std::runtime_error(
            "cannot pop off empty list");
    return 0;
  }
  Node *prev = nullptr;
  Node *temp = tail;
  Node *it   = head;

  while (it->next) {
    prev = it;
    it   = it->next;
  }
  tail = prev;

  if (prev) {
    tail->next = nullptr;
  }
  return temp->data;
}

template<typename E>
E SDAL<E>::pop_front(void)          {
  if (is_empty()) {
    throw std::runtime_error(
            "cannot pop off empty list");
    return 0;
  }
  Node *temp = head;

  if (head == tail) {
    head = tail = nullptr;
  }
  else {
    head = head->next; // could equal nullptr
  }
  return temp->data;
}

template<typename E>
E      SDAL<E>::item_at(size_t position) {
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
  return 0;
}

template<typename E>
E      SDAL<E>::peek_back(void)  {
  if (is_empty()) {
    throw std::runtime_error(
            "cannot peek empty list");
    return 0;
  }
  return tail->data;
}

template<typename E>
E      SDAL<E>::peek_front(void) {
  if (is_empty()) {
    throw std::runtime_error(
            "cannot peek empty list");
    return 0;
  }
  return head->data;
}

template<typename E>
bool   SDAL<E>::is_empty(void) {
  if (head == tail) {
    return true;
  }
  return false;
}

template<typename E>
bool   SDAL<E>::is_full(void) {
  return false;
}

template<typename E>
size_t SDAL<E>::length(void) {
  size_t counter = 0;
  Node  *it      = head;

  while (it) {
    counter++;
    it = it->next;
  }
  return counter;
}

template<typename E>
void   SDAL<E>::clear(void) {
  // could cause memory leak
  head = nullptr;
  tail = nullptr;
}

template<typename E>
bool SDAL<E>::contains(E element,
                       bool (*equals_to_function)(E, E))  {
  Node *it = head;

  while (it) {
    if (equals_to_function(it->data, element)) {
      return true;
    }
    it = it->next;
  }
  return false;
}

template<typename E>
void SDAL<E>::print(std::ostream& os) {
  std::string str = "";

  while (it != -1) {
    str += to_string(v.at(it)->data) + " ";
    it   = v.at(it)->next;
  }
  os << str << endl;
}

template<typename E>
E *SDAL<E>::contents(void) {
  size_t len = length();

  E[len] * elements;
  size_t counter = 0;
  size_t it      = head;

  while (it != -1) {
    e[counter] = v.at(it)->data;
    it         = v.at(it)->next;
    counter++;
  }
  return elements;
}

template<typename E>
SDAL<E>::~SDAL() {
  head = nullptr;
  tail = nullptr;
}
}
#endif // ifndef _SDAL_H
