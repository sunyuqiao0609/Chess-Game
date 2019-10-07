#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H
#include <vector>
#include <string>
#include <iostream>
#include "player.h"

class Player;
class Piece;
class Coordinate;
class TextDisplay;
class GraphicsDisplay;

struct Command {
  std::vector<std::string> c;
  Piece *p;
  bool promotion;
  bool enpassant;
  bool castling;
};

class Checkboard {
  std::vector< std::vector<Coordinate *> > checkboard;
  std::vector<Command> commands;
  std::vector<Piece *> pieces;
  TextDisplay *td;
  GraphicsDisplay *gd;
  Coordinate *Wking;
  Coordinate *Bking;
  Player *p1;
  Player *p2;
  std::string turn;
  
  public:
  Checkboard(bool is_com1,bool is_com2,int lvl1,int lvl2);
  ~Checkboard();

  void init();
  void attachCommand(Command &c);
  Command *getCommand();
  void clear();
  void undo();
  void move(std::string coor1 = "", std::string coor2 = "");
  bool check(std::string king);
  bool checkmate(std::string king);
  void concede();
  void setup(std::string piece, std::string coor);
  void unset(std::string coor);
  void setturn(std::string t);
  bool verify();
  bool underattack(Piece *p);
  int value(std::string color);
  Player *getplayer(std::string p);
  std::string getturn();
  void setTurn();
  void setking(std::string color, Coordinate *coor);
  bool stalemate(std::string color);
  void standardopening(std::string color);
  void printmoves();

  void move1(std::string color);
  void move2(std::string color);
  void move3(std::string color);

  Coordinate* coordinateat(int x, int y) const;
  bool clearhorizontal(Coordinate *from, Coordinate *to) const;
  bool clearvertical(Coordinate *from, Coordinate *to) const;
  bool cleardiagonal(Coordinate *from, Coordinate *to) const;
  bool endrow(Coordinate *sq) const;

  friend std::ostream &operator<<(std::ostream &out, Checkboard &cb);
};


#endif



