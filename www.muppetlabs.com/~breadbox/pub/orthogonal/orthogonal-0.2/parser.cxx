#include <stdlib.h>
#include <ctype.h>
#include <String.h>
#include <iostream.h>
#include <iomanip.h>
#include <strstream.h>
#include "gen.hxx"
#include "value.hxx"
#include "gridptr.hxx"
#include "parser.hxx"

// The list of operator symbols.
// Please note that this must jibe with the Operator enum.
static char const *opname[opMax]= { "nop",
				    "+", "-", "*", "/", "%",
				    "!", "&", "|", "^",
				    "~", "@", "$",
				    "=", "#",
				    "c", "s", "d",
				    "x", "y", "dx", "dy",
				    "cw", "ccw", "rev",
				    "h", "l", "k", "j",
				    "?", "ret"
};

char const *OrthParser::getopname(Operator op)
{
  return op == opMax ? "" : opname[op];
}

bool OrthParser::getop(char const *str, Operator &op)
{
  String opstr;

  opstr = downcase(str);
  for (int i = 0 ; i < opMax ; ++i)
    if (opstr == opname[i]) {
      op = (Operator)i;
      return true;
    }
  return false;
}

bool OrthParser::getvalue(char const *str, int32 &value)
{
  if (str[0] == '-' ? isdigit(str[1]) : isdigit(str[0])) {
    char *p;
    long v = strtol(str, &p, 0);
    value = (int32)v;
    if (*p || v != (long)value)
      return false;
  } else if (str[0] == '\'') {
    if (str[1] == '\\') {
      if (!str[2] || (str[3] && (str[3] != '\'' || str[4])))
	return false;
      switch (str[2]) {
      case '0':	value = '\0';	break;
      case 'a':	value = '\a';	break;
      case 'b':	value = '\b';	break;
      case 'f':	value = '\f';	break;
      case 'n':	value = '\n';	break;
      case 'r':	value = '\r';	break;
      case 't':	value = '\t';	break;
      case 'v':	value = '\v';	break;
      default:	value = str[2];	break;
      }
    } else {
      if (!str[1] || (str[2] && (str[2] != '\'' || str[3])))
	return false;
      value = str[1];
    }
  } else if (str[0] == '_' || isalpha(str[0])) {
    if (!vallist.lookup(str, value))
      return false;
  } else
    return false;
  return true;
}


void OrthParser::skipwhite()
{
  int ch;
  do
    ch = infile.get();
  while (ch == ' ' || ch == '\t');
  if (ch != EOF)
    infile.unget();
}

int OrthParser::chewline()
{
  int ch;
  do
    ch = infile.get();
  while (ch != '\n' && ch != EOF);
  return ch;
}

bool OrthParser::parsecoord()
{
  char buffer[256];
  char ch;
  int x, y;

  if (infile.get() != '[') {
    ERR = errInternal;
    return false;
  }

  infile.getline(buffer, sizeof buffer, ',');
  if (infile.fail()) {
    ERR = errPPSyntax;
    return false;
  }
  if (!getvalue(buffer, x) || x < 0) {
    ERR = errPPOffGrid;
    return false;
  }
  infile.getline(buffer, sizeof buffer, ']');
  if (infile.fail()) {
    ERR = errPPSyntax;
    return false;
  }
  if (!getvalue(buffer, y) || y < 0) {
    ERR = errPPOffGrid;
    return false;
  }
  skipwhite();
  ch = infile.get();
  if (ch == ';')
    ch = chewline();
  if (ch != '\n' && ch != EOF) {
    infile.unget();
    ERR = errPPSyntax;
    return false;
  }

  gridptr.setpos(x, y);
  return true;
}

bool OrthParser::parsecmd()
{
  if (infile.get() != ':') {
    ERR = errInternal;
    return false;
  }

  char inbuffer[256];
  infile.getline(inbuffer, sizeof inbuffer);
  istrstream instr(inbuffer);

  char buffer[256];
  char ch;

  instr >> buffer;
  if (instr.fail() || String(buffer) != "set") {
    ERR = errPPSyntax;
    return false;
  }
  instr >> buffer >> ch;
  if (instr.fail() || ch != '=') {
    ERR = errPPSyntax;
    return false;
  }

  Operator o;
  if (getop(buffer, o)) {
    ERR = errBadValName;
    return false;
  }
  Value value(buffer, 0);
  if (!value.validate()) {
    ERR = errBadValName;
    return false;
  }

  int i;
  do
    ch = instr.get();
  while (ch == ' ' || ch == '\t');
  instr.unget();
  instr.getline(buffer, sizeof buffer, '\0');
  for (i = String(buffer).length() - 1 ; i >= 0 ; --i)
    if (buffer[i] != ' ' && buffer[i] != '\t')
      break;
  if (i < 0) {
    ERR = errPPSyntax;
    return false;
  }
  buffer[i + 1] = '\0';
  int32 val;
  if (!getvalue(buffer, val)) {
    ERR = errPPSyntax;
    return false;
  }

  value.set(val);
  return vallist.add(value);
}

