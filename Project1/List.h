#ifndef _LIST_H
#define _LIST_H

namespace cop3530 {
template<typename E>
class List {
public:

  // adds the specified element to the list at the specified position, shifting
  // the element originally at that and those in subsequent positions one
  // position to the ”right.“
  virtual void insert(E   element,
                      int position) = 0;

  // appends the specified element to the list.
  virtual void push_back(E element) = 0;

  // prepends the specified element to the list.
  virtual void push_front(E element) = 0;

  // replaces the existing element at the specified position with the specified
  // element and return the original element.
  virtual void replace(E   element,
                       int position) = 0;

  // removes and returns the the element at the specified position, shifting the
  // subsequent elements one position to the ”left.“
  virtual E remove(int position) = 0;

  // removes and returns the element at the list's tail.
  virtual E pop_back(void) = 0;

  // removes and returns the element at the list's head.
  virtual E pop_front(void) = 0;

  // returns (without removing from the list) the element at the specified
  // position.
  virtual E    item_at(int position) = 0;

  // returns the element at the list's tail.
  virtual E    peek_back(void) = 0;

  // returns the element at the list's head.
  virtual E    peek_front(void) = 0;

  // returns true IFF the list contains no elements.
  virtual bool is_empty(void) = 0;

  // returns true IFF the no more elemtns can be added to the list.
  virtual bool is_full(void) = 0;

  // returns the number of elements in the list as a size_t.

  virtual size_t length(void) = 0;

  // removes all elements from the list.
  virtual void   clear(void) = 0;

  // returns true IFF at least one of the elements of the list matches the
  // specified element.
  virtual bool contains(E element,
                        bool (*equals_to_function)(E, E)) = 0;

  // If the list is empty, inserts "<empty list>" into the ostream; otherwise,
  // inserts, enclosed in square brackets, the list's elements, separated by
  // commas, in sequential order.
  virtual void print(std::ostream& os) = 0;

  // Allocates, initializes, and returns an array containing a copy of the
  // list's elements in sequential order.
  virtual E* contents(void) = 0;
};
}
#endif // ifndef LIST_H
