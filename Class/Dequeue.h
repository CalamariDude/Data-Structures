#ifndef DEQUEUE_H
#define DEQUEUE_H

namespace dequeue {
template <typename E>
class Dequeue {
public:
virtual bool is_empty()= 0;
virtual bool is_full()= 0;
virtual int length()= 0;
virtual void clear()= 0;
virtual void push_front(E data) = 0;
virtual void push_back(E data)= 0;
virtual E pop_front()= 0;
virtual E pop_back()= 0;
virtual E peek_front()= 0;
virtual E peek_back()= 0;

  #ifdef DEBUG
virtual E* to_array() = 0;
  #endif

virtual ~Dequeue() {
};
};
}
#endif
