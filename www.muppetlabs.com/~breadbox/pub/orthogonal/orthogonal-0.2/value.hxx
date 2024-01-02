#ifndef __VALUE_HXX__
#define __VALUE_HXX__

#include <String.h>
#include "gen.hxx"

typedef enum { setAll = 0x0000,
	       setReadOnly = 0x0001,
	       setNonNeg = 0x0002, setNonZero = 0x0004, setPositive = 0x0006
	} valFlag;

class Value
{
public:
public:
  Value() : _name(NULL), _value(0), _flags(setAll) { }
  Value(char const *n, int32 v) : _name(n), _value(v), _flags(setAll) { }
  virtual ~Value() { }
  String const &name() const { return _name; }
  int32 value() const { return _value; }
  valFlag flags() const { return _flags; }
  bool validate();
  bool set(char const *n, int32 v);
  bool set(int32 v);
  void setflags(valFlag f) { _flags = (valFlag)(_flags | f); }

private:
  String _name;
  int32 _value;
  valFlag _flags;
};

class ValueLink : public Value
{
public:
  ValueLink() : next(NULL) { }
  ValueLink(char const *n, int32 v) : Value(n, v), next(NULL) { }
  ValueLink(ValueLink const &vl) : Value(vl), next(NULL) { }
  virtual ~ValueLink() { }
  ValueLink &operator=(ValueLink const &vl);
  ValueLink *cdr() { return next; }
  void attach(ValueLink *vl);
  void append(ValueLink *vl);

private:
  ValueLink *next;
};

class ValueList
{
public:
  ValueList();
  ~ValueList();
  bool lookup(char const *nm, int32 &val) const;
  bool add(char const *nm, int32 val);
  bool add(Value const &value) { return add(value.name(), value.value()); }
  int32 getorthver() const { return list->value(); }
  int32 getargrow() const { return list->cdr()->value(); }
  int32 getmaxargs() const { return list->cdr()->cdr()->value(); }
  int32 getcolsize() const { return list->cdr()->cdr()->cdr()->value(); }
  int32 gettabsize() const { return list->cdr()->cdr()->cdr()->cdr()->value();}

private:
  ValueLink *list;

private:
  ValueList(ValueList const &) { }
  ValueList &operator=(ValueList const &) { return *this; }
};

#endif
