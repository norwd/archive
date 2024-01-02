#ifndef __GRID_HXX__
#define __GRID_HXX__

#include "gen.hxx"

// What sorts of things can be stored on the grid.
typedef enum CellType { typeUndefined = 0,
			typeValue,
			typeOperator
	} CellType;

class Cell
{
public:
  Cell() : _type(typeUndefined) { }
  Cell(CellType t) : _type(t) { }
  Cell(Operator o) : _type(typeOperator), _op(o) { }
  Cell(int32 v) : _type(typeValue), _val(v) { }
  ~Cell() { }
  Cell &operator=(CellType t) { _type = t; return *this; }
  Cell &operator=(Operator o) { _type = typeOperator; _op = o; return *this; }
  Cell &operator=(int32 v) { _type = typeValue; _val = v; return *this; }
  CellType type() const { return _type; }
  Operator op() const { return _op; }
  int32 val() const { return _val; }

private:
  CellType _type;
  union {
    Operator _op;
    int32 _val;
  };
};

class Grid
{
public:
  Grid() : theGrid(NULL), cx(0), cy(0), cxMem(0), cyMem(0) { }
  ~Grid() { delete theGrid; }
  int width() const { return cx; }
  int height() const { return cy; }
  void getsize(int &x, int &y) const { x = cx; y = cy; }
  bool sizetoinclude(int x, int y);
  Cell &cell(int x, int y) { return theGrid[offset(x, y)]; }
  Cell const *getcell(int x, int y) const;

private:
  Cell *theGrid;
  int cx, cy;
  int cxMem, cyMem;
  int offset(int x, int y) const { return x + y * cxMem; }

  friend class GridPtr;
};

#endif
