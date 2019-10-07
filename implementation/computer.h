#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"

class Computer: public Player {
  int level;

  public:
  ~Computer() override {}
  Computer(std::string color, bool is_com, double score,int level):
    Player(color,is_com,score), level{level} {this->is_com = true;}
  int getLevel() override { return level; }
};

#endif


