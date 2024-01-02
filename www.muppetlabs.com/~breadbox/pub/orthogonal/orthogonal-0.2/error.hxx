#ifndef __ERROR_HXX__
#define __ERROR_HXX__

// The list of error types.
typedef enum ErrorType { errNone = 0,
			 errLowMem,
			 errSyntax, errPPSyntax, errPPRSyntax,
			 errOffGrid, errPPOffGrid, errIPOffGrid,
			 errEmpty, errRedefine,
			 errExcessVals, errBadValName, errBadValAssign,
			 errStackOver, errStackUnder, errBadPushVal,
			 errNoProgram, errInternal
	} ErrorType;

class Err
{
public:
  Err() : _err(errNone), line(0), x(0), y(0), useline(false), usexy(false) { }
  ~Err() { }
  Err &operator=(ErrorType e) { _err = e; report(); return *this; }
  bool operator!() const { return _err == errNone; }
  operator void*() const { return (void*)(_err == errNone ? NULL : this); }
  void startlinecount(int n = 1) { useline = true; line = n; }
  void nextline() { ++line; }
  void forgetlinecount() { useline = false; line = 0; }
  void setxy(int xSet, int ySet) { usexy = true; x = xSet; y = ySet; }
  void forgetxy() { usexy = false; x = y = -1; }
  void report();

private:
  ErrorType _err;
  int line;
  int x, y;
  bool useline;
  bool usexy;
};

#endif
