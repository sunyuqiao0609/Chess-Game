#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player {
  protected:
  std::string color;
  bool is_com;
  double score;
  public:
  void printnumplayer();
  virtual ~Player() {};
  Player(std::string color,bool is_com,double score);
  bool getIs_com() { return is_com; }
  double getScore() { return score; }
  void winscore();
  void draw();
  virtual int getLevel() = 0;
  std::string getcolor() { return color;}
};
#endif


