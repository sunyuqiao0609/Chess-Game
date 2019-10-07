#include "queen.h"
#include "checkerboard.h"

using namespace std;

Queen::Queen(string color, Coordinate *coor, Checkboard *cb): Piece(color, coor, cb) {
  value = 90;

  if (color == "W") {
   name = 'Q';
  } else if (color == "B") {
   name = 'q';
 }
}

bool Queen::ischanged_queen(){return false;}

void printcolor_queen() {
  return;
}

char Queen::getname() const {
  return name;
}

int Queen::getvalue() const {
  return value;
}

bool Queen::canmove(Coordinate *move) {
  if (cb->clearvertical(coor, move) ||
      cb->clearhorizontal(coor, move) ||
      cb->cleardiagonal(coor, move)) {
    return true;
  } else {  
    return false;
  }
}

Queen::~Queen(){}
