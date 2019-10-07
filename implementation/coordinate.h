#ifndef _COORDINATE_H_
#define _COORDINATE_H_
#include <string>
#include "subject.h"

class Piece;

class Coordinate: public Subject {
  char c;
  char r;
  Piece *piece;
  bool occupied;
  std::string color;

 public:
  Coordinate(char c, char r); //set inital color by position
   
  char getc() const override;
  char getr() const override;
  int getx() const;
  int gety() const;
  std::string getcolor() const override;
  
  void moveto(Coordinate *coor);
  bool iscoor();
  void setPiece(Piece *p);
  bool hasoccupied() const override;
  Piece* getoccupied() const override;
  ~Coordinate();
};

#endif

