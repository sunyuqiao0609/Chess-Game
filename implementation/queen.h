#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "piece.h"
#include <string>

class Coordinate;
class Checkboard;

class Queen: public Piece {
 public:
  Queen(std::string color, Coordinate *coor, Checkboard *cb);
  bool ischanged_queen();
  void printcolor_queen();
  char getname() const override;
  int getvalue() const override;
  bool canmove(Coordinate *move) override;
  ~Queen();
};

#endif

