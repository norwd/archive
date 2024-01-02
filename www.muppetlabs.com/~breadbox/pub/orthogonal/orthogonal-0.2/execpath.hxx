#ifndef __PATH_HXX__
#define __PATH_HXX__

#include "gen.hxx"
#include "gridptr.hxx"
#include "stack.hxx"

typedef enum { stateReady = 0, stateRunning, stateStopped } ExecState;

class ExecutionPath
{
public:
  ExecutionPath(Grid &grid);
  ~ExecutionPath() { }
  bool inmotion() const { return state == stateRunning; }
  bool execute();
  int32 returnval() const { return retval; }
  int32 go() { if (state == stateReady) while (execute()) ; return retval; }

private:
  GridPtr gridptr;
  Stack stack;
  ExecState state;
  int32 retval;
  void push(int32 n) { stack.push(n); }
  int32 pop() { return stack.pop(); }
  void evaluate();
};

#endif
