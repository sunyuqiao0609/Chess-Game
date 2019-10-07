#include <cmath>

//#include <iostream>
#include "king.h"
#include "checkerboard.h"
#include "coordinate.h"

using namespace std;


King::King(string color, Coordinate *coor, Checkboard *cb): Piece(color, coor, cb), moved{0} {
  if ((coor->getc() == 'e') && (coor->getr() == '1' || coor->getr() == '8')){
    moved = 0;
  } else {
    moved = 1;
  }
  
  value = 800;
  
  if (color == "W"){
    name = 'K';
  } else if (color == "B") {
    name = 'k';
  }
}

bool King::ischanged(){return false;}

void printnummove(){return;}


bool King::hasmoved() const {
  return moved;
}

bool King::canmove(Coordinate *move) {
  int distancec = abs(move->getc() - this->coor->getc());
  int distancer = abs(move->getr() - this->coor->getr());
  

  if (distancer == 1 && distancec == 0) { // move forward/back
    return true;
  } else if (distancer == 0 && distancec == 1) { // move left/right
    return true;
  } else if (distancer == 1 && distancec == 1) { // move diagonal
    return true;
  }
    else {
    return false;
  }
}

char King::getname() const {
  return name;
}

int King::getvalue() const {
  return value;
}


void King::moveto(Coordinate *move) {
    if (canmove(move) == true) { 

      if (move->hasoccupied() == true) { 
        if (move->getoccupied()->getcolor() == this->color) {
          cout << "Move is not valid. Error code: King.cc -- moveto" << endl;
          return ;
        }
      }
      moved = moved + 1;

      vector<string> s;
      string c1 = "";
      string c2 = "";

      c1.push_back(coor->getc());
      c1.push_back(coor->getr());
      c2.push_back(move->getc());
      c2.push_back(move->getr());

      s.emplace_back(c1);
      s.emplace_back(c2);

      struct Command c{s, move->getoccupied(), false, false, false};
      cb->attachCommand(c);
      cb->setking(color, move);
      move->setPiece(this);
      coor->setPiece(nullptr);
      coor->notifyObservers();
      move->notifyObservers();
      coor = move;
      cb->setTurn();

    } else { 
    cout << "Move is not valid. Error code: king.cc -- moveto_1" << endl;
    return ;
    }

}

void King::undo() { 
 moved = moved - 1;
}

