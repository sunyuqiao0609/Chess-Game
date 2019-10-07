#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "checkerboard.h"
#include "coordinate.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

Pawn::Pawn(string color, Coordinate *coor, Checkboard *cb): Piece(color, coor, cb), moved{0},p{nullptr} {
  if (!(coor->getr() != '7'|| coor->getr() != '2')) {
    moved = 2;
  }

  value = 10;

  if (color == "W"){
   name = 'P';
  } else if (color == "B") {
   name = 'p';
  } 
}




int Pawn::getvalue() const {
 if (p){
  return p->getvalue();
 } else {
  return value;
 }
}

char Pawn::getname() const {
  if (p) {
   return p->getname();
 } else {
   return name;
 }
}

bool Pawn::hasmoved() const {
  return moved;
}

bool Pawn::canmove(Coordinate *move) {
  int distancec = abs(this->coor->getc() - move->getc());
  int distancer = abs(this->coor->getr() - move->getr());

  if (p) {
    return p->canmove(move);
  } else {
    if (color == "W") {
      distancer = -distancer;
    }

    if (distancer == 1 && distancec == 0 && (!move->hasoccupied())) {
      return true;
    } else if (distancer == 1 && distancec == 1 && move->hasoccupied()) {
      return true;
    } else if (moved == false  && distancer == 2 && distancec == 0 && cb->clearvertical(coor, move) && (!move->hasoccupied())) {
      return true;
    }
  }
  return false;
}

void Pawn::moveto(Coordinate *move) {
  if (p) {
    p->moveto(move);
  } else {
 
    if (canmove(move) == false) {
      cout << "Move is not valid." << endl;
      return ;
    } else {
      vector<string> s;
      string c1 = "";
      string c2 = "";
      c1.push_back(coor->getc());
      c1.push_back(coor->getr());
      c2.push_back(move->getc());
      c2.push_back(move->getr());
      s.emplace_back(c1);
      s.emplace_back(c2);
      
        if (move->hasoccupied() == true) {
          if (move->getoccupied()->getcolor() == this->color) {
            cout << "Move is not valid." << endl;
            return;
          }
        } 
        if (cb->endrow(move) &&(cb->getplayer(cb->getturn())->getIs_com())) {
         p = new Queen(color,move,cb);
         } else if (cb ->endrow(move)){
            string pro;
            while (cin >> pro) {
              if (pro == "N" || pro == "n") { 
                p = new Knight(color, move, cb);
                break;
              } else if (pro == "R" || pro == "r") {
                p = new Rook(color, move, cb);
                break;
              } else if (pro == "Q" || pro == "q") {
                p = new Queen(color, move, cb);
                break;
              } else if (pro == "B" || pro == "b") {
                p = new Bishop(color, move, cb);
                break;
              } else {
                cout <<  "Promotion is not valid" << endl; 
              } 
            }
          struct Command c{s, move->getoccupied(), true, false, false};
          cb->attachCommand(c);
        } else {
          struct Command c{s, move->getoccupied(), false, false, false};
          cb->attachCommand(c);
        }
      
      move->setPiece(this);
      coor->setPiece(nullptr);
      coor->notifyObservers();
      move->notifyObservers();
      coor = move;
      moved += 1;
      cb->setTurn();
    }
 } 
}

void Pawn::restore() {
  delete p;
  p = nullptr;
  coor->notifyObservers();
}

void Pawn::undo() { 
  moved = moved - 1;
}

Pawn::~Pawn() {
  delete p;
}
