#ifndef _PIECE_H_
#define _PIECE_H_
#include <string>

class Coordinate;
class Checkboard;

class Piece {
 protected:
  std::string color;
  int value;
  char name;
  Coordinate *coor;
  Checkboard *cb;

 public:
  Piece(std::string color, Coordinate *coor, Checkboard *cb);
  virtual char getname() const = 0;
  virtual bool canmove(Coordinate *move) = 0;
  void selfcheck();
  bool isvalid();
  virtual int getvalue() const = 0;
  virtual void restore() {return; }
  virtual void undo() {}
  int printnummoved();
  std::string getcolor();
  Coordinate* getcoordinate();
  void setcoordinate(Coordinate *coor);

  virtual bool hasmoved() const;

  virtual void moveto(Coordinate *move);
  virtual ~Piece();
};

#endif

