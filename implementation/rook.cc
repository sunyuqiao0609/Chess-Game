#include "rook.h"
#include "coordinate.h"
#include "checkerboard.h"
#include <vector>
#include <iostream>
using namespace std;

Rook::Rook(string color, Coordinate *coor, Checkboard *cb): Piece(color, coor, cb), moved{0} {
  value = 50;
  
  if (color == "W") {
   name = 'R';
  } else if (color == "B") {
   name = 'r';
 }

}

bool Rook::ischanged() {return false;}

char Rook::getname() const {
  return name;
}

int Rook::getvalue() const {
  return value;
}

void printcolor_rook(){
	int i = 0;

	char c = 'j';
	while(i < 8){
		c = c - 1;
		++i;
	}
	cout << c <<endl;
}
bool Rook::hasmoved() const {
  return moved;
}

bool Rook::canmove(Coordinate *move) {
  if (cb->clearhorizontal(coor, move) || cb->clearvertical(coor, move)) {
    return true;
  } else {
    return false;
  }
}

void Rook::undo() { 
 moved = moved - 1;
}



