#ifndef _ROOK_H_
#define _ROOK_H_
#include "piece.h"
#include <string>

class Coordinate;
class Checkboard;

class Rook: public Piece {
  int moved;

 public:
  Rook(std::string color, Coordinate *coor, Checkboard *cb);
  bool ischanged();
  char getname() const override;  
  int getvalue() const override;
  void printcolor_rook();
  bool canmove(Coordinate *move) override;
  bool hasmoved() const override;
  
  void undo() override;
  ~Rook() {};
};

#endif