bool OrthParser::parsefile()
{
  int xLeft = 0;
  int ch;
  bool xyset = false;

  ERR.startlinecount();
  for (ch = infile.get() ; ch != EOF ; ERR.nextline(), ch = infile.get()) {
    if (ch == ';') {
      chewline();
      continue;
    } else if (ch == ':') {
      ERR.forgetxy();
      infile.unget();
      if (!parsecmd())
	break;
      continue;
    } else if (ch == '[') {
      infile.unget();
      ERR.forgetxy();
      if (!parsecoord())
	break;
      xLeft = gridptr.getX();
      xyset = true;
      continue;
    }

    int cxCol = vallist.getcolsize();
    int cxLine = 0;
    int cx = 0;
    while (ch != '\n' && ch != EOF) {
      String cmd;
      int cb;

      ERR.setxy(gridptr.getX(), gridptr.getY());
      for ( ; cx < cxCol && ch == ' ' ; ++cx)
	ch = infile.get();
      if (ch == ';') {
	ch = chewline();
	break;
      }
      cmd = "";
      for (cb = 0 ; cx < cxCol ; ++cx, ++cb) {
	if (ch == '\t') {
	  ch = ' ';
	  cx += vallist.gettabsize() - (cxLine + cx) % vallist.gettabsize();
	  --cx;
        } else if (ch == '\n' || ch == EOF)
	  break;
	cmd += ch;
	ch = infile.get();
      }
      for ( ; cb > 0 && cmd[cb - 1] == ' ' ; --cb) ;

      if (cb > 0) {
	if (!gridptr.reify())
	  break;
	xyset = true;
	cmd = String(cmd, cb);
	if (gridptr.cell()->type() != typeUndefined) {
	  ERR = errRedefine;
	  break;
	}
	if (debugging)
	  cerr << "[" << gridptr.getX() << "," << gridptr.getY() << "] " <<
			 cmd << endl;
	Operator op;
	int32 val;
	if (getop(cmd, op))
	  *gridptr.cell() = op;
	else {
	  if (!getvalue(cmd, val)) {
	    ERR = errPPRSyntax;
	    break;
	  }
	  *gridptr.cell() = val;
	}
      }

      if (ERR)
	break;
      while (cx >= cxCol) {
	cx -= cxCol;
	cxLine += cxCol;
	gridptr.move();
      }
    }

    if (ERR)
      break;
    if (xyset)
      gridptr.setpos(xLeft, gridptr.getY() + 1);
    else
      gridptr.setpos(0, 0);
  }

  ERR.forgetlinecount();
  return !ERR;
}

bool OrthParser::storeargs(int argc, char *argv[])
{
  if (vallist.getmaxargs() == 0)
    return true;
  if (!gridptr.isetpos(0, vallist.getargrow())) {
    ERR = errLowMem;
    return false;
  }
  for (int c = 0 ; c < argc ; ++c) {
    for (int n = 0 ; gridptr.getX() < vallist.getmaxargs() - 1 ; ++n) {
      *gridptr.cell() = (int32)argv[c][n];
      if (!gridptr.imove()) {
	ERR = errLowMem;
	return false;
      }
      if (!argv[c][n])
	break;
    }
  }
  while (gridptr.getX() < vallist.getmaxargs()) {
    *gridptr.cell() = 0;
    if (!gridptr.imove()) {
      ERR = errLowMem;
      return false;
    }
  }
  return true;
}

void OrthParser::showgrid(ostream& out /* = cerr */)
{
  int width = 4;

  int32 nLeast = -99, nMost = 999;
  for (int y = 0 ; y < gridptr.getgrid().height() ; ++y) {
    gridptr.isetpos(0, y);
    for (int x = 0 ; x < gridptr.getgrid().width() ; ++x) {
      if (x)
	gridptr.imove();
      Cell const *c = gridptr.cell();
      if (c->type() == typeValue) {
	while (c->val() < nLeast || c->val() > nMost) {
	  ++width;
	  nLeast = nLeast * 10 - 9;
	  nMost = nMost * 10 + 9;
	}
      }
    }
  }

  out << "Grid is " << gridptr.getgrid().width() <<
         " x " << gridptr.getgrid().height() << endl;

  cerr.flags(ios::left);
  for (int y = 0 ; y < gridptr.getgrid().height() ; ++y) {
    gridptr.isetpos(0, y);
    for (int x = 0 ; x < gridptr.getgrid().width() ; ++x) {
      if (x)
	gridptr.imove();
      Cell const *c = gridptr.cell();
      out << setw(width);
      switch (c->type()) {
      case typeUndefined:	out << "..";			break;
      case typeOperator:	out << getopname(c->op());	break;
      case typeValue:		out << c->val();		break;
      }
    }
    out << endl;
  }
}
