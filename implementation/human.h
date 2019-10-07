#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human: public Player {
  public:
  ~Human() override {};
  Human(std::string color,bool is_com,double score): Player{color,is_com,score} {}
  int getLevel() override { return 0;}
};
#endif


