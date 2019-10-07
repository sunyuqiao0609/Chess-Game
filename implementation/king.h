#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class Coordinate;
class Checkboard;

class King: public Piece {
  int moved;


 public:
  King(std::string color, Coordinate *coor, Checkboard *cb);
  bool hasmoved() const override;
  bool canmove(Coordinate *move) override;

  bool ischanged();
  void printnummove();

  char getname() const override;
  int getvalue() const override;

  void moveto(Coordinate *move) override;
  void undo() override;

  ~King() {};
};

#endif

