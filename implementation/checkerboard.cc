#include "player.h"
#include "checkerboard.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "computer.h"
#include "human.h"
#include "coordinate.h"
using namespace std;

Checkboard::Checkboard(bool is_com1,bool is_com2,int lvl1,int lvl2): 
  checkboard{},commands{},pieces{},td{},Wking{nullptr},Bking{nullptr},p1{nullptr},p2{nullptr},turn{"p1"} {
  td = new TextDisplay();
  gd = new GraphicsDisplay();
  int i = 0;
  while(i < 8){
    int j = 0;
    std::vector<Coordinate *> v;
    while(j < 8){
      char c = 'a' + j;
      char r = 7 - i + '1';
      Coordinate *coor = new Coordinate(c,r);
      coor->attach(td);
      coor->attach(gd);
      v.emplace_back(coor);
      ++j;
    }
    checkboard.emplace_back(v);
    ++i;
  }
  if (!is_com1) {
    p1 = new Human("W",false,0);
  }
  else {
    p1 = new Computer("W",true,0,lvl1); 
  }
  if (!is_com2){
    p2 = new Human("B",false,0);
  } else {
    p2 = new Computer("B",true,0,lvl2);
  }
}

Checkboard::~Checkboard() {
  delete td;
  delete gd;
  delete p1;
  delete p2;
  for (auto &p : pieces) {
    delete p;
  }
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      Coordinate *coor = checkboard.at(i).at(j);
      delete coor;
      ++j;
    }
    ++i;
  }
}

void Checkboard::init() {
  td->init();
  gd->init();
  turn = "p1";
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      Coordinate *coor = checkboard[i][j];
      if(i == 0){
        if(j == 0){
          Rook *r = new Rook("B",coor,this);
          pieces.emplace_back(r);
          coor->setPiece(r);
        } 
        if(j == 1){
          Knight *n = new Knight("B",coor,this);
          pieces.emplace_back(n);
          coor->setPiece(n);
        }
        if(j == 2){
          Bishop *b = new Bishop("B",coor,this);
          pieces.emplace_back(b);
          coor->setPiece(b);
        } 
        if(j == 3){
          Queen *q = new Queen("B",coor,this);
          pieces.emplace_back(q);
          coor->setPiece(q);
        }
        if(j == 4){
          King *k = new King("B",coor,this);
          pieces.emplace_back(k);
          Bking = coor;
          coor->setPiece(k);
        } 
        if(j == 5){
          Bishop *b = new Bishop("B",coor,this);
          pieces.emplace_back(b);
          coor->setPiece(b);
        }
        if(j == 6){
          Knight *n = new Knight("B",coor,this);
          pieces.emplace_back(n);
          coor->setPiece(n);
        } 
        if(j == 7){
          Rook *r = new Rook("B",coor,this);
          pieces.emplace_back(r);
          coor->setPiece(r);
        }
      } else if(i == 1){
        Pawn *p = new Pawn("B",coor,this);
        pieces.emplace_back(p);
        coor->setPiece(p);
      } else if(i == 6){
        Pawn *p = new Pawn("W",coor,this);
        pieces.emplace_back(p);
        coor->setPiece(p);
      } else if(i == 7){
        if (j == 0){
          Rook *r = new Rook("W",coor,this);
          pieces.emplace_back(r);
          coor->setPiece(r);
        }
        if (j == 1){
          Knight *n = new Knight("W",coor,this);
          pieces.emplace_back(n);
          coor->setPiece(n);
        }
        if (j == 2){
          Bishop *b = new Bishop("W",coor,this);
          pieces.emplace_back(b);
          coor->setPiece(b);
        }
        if (j == 3){
          Queen *q = new Queen("W",coor,this);
          pieces.emplace_back(q);
          coor->setPiece(q);
        }
        if (j == 4){
          King *k = new King("W",coor,this);
          pieces.emplace_back(k);
          Wking = coor;
          coor->setPiece(k);
        }
        if (j == 5){
          Bishop *b = new Bishop("W",coor,this);
          pieces.emplace_back(b);
          coor->setPiece(b);
        }
        if (j == 6){
          Knight *n = new Knight("W",coor,this);
          pieces.emplace_back(n);
          coor->setPiece(n);
        }
        if (j == 7){
          Rook *r = new Rook("W",coor,this);
          pieces.emplace_back(r);
          coor->setPiece(r);
        }
      } else {
        coor->setPiece(nullptr);
      }
      ++j;
    }
    ++i;
  }
}

