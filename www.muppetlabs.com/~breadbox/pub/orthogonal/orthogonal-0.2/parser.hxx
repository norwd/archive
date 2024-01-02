#ifndef __PARSER_HXX__
#define __PARSER_HXX__

#include <String.h>
#include <iostream.h>
#include "gen.hxx"
#include "gridptr.hxx"
#include "value.hxx"

class OrthParser
{
public:
  static char const *getopname(Operator op);
public:
  OrthParser(Grid &grid, istream &in) : gridptr(grid), infile(in) { }
  ~OrthParser() { }
  void skipwhite();
  int chewline();
  bool parsecoord();
  bool parsecmd();
  bool parsefile();
  bool storeargs(int argc, char *argv[]);
  void showgrid(ostream& out = cerr);

private:
  GridPtr gridptr;
  ValueList vallist;
  istream &infile;
  static bool getop(char const *str, Operator &op);
  static bool getcoord(char const *str, int &x, int &y);
  bool getvalue(char const *str, int32 &val);
};

#endif
