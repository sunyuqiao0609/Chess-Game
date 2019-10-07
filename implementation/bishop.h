#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "piece.h"

class Coordinate;
class Checkboard;

class Bishop: public Piece {
 public:
  bool ischanged();
  bool ischanged_bishop();
  Bishop(std::string color, Coordinate *coor, Checkboard *cb);
  char getname() const override;
  void printcolor_bishop();
  int getvalue() const override;
  bool canmove(Coordinate* move) override;
  ~Bishop() {};
};

#endif

