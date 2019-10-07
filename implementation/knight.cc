#include "knight.h"
#include "coordinate.h"
#include "checkerboard.h"

using namespace std;

Knight::Knight(string color, Coordinate *coor, Checkboard *cb): Piece(color, coor, cb) {
  value = 30;

  if (color == "B") {
   name = 'n';
  } else if (color == "W") {
   name = 'N';
  }
}

bool Knight::ischanged() {return false;}

void printcolor() {return;}

char Knight::getname() const {
  return name;
}

int Knight::getvalue() const {
  return value;
}

bool Knight::canmove(Coordinate *move) {
  int distancec = abs(move->getc() - this->coor->getc());
  int distancer = abs(move->getr() - this->coor->getr());

  if (distancec == 1 && distancer == 2) { //check valid move 1 right/left and 2 up/down
    return true;
  } else if (distancec == 2 && distancer == 1) { // check valid move 2 right/left and 1 up/down
    return true;
  } else {
    return false;
  }
}

Knight::~Knight(){}
