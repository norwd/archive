#include <stdlib.h>
#include <iostream.h>
#include "gen.hxx"
#include "stack.hxx"

const int stackChunk = 256 * sizeof(int32);

Stack::~Stack()
{
  if (bottom)
    free(bottom);
}

void Stack::push(int32 val)
{
  if (!bottom) {
    bottom = (int32*)malloc(stackChunk);
    if (!bottom) {
      ERR = errLowMem;
      return;
    }
    count = stackChunk;
    top = bottom + stackChunk / sizeof(int32);
    SP = bottom;
  } else if (SP == top) {
    count += stackChunk;
    int32 *newStack = (int32*)realloc(bottom, count);
    if (!newStack) {
      count -= stackChunk;
      ERR = errStackOver;
      return;
    }
    bottom = newStack;
    top += stackChunk / sizeof(int32);
  }

  if (debugging)
    cerr << "push: " << val << endl;
  *SP++ = val;
}

int32 Stack::pop()
{
  if (SP == bottom) {
    ERR = errStackUnder;
    return 0;
  } else if (top - SP > stackChunk) {
    count -= stackChunk;
    int32 *newStack = (int32*)realloc(bottom, count);
    if (newStack) {
      bottom = newStack;
      top -= stackChunk / sizeof(int32);
    } else
      count += stackChunk;
  }
  if (debugging)
    cerr << "pop: " << SP[-1] << endl;
  return *--SP;
}

void Stack::display(int nTop /* = 0 */) const
{
  if (!bottom)
    return;

  int n;
  if (nTop && nTop < size())
    n = nTop - 1;
  else
    n = size();
  for (int32 *BP = SP - 1 ; n > 0 ; --BP, --n)
    cerr << *BP << ' ';
  if (nTop && nTop < size())
    cerr << "...";
}
