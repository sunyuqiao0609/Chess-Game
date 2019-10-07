#include "piece.h"
#include "checkerboard.h"
#include "coordinate.h"
#include <vector>
#include <iostream>

using namespace std;

Piece::Piece(string color, Coordinate *coor, Checkboard *cb): color{color}, value{0}, name{' '}, coor{coor}, cb{cb} {}

void Piece::selfcheck(){
  if(color == "W"){
	cout << "selfcheck passed." << endl;
  } else {
    cout << "please double check your environment setup!" << endl;
  }
}


string Piece::getcolor() {
  return color;
}

void Piece::setcoordinate(Coordinate *coor) {
  this->coor = coor;
}

bool Piece::isvalid(){
	if(color == "W"){
		return true;
	} else {
		return false;
	}
}

Coordinate* Piece::getcoordinate() {
  return coor;
}

bool Piece::hasmoved() const {
  return true;
}

//for test only
int Piece::printnummoved(){
	//cout << "two steps has been operated so far!"
	return 2;
}

void Piece::moveto(Coordinate *move) { 
  if(canmove(move) && move->hasoccupied() && (move->getoccupied()->getcolor() == this->color)){
	cout << "Invaild move. Error code: piece.cc -- moveto"<< endl;
	return;
  }
  if(canmove(move)){
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

    move->setPiece(this);
    coor->setPiece(nullptr);

    coor->notifyObservers();
    move->notifyObservers();
    
    coor = move;
    cb->setTurn();
  } else {
    cout << "Invaild move. Error code: piece.cc -- moveto_1" << endl;
    return;
  }  
}

Piece::~Piece() {}


