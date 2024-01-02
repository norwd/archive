#include <iostream.h>
#include <strstream.h>
#include <iomanip.h>
#include "gen.hxx"
#include "grid.hxx"
#include "gridptr.hxx"
#include "stack.hxx"
#include "parser.hxx"
#include "execpath.hxx"

ExecutionPath::ExecutionPath(Grid &g)
 : gridptr(g), state(stateReady), retval(-1)
{
  if (debugging)
    cerr.flags(ios::left);
}

void ExecutionPath::evaluate()
{
  int32 t1, t2;

  switch (gridptr.cell()->op()) {
  case opNop:								break;
  case opPlus:	push(pop() + pop());					break;
  case opMinus:	t1 = pop(); push(pop() - t1);				break;
  case opMult:	push(pop() * pop());					break;
  case opDiv:	t1 = pop(); push(pop() / t1);				break;
  case opMod:	t1 = pop(); push(pop() % t1);				break;
  case opNot:	push(pop() ? 0 : 1);					break;
  case opAnd:	push(pop() & pop());					break;
  case opOr:	push(pop() | pop());					break;
  case opXor:	push(pop() ^ pop());					break;
  case opExch:	t1 = pop(); t2 = pop(); push(t1); push(t2);		break;
  case opDup:	t1 = pop(); push(t1); push(t1);				break;
  case opDisc:	(void)pop();						break;
  case opChar:	t1 = pop(); cout << (t1 ? (char)t1 : '\n');		break;
  case opStr:	while ((t1 = pop()) != 0) cout << (char)t1;		break;
  case opDec:	cout << pop();						break;
  case opX:	gridptr.isetpos(pop(), gridptr.getY());			break;
  case opY:	gridptr.isetpos(gridptr.getX(), pop());			break;
  case opDX:	gridptr.setdelta(pop(), gridptr.getDY());		break;
  case opDY:	gridptr.setdelta(gridptr.getDX(), pop());		break;
  case opCW:	gridptr.setdelta(-gridptr.getDY(), gridptr.getDX());	break;
  case opCCW:	gridptr.setdelta(gridptr.getDY(), -gridptr.getDX());	break;
  case opRev:	gridptr.setdelta(-gridptr.getDX(), -gridptr.getDY());	break;
  case opLeft:	gridptr.setdelta(-1, 0);				break;
  case opRight:	gridptr.setdelta(1, 0);					break;
  case opUp:	gridptr.setdelta(0, -1);				break;
  case opDown:	gridptr.setdelta(0, 1);					break;
  case opIf:	if (!pop()) gridptr.imove();				break;
  case opRet:	retval = pop(); state = stateStopped;			break;

  case opPush:
    {
      int pushX = pop();
      int pushY = pop();
      if (pushX < 0 || pushY < 0) {
	ERR = errOffGrid;
	break;
      }
      Cell const *other = gridptr.getgrid().getcell(pushX, pushY);
      if (!other || other->type() != typeValue)
	ERR = errBadPushVal;
      else
	push(other->val());
    }
    break;

  case opSet:
    {
      int x = gridptr.getX();
      int y = gridptr.getY();
      int setX = pop();
      int setY = pop();
      if (gridptr.isetpos(setX, setY))
	*gridptr.cell() = pop();
      gridptr.isetpos(x, y);
    }
    break;
	
  default:
    ERR = errInternal;
    break;
  }
}

bool ExecutionPath::execute()
{
  if (state == stateStopped)
    return false;
  else if (state == stateReady)
    state = stateRunning;

  ERR.setxy(gridptr.getX(), gridptr.getY());
  Cell const *c = gridptr.cell();

  if (debugging) {
    char buffer[64];
    {
      ostrstream ostr(buffer, sizeof buffer);
      ostr << "[" << gridptr.getX() << "," << gridptr.getY() << "]" << ends;
    }
    cerr << setw(16) << buffer << setw(16);
    switch (c->type()) {
    case typeUndefined:	cerr << "(empty)";			break;
    case typeValue:	cerr << c->val();			break;
    case typeOperator:	cerr << OrthParser::getopname(c->op());	break;
    }
    stack.display(8);
    cerr << endl;
  }

  switch (c->type()) {
  case typeUndefined:	ERR = errEmpty;		break;
  case typeValue:	stack.push(c->val());	break;
  case typeOperator:	evaluate();		break;
  }
  if (ERR || !gridptr.imove())
    state = stateStopped;

  return inmotion();
}

