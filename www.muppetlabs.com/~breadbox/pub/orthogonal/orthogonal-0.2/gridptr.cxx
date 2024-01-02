#include "gen.hxx"
#include "grid.hxx"
#include "gridptr.hxx"

GridPtr::GridPtr(Grid &g)
  : grid(g), x(0), y(0), dx(1), dy(0), ptr(g.theGrid), ptrinc(1)
{ }

bool GridPtr::reify()
{
  if (x < 0 || y < 0) {
    ERR = errOffGrid;
    return false;
  }
  if (x >= grid.width() || y >= grid.height()) {
    if (!grid.sizetoinclude(x, y)) {
      ERR = errLowMem;
      return false;
    }
    ptr = &grid.cell(x, y);
    ptrinc = grid.offset(dx, dy);
  }
  return true;
}

void GridPtr::setpos(int newX, int newY)
{
  x = newX;
  y = newY;
  ptr = &grid.cell(x, y);
}

bool GridPtr::setdelta(int newDX, int newDY)
{
  if (newDX == 0 && newDY == 0)
    return false;
  dx = newDX;
  dy = newDY;
  ptrinc = grid.offset(dx, dy);
  return true;
}

void GridPtr::move()
{
  x += dx;
  y += dy;
  ptr += ptrinc;
}

