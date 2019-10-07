#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"
#include <string>

class Coordinate;
class Checkerboard;

class Pawn: public Piece {
  int moved;
  Piece *p;

 public:
  Pawn(std::string color, Coordinate *coor, Checkboard *cb);

  bool ischanged();
  void printnummove();
  char getname() const override;
  int getvalue() const override;
  
  bool canmove(Coordinate *move) override;
  bool hasmoved() const override;
  
  void moveto(Coordinate *move) override;
  void restore() override;
  void undo() override;

  ~Pawn();
};

#endif