void Checkboard::clear() {
  for (auto &p : pieces) {
    delete p;
    p = nullptr;
  }
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      Coordinate *coor = checkboard[i][j];
      coor->setPiece(nullptr);
      coor->notifyObservers();
      ++j;
    }
    ++i;
  } 
}

void Checkboard::setTurn() {
  if (turn == "p2") turn = "p1";
  else turn = "p2";
}

void Checkboard::attachCommand(Command &c) {
  commands.emplace_back(c);
}

Command *Checkboard::getCommand() {
  return &commands.back();
}

void Checkboard::undo() {
  if (commands.size() == 0) {
    cout << "You haven't moved!" << endl;
    return;
  }

  Command *cd = this->getCommand();

  this->setTurn();

  int i1 = 7 - (cd->c[1][1] - '1');
  int j1 = cd->c[1][0] - 'a';
  int i2 = 7 - (cd->c[0][1] - '1');
  int j2 = cd->c[0][0] - 'a';
  Coordinate *coor1 = checkboard[i1][j1];
  Coordinate *coor2 = checkboard[i2][j2];
  Piece *piece = coor1->getoccupied();
  if (coor1 == Wking) Wking = coor2;
  else if(coor1 == Bking) Bking = coor2;
  piece->undo();


  if (cd->promotion) {
    coor1->getoccupied()->restore();
    coor2->setPiece(piece);
    coor1->setPiece(nullptr);
    piece->setcoordinate(coor2);
  }
  else {
    coor2->setPiece(piece);
    coor1->setPiece(nullptr);
    piece->setcoordinate(coor2);
  }
  if (cd->p) cd->p->getcoordinate()->setPiece(cd->p);
  commands.pop_back();
  
  coor1->notifyObservers();
  coor2->notifyObservers();
}

 
void Checkboard::move(string coor1, string coor2) {
  Player *pl = nullptr;
  if (turn == "p1") pl = p1;
  else pl = p2;
  if (pl->getIs_com()) {
    string c = pl->getcolor();
    if (pl->getLevel() == 1) {
      this->move1(c);
    } 
    else if (pl->getLevel() == 2) {
      this->move2(c);
    }
    else if (pl->getLevel() == 3) {
      this->move3(c);
    }
  }
  else {
    while(cin >> coor1) {
      if ((coor1.length() == 2) && (coor1[0] <= 'h') && (coor1[0] >= 'a') && (coor1[1] >= '1') && (coor1[1] <= '8')) break;
    }
    while(cin >> coor2) {
      if ((coor2.length() == 2) && (coor2[0] <= 'h') && (coor2[0] >= 'a') && (coor2[1] >= '1') && (coor2[1] <= '8')) break;
    }
    int i1 = 7 - (coor1[1] - '1');
    int j1 = coor1[0] - 'a';
    int i2 = 7 - (coor2[1] - '1');
    int j2 = coor2[0] - 'a';
    Coordinate *s1 = checkboard.at(i1).at(j1);
    Coordinate *s2 = checkboard.at(i2).at(j2);
    if (!s1->hasoccupied()) { 
      cout << "Invalid Move! There is no piece here" << endl;
      return;
    }
    
    if (s1->getoccupied()->getcolor() != pl->getcolor()) {
      cout <<  "Invalid Move! It's not your turn! " << endl;
      return;
    }

    if (s1 == Wking) Wking->moveto(s2);
    else if (s1 == Bking) Bking->moveto(s2);
    else s1->moveto(s2);

    if (s1 == Wking) Wking = s2;
    if (s1 == Bking) Bking = s2;
    if (turn == "p2") {
      if (check("W")) {
        cout << "Invalid Move! White is in check!" << endl;
        this->undo();
      }
      else if (check("B")) cout << "Black is in check!" << endl;
    } 
    else if (turn == "p1") {
      if (check("B")) {
        cout << "Invalid Move! Black is in check!" << endl;
        this->undo();
      }
      else if (check("W")) cout << "White is in check!" << endl;
    }

  }
}

