#ifndef __GRIDPTR_HXX__
#define __GRIDPTR_HXX__

#include "gen.hxx"
#include "grid.hxx"

class GridPtr
{
public:
  GridPtr(Grid &g);
  virtual ~GridPtr() { }
  int getX() const { return x; }
  int getY() const { return y; }
  int getDX() const { return dx; }
  int getDY() const { return dy; }
  Grid const &getgrid() const { return grid; }
  Cell *cell() { return ptr; }
  bool reify();
  void setpos(int newX, int newY);
  bool setdelta(int newDX, int newDY);
  void move();
  bool isetpos(int newX, int newY) { setpos(newX, newY); return reify(); }
  bool imove() { move(); return reify(); }

private:
  Grid &grid;
  int x, y;
  int dx, dy;
  Cell *ptr;
  int ptrinc;
};

#endif
