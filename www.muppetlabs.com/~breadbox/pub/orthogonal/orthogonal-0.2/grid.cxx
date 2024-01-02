#include <stdlib.h>
#include <string.h>
#include "gen.hxx"
#include "grid.hxx"

bool Grid::sizetoinclude(int xInc, int yInc)
{
  if (xInc < cx && yInc < cy)
    return true;
  else if (xInc < cxMem && yInc < cyMem) {
    if (cx <= xInc)
      cx = xInc + 1;
    if (cy <= yInc)
      cy = yInc + 1;
    return true;
  }

  int cxNew = xInc < cxMem ? cxMem : (xInc | 15) + 1;
  int cyNew = yInc < cyMem ? cyMem : (yInc | 15) + 1;
  Cell *newGrid = new Cell[cxNew * cyNew];
  if (!newGrid) {
    ERR = errLowMem;
    return false;
  }
  if (cxMem) {
    if (cxMem == cxNew)
      memcpy(newGrid, theGrid, cxMem * cy * sizeof(Cell));
    else {
      int cbOld = 0, cbNew = 0;
      int cbCopy = cx * sizeof(Cell);
      for (int y = 0 ; y < cy ; ++y) {
	memcpy(newGrid + cbNew, theGrid + cbOld, cbCopy);
	cbOld += cxMem;
	cbNew += cxNew;
      }
    }
  }

  delete theGrid;
  theGrid = newGrid;
  cxMem = cxNew;
  cyMem = cyNew;
  if (cx <= xInc)
    cx = xInc + 1;
  if (cy <= yInc)
    cy = yInc + 1;
  return true;
}

Cell const *Grid::getcell(int x, int y) const
{
  static Cell cellDead = typeUndefined;
  return x < cx && y < cy ? &theGrid[offset(x, y)] : &cellDead;
}