bool Checkboard::check(string king) {
  if (king == "B") {
    int i = 0;
    while(i < 8){
      int j = 0;
      while(j < 8){
        Coordinate *coor = checkboard[i][j];
        if (coor->hasoccupied()) {
          Piece *p = coor->getoccupied();
          if (p->getcolor() != king) {
            if (p->canmove(Bking)) return true;
  	      }
        }
        ++j;
      }
      ++i;
    }

  }
  else {
    int x = 0;
    while(x < 8){
      int y = 0;
      while(y < 8){
                Coordinate *coor = checkboard.at(x).at(y);
        if (coor->hasoccupied()) {
          Piece *p = coor->getoccupied();
          if (p->getcolor() != king) {
            if (p->canmove(Wking)) return true;
  	  }
        }
        ++y;
      }
      ++x;
    }
  }
  return false;
}

bool Checkboard::checkmate(string king) {
  Coordinate *to = nullptr;

  for (int i = 0; i <= 7; ++i) {
    for (int j =0; j <= 7; ++j) {
      Coordinate *coor = checkboard[i][j];
      if (king == "W") {
      if (coor->hasoccupied() && coor->getoccupied()->getcolor() == king) continue;
    	if (Wking->getoccupied()->canmove(coor)) {
          to = coor;
          Wking->moveto(coor);
          if (!check("W")) {
            this->undo();
            return false;
          }
          this->undo();
        } 
      }
      else if (king == "B") {
        if (coor->hasoccupied() && coor->getoccupied()->getcolor() == king) continue;
        if (Bking->getoccupied()->canmove(coor)) {
          to = coor;
          Bking->moveto(coor);
          if (!check("B")) {
            this->undo();
            return false;
          }
          this->undo();
        }
      }
    }
  }

  for (int a = 0; a <= 7; ++a) {
    for (int b = 0; b <= 7; ++b) {
      Coordinate *s = checkboard[a][b];
      if (s->hasoccupied() && s->getoccupied()->getcolor() == king) {
        for (int x =0; x <= 7; ++x) {
          for (int y = 0; y <= 7; ++y) {
            Coordinate *s2 = checkboard[x][y];
            if (s2->hasoccupied() && s2->getoccupied()->getcolor() == king) continue;
            if (s->getoccupied()->canmove(s2)) {
              s->moveto(s2);
              if (!check(king)) {
                this->undo();
                return false;
              }
              this->undo();
            }
          }
        }
      }
    }
  }
  if (!to) return check(king);
  else return true;
}

void Checkboard::concede() {
  if (turn == "p1") cout << "Black wins!";
  else cout << "White wins!";
}

void Checkboard::setup(string piece, string coor) {
  char c = coor[0];
  char r = coor[1];
  int j = c - 'a';
  int i = 7 - (r - '1');
  Coordinate *toset = checkboard[i][j];
  if (piece == "r") {
    Rook *r = new Rook("B",toset,this);
    toset->setPiece(r);
    pieces.emplace_back(r);
  }
  else if (piece == "n") {
    Knight *n = new Knight("B",toset,this);
    pieces.emplace_back(n);
    toset->setPiece(n);
  }
  else if (piece == "b") {
    Bishop *b = new Bishop("B",toset,this);
    pieces.emplace_back(b);
    toset->setPiece(b);
  }
  else if (piece == "q") {
    Queen *q = new Queen("B",toset,this);
    pieces.emplace_back(q);
    toset->setPiece(q);
  }
  else if (piece == "k") {
    King *k = new King("B",toset,this);
    pieces.emplace_back(k);
    Bking = toset;
    toset->setPiece(k);
  }
  else if (piece == "p") {
    Pawn *p = new Pawn("B",toset,this);
    pieces.emplace_back(p);
    toset->setPiece(p);
  }
  else if (piece == "P") {
    Pawn *p = new Pawn("W",toset,this);
    pieces.emplace_back(p);
    toset->setPiece(p);
  }
  else if (piece == "R") {
    Rook *r = new Rook("W",toset,this);
    pieces.emplace_back(r);
    toset->setPiece(r);
  }
  else if (piece == "N") {
    Knight *n = new Knight("W",toset,this);
    pieces.emplace_back(n);
    toset->setPiece(n);
  }
  else if (piece == "B") {
    Bishop *b = new Bishop("W",toset,this);
    pieces.emplace_back(b);
    toset->setPiece(b);
  }
  else if (piece == "Q") {
    Queen *q = new Queen("W",toset,this);
    pieces.emplace_back(q);
    toset->setPiece(q);
  }
  else if (piece == "K") {
    King *k = new King("W",toset,this);
    pieces.emplace_back(k);
    toset->setPiece(k);
    Wking = toset;
  }
  toset->notifyObservers();
}


