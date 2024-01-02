#ifndef __STACK_HXX__
#define __STACK_HXX__

#include "gen.hxx"

class Stack
{
public:
  Stack() : bottom(NULL), count(0) { }
  ~Stack();
  void push(int32 val);
  int32 pop(void);
  int size() const { return SP - bottom; }
  void display(int nTop = 0) const;

private:
  int32 *bottom;
  int32 *SP;
  int32 *top;
  int count;
};

#endif
