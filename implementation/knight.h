#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "piece.h"
#include <string>

class Coordinate;
class Checkboard;

class Knight: public Piece {
 public:
  bool ischanged();
  void printcolor();
  Knight(std::string color, Coordinate *coor, Checkboard *cb);
  char getname() const override;
  int getvalue() const override;
  bool canmove(Coordinate *move) override;
  ~Knight();
};

#endif

