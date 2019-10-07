#include "coordinate.h"
#include "piece.h"

using namespace std;

Coordinate::Coordinate(char col, char row): c{col}, r{row}, piece{nullptr}, occupied{false}, color{} {
    if ((((c - 'a') % 2 == 0) && ((7 - (r - '1')) % 2 == 0)) || (((c - 'a') % 2 == 1) && ((7 - (r - '1')) % 2 == 1))) {
	color = "W";
    } else if ((((c - 'a') % 2 == 0) && ((7 - (r - '1')) % 2 == 1)) || (((c - 'a') % 2 == 1) && ((7 - (r - '1')) % 2 == 0))){
	color = "B";
    }
}

char Coordinate::getc() const {
  return c;
}

bool Coordinate::iscoor(){
	return c;
}

int Coordinate::getx() const {
  return c - 'a';
}

char Coordinate::getr() const {
  return r;
}

int Coordinate::gety() const {
  return 7 - (r - '1');
}

string Coordinate::getcolor() const {
  return color;
}

void Coordinate::moveto(Coordinate *coor) {
  piece->moveto(coor);
}

void Coordinate::setPiece(Piece *p) {
   piece = p;  
   if (p) {
    occupied = true;
  } else {
    occupied = false;
  }
}

bool Coordinate::hasoccupied() const {
  return occupied;
}

Piece* Coordinate::getoccupied() const {
  return piece;
}

Coordinate::~Coordinate() {}
