#include <String.h>
#include <ctype.h>
#include "gen.hxx"
#include "value.hxx"

// The list of predefined values.
// Please note that this must jibe with the ValueList member functions.
const struct { char *name; int32 val; valFlag flags; }
	     valPredefined[] = { { "orthver", 0x0002, setReadOnly },
				 { "argrow", 256, setPositive },
				 { "maxargs", 255, setNonNeg },
				 { "colsize", 4, setPositive },
				 { "tabsize", 8, setPositive }
       };

bool Value::validate()
{
  if (!_name)
    return false;
  if (_name[0] != '_' && !isalpha(_name[0]))
    return false;
  for (unsigned int i = 1 ; i < _name.length() ; ++i) {
    if (_name[i] != '_' && !isalnum(_name[i]))
      return false;
  }
  return true;
}

bool Value::set(int32 v)
{
  if (_flags & setReadOnly) {
    ERR = errBadValAssign;
    return false;
  } else if ((_flags & setNonNeg) && v < 0) {
    ERR = errBadValAssign;
    return false;
  } else if ((_flags & setNonZero) && v == 0) {
    ERR = errBadValAssign;
    return false;
  }
  _value = v;
  return true;
}

bool Value::set(char const *n, int32 v)
{
  if (!set(v))
    return false;
  _name = n;
  return true;
}


ValueLink &ValueLink::operator=(ValueLink const &vl)
{
  Value::operator=(vl);
  return *this;
}

void ValueLink::attach(ValueLink *vl)
{
  ValueLink *n;
  n = next;
  next = vl;
  vl->next = n;
}

void ValueLink::append(ValueLink *vl)
{
  if (next)
    next->append(vl);
  else
    attach(vl);
}


ValueList::ValueList()
  : list(NULL)
{
  list = new ValueLink(valPredefined[0].name, valPredefined[0].val);
  if (!list) {
    ERR = errLowMem;
    return;
  }
  list->setflags(valPredefined[0].flags);

  ValueLink *vlLast = list;
  unsigned int i;
  for (i = 1 ; i < sizeof valPredefined / sizeof *valPredefined ; ++i) {
    ValueLink *vl = new ValueLink;
    if (!vl) {
      ERR = errLowMem;
      return;
    }
    vl->set(valPredefined[i].name, valPredefined[i].val);
    list->setflags(valPredefined[i].flags);
    vlLast->attach(vl);
    vlLast = vl;
  }
}

ValueList::~ValueList()
{
  ValueLink *vl;
  ValueLink *vlNext;

  for (vl = list ; vl ; vl = vlNext) {
    vlNext = vl->cdr();
    delete vl;
  }
}

#if 0
ValueList::ValueList(ValueList const &vl)
  : list(NULL), count(0), countMem(0)
{
  if (vl.count > 0) {
    list = new Value[vl.countMem];
    if (list) {
      for (int i = 0 ; i < vl.count ; ++i)
	list[i] = vl.list[i];
    }
    count = vl.count;
  }
}

ValueList &ValueList::operator=(ValueList const &vl)
{
  Value *newList;

  if (vl.count) {
    newList = new Value[vl.countMem];
    if (!newList)
      return;
    for (int i = 0 ; i < vl.count ; ++i)
      newList[i] = vl.list[i];
    count = vl.count;
  } else
    newList = NULL;

  delete[] list;
  list = newList;
  count = vl.count;
}
#endif

bool ValueList::lookup(char const *nm, int32 &val) const
{
  ValueLink *vl;
  String name;

  name = downcase(nm);
  for (vl = list ; vl ; vl = vl->cdr())
    if (name == vl->name()) {
      val = vl->value();
      return true;
    }

  return false;
}

bool ValueList::add(char const *nm, int32 val)
{
  ValueLink *vl;
  ValueLink *vlNext;
  String name;

  name = downcase(nm);
  for (vl = list ; vl ; vl = vlNext) {
    if (name == vl->name())
      return vl->set(val);
    vlNext = vl->cdr();
    if (!vlNext)
      break;
  }
  vlNext = new ValueLink(name, val);
  if (!vlNext) {
    ERR = errLowMem;
    return false;
  }
  vl->attach(vlNext);
  return true;
}