void Checkboard::unset(string coor) {
  char c = coor[0];
  char r = coor[1];
  int j = c - 'a';
  int i = 7 - (r - '1');

  Coordinate *tounset = checkboard[i][j];
  tounset->setPiece(nullptr);
  tounset->notifyObservers();
}

void Checkboard::setturn(string t) {
  turn = t;
}

ostream &operator<<(ostream &out, Checkboard &cb) {
  out << *cb.td;
  return out;
}

bool Checkboard::verify() {
  int bk = 0,wk = 0;
  bool pawn = true;
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      Coordinate *coor = checkboard[i][j];
      if (coor->hasoccupied()) {
        if (coor->getoccupied()->getname() == 'K') ++wk;
        if (coor->getoccupied()->getname() == 'k') ++bk;
        if (coor->getoccupied()->getname() == 'p') {
          if (coor->getr() == '1') pawn = false;
        }
        if (coor->getoccupied()->getname() == 'P') {
          if (coor->getr() == '8') pawn = false;
        }
      }
      ++j;
    }
    ++i;
  }


  return (bk == 1) && (wk == 1) && pawn;
}

bool Checkboard::underattack(Piece *p) {
  Coordinate *pos = p->getcoordinate();
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      Coordinate *coor = checkboard[i][j];
      if (coor->hasoccupied() && coor->getoccupied()->getcolor() != p->getcolor()) {
        if (coor->getoccupied()->canmove(pos)) return true;
      } 
      ++j;
    }
    ++i;
  }

  return false;
}


int Checkboard::value(string color) {
  int v = 0;
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      Coordinate *coor = checkboard[i][j];
      if (coor->hasoccupied() && coor->getoccupied()->getcolor() == color) v += coor->getoccupied()->getvalue();
      else if (coor->hasoccupied() && coor->getoccupied()->getcolor() != color) v = v - coor->getoccupied()->getvalue();
      ++j;
    }
    ++i;
  }

  return v;
}

Player *Checkboard::getplayer(string p) {
  if (p == "p1") return p1;
  else return p2;
}

string Checkboard::getturn() {
  return turn;
}

void Checkboard::setking(string color, Coordinate *coor) {
  if (color == "B") Bking = coor;
  else if (color == "W") Wking = coor;
}

void Checkboard::move1(string color) {
  Coordinate *from = nullptr;
  Coordinate *to = nullptr;
  vector<vector<Coordinate *>> v;
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
            Coordinate *coor = checkboard[i][j];
      if (coor->hasoccupied()) {
    	if (coor->getoccupied()->getcolor() == color) {
    	  from = coor;

    	  for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
              Coordinate *coor2 = checkboard[x][y];
              if (coor2->hasoccupied() && coor2->getoccupied()->getcolor() == color) continue;
              if (from->getoccupied()->canmove(coor2)) {
                to = coor2;
                from->moveto(coor2);
                if (check(color)) { 
                  this->undo();
                  continue;
                }
                vector<Coordinate *> sv;
                sv.emplace_back(from);
                sv.emplace_back(to);
                v.emplace_back(sv);
                this->undo();
              }
  	    }
          }
        }
      }
      ++j;
    }
    ++i;
  }
  int count = rand()%(v.size());
  v[count][0]->moveto(v[count][1]);
}

void Checkboard::move2(string color) {
  Coordinate *from = nullptr;
  Coordinate *to = nullptr;
  for(int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Coordinate *coor = checkboard[i][j];
      if (coor->hasoccupied() && (coor->getoccupied()->getcolor() == color)) {
        from = coor;
        for (int x = 0; x < 8; ++x) {
          for (int y = 0; y < 8; ++y) {
            Coordinate *coor2 = checkboard[x][y];
            if (coor2->hasoccupied() && coor2->getoccupied()->getcolor() == color) continue;
            if (from->getoccupied()->canmove(coor2)) {
              to = coor2;
              from->moveto(coor2);
              if (color == "W") {
                if (check("B")) {
                  return;
                }
              }
              else if (color == "B") {
                if (check("W")) {
                  return;
                }
              }
              this->undo();
            }
            if (coor2->hasoccupied()) {
              if (coor2->getoccupied()->getcolor() != color && from->getoccupied()->canmove(coor2)) {
                to = coor2;
                from->moveto(coor2);
                return;
              }
            }
          }
        }
      }
    }
  }
  this->move1(color);
}

