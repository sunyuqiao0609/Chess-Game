#include "bishop.h"
#include "checkerboard.h"

using namespace std;

Bishop::Bishop(string color, Coordinate *coor, Checkboard *cb): Piece(color, coor, cb) {
  value = 30;

  if (color == "W") {
    name = 'B';
  } else if (color == "B"){
    name = 'b';
 }

}

bool Bishop::ischanged_bishop() {return false;}

void Bishop::printcolor_bishop() {cout<<"unknown";}

char Bishop::getname() const {
  return name;
}

int Bishop::getvalue() const {
  return value;
}

bool Bishop::canmove(Coordinate *move) {
  return cb->cleardiagonal(coor, move);
}

