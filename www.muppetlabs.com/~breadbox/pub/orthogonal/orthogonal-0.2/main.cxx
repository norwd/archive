#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
#include "gen.hxx"
#include "grid.hxx"
#include "gridptr.hxx"
#include "stack.hxx"
#include "value.hxx"
#include "parser.hxx"
#include "execpath.hxx"

Err ERR;
bool debugging = false;

void usage(ostream &out)
{
  out << "Usage: orth [-t] [<source file>] [args...]" << endl <<
	 "  -t turns on trace mode." << endl << 
	 "  Any arguments after the source filename are passed "
	 		"to the program." << endl <<
	 "  If the filename is omitted (or \"-\" is used), "
	 		"the source is read from stdin." << endl;
}

int main(int argc, char *argv[])
{
  int arg;
  bool showgrid = false;
  bool closein = false;

  for (arg = 1 ; arg < argc && argv[arg][0] == '-' && argv[arg][1] ; ++arg) {
    switch (tolower(argv[arg][1])) {
    case 't':	debugging = true;	break;
    case 'g':	showgrid = true;	break;
    case 'h':	usage(cout);		return 0;
    default:
      cerr << "Invalid argument: " << argv[arg][1] << endl;
      usage(cerr);
      return 1;
    }
  }

  istream *infile = NULL;

  if (arg == argc) {
    infile = &cin;
    closein = false;
  } else if (argv[arg][0] == '-' && !argv[arg][1]) {
    infile = &cin;
    closein = false;
    ++arg;
  } else {
    infile = new ifstream(argv[arg]);
    if (infile->fail()) {
      delete infile;
      infile = NULL;
      ERR = errNoProgram;
    } else {
      closein = true;
      ++arg;
    }
  }

  int retval;

  if (!ERR) {
    Grid grid;

    {
      OrthParser parser(grid, *infile);
      if (parser.parsefile()) {
	if (showgrid)
	  parser.showgrid();
	parser.storeargs(argc - arg, argv + arg);
      }
      if (closein) {
	delete infile;
	infile = NULL;
      }
      if (!ERR) {
	ExecutionPath path(grid);
	retval = path.go();
      }
    }
  }

  return retval;
}