void Checkboard::move3(string color) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      Coordinate *coor = checkboard[i][j];
      if (coor->hasoccupied() && coor->getoccupied()->getcolor() == color && underattack(coor->getoccupied())) {
        for (int x = 0; x < 8; ++x) {
          for (int y = 0; y < 8; ++y) {
            Coordinate *coor2 = checkboard[x][y];
            if (coor2->hasoccupied() && coor2->getoccupied()->getcolor() == color) continue;
  	    if (coor->getoccupied()->canmove(coor2)) {
  	      coor->moveto(coor2);
              if (this->check(color) || this->underattack(coor2->getoccupied())) {
                this->undo();
                break;
              }
              if (color == "W") {
                if(check("B")) {
                }
              }
              else if (color == "B") {
                if(check("W")) {
                }
              }
  	      return;
  	    }
          }
        }
      }
    }
  }
  move2(color);
}



Coordinate* Checkboard::coordinateat(int r, int c) const {
  Coordinate* s = checkboard[r][c];
  return s;
}

bool Checkboard::clearvertical(Coordinate *from, Coordinate *to) const {
  int start = 0;
  int end = 0;
  if (from->gety() <= to->gety()) {
    start = from->gety();
    end = to->gety();
  }
  if (from->gety() > to->gety()) {
    start = to->gety();
    end = from->gety();
  }
  if (from->getx() != to->getx()) return false;
  int i = start + 1;
  while (i < end) {
    if (coordinateat(i, from->getx())->hasoccupied()) return false;
    ++i;
  } 
  return true;
}

bool Checkboard::clearhorizontal(Coordinate *from, Coordinate *to) const {
  int start = 0;
  int end = 0;
  if (from->getx() <= to->getx()) {
    start = from->getx();
    end = to->getx();
  }
  if (from->getx() > to->getx()) {
    start = to->getx();
    end = from->getx();
  }
  if (from->gety() != to->gety()) return false;
  int i = start + 1;
  while (i < end) {
    if (coordinateat(from->gety(), i)->hasoccupied()) return false;
    ++i;
  }
  return true;
}

bool Checkboard::cleardiagonal(Coordinate *from, Coordinate *to) const {
  const int directiony = to->gety() - from->gety();
  const int directionx = to->getx() - from->getx();
  int d1 = 1;
  int d2 = 1;
  if (directiony < 0) d1 = -1;
  if (directionx < 0) d2 = -1;
  if (abs(directiony) != abs(directionx)) return false;
  int i = 1;
  while(i < abs(directionx)){
        if (coordinateat(from->gety() + (i * d1), from->getx() + (i * d2))->hasoccupied()) {
      return false;
    }
    ++i;
  }

  return true;
}

bool Checkboard::endrow(Coordinate *coor) const {
  return (coor->gety() == 0 || coor->gety() == 7);
}

bool Checkboard::stalemate(string color) {
  Coordinate *form = nullptr;
  Coordinate *to = nullptr;
  if (check(color)) return false;
  if (color == "W") {
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      Coordinate *coor = checkboard[i][j];
        if (coor->hasoccupied() && coor->getoccupied()->getcolor() == color) {
          int x = 0;
          while(x < 8){
            int y = 0;
            while(y < 8){
              Coordinate *coor2 = checkboard[x][y];
              if (coor2->hasoccupied() && coor2->getoccupied()->getcolor() == color) continue;
              if (coor->getoccupied()->canmove(coor2)) {
                coor->moveto(coor2);
                if (!check(color)) {
                  this->undo();
                  return false;
                }
                undo();
              }
              ++y;
            }
            ++x;
          }
        }
      ++j;
    }
    ++i;
  }
  }
  return true;
}

void Checkboard::printmoves() {
  const int size = commands.size();
  if (size == 0) {
    cout << "No move has been made!" << endl;
    return;
  }
  else {
    int i = 0;
    while(i < size){
      cout << "move " << commands[i].c[0] << " " << commands[i].c[1] << endl;
      ++i;
    }
  }
}


