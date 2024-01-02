#include <iostream.h>
#include "error.hxx"

void Err::report()
{
  if (_err == errNone)
    return;
  cerr << "Error";
  if (usexy)
    cerr << ": (" << x << "," << y << ")";
  if (useline) {
    if (usexy)
      cerr << ", ";
    else
      cerr << ": ";
    cerr << "line " << line;
  }
  cerr << ": ";
  switch (_err) {
  case errLowMem:
    cerr << "Out of memory.";
    break;
  case errSyntax:
    cerr << "Syntax error.";
    break;
  case errPPSyntax:
    cerr << "Syntax error.";
    break;
  case errPPRSyntax:
    cerr << "Syntax error.";
    break;
  case errPPOffGrid:
    cerr << "Bad co-ordinates.";
    break;
  case errOffGrid:
    cerr << "Attempted access outside the grid.";
    break;
  case errIPOffGrid:
    cerr << "Execution has left the grid.";
    break;
  case errRedefine:
    cerr << "Defined twice.";
    break;
  case errExcessVals:
    cerr << "Too many values defined.";
    break;
  case errBadValName:
    cerr << "Illegal value name.";
    break;
  case errBadValAssign:
    cerr << "Illegal value assignment.";
    break;
  case errEmpty:
    cerr << "No contents.";
    break;
  case errStackOver:
    cerr << "Stack overflow.";
    break;
  case errStackUnder:
    cerr << "Stack underflow.";
    break;
  case errBadPushVal:
    cerr << "Cannot push a non-value.";
    break;
  case errNoProgram:
    cerr << "Cannot access program file.";
    break;
  case errInternal:
    cerr << "Interpreter error.";
    break;
  case errNone:
    cerr << "No error.";
    break;
  }
  cerr << endl;
}
