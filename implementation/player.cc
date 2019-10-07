#include "player.h"

using namespace std;

Player::Player(string color,bool is_com,double score):
  color{color}, is_com{is_com},score{score}  {}

void printnumplayer() {//cout << "2";
  return;
}

void Player::winscore() {
  ++score;
}

void Player::draw() {
  score += 0.5;
}


