#include <iostream>
#include <string>
#include <stdexcept>
#include "checkerboard.h"
#include "player.h"

using namespace std;

int main(int argc, char *argv[]) {
  string cmd;
  string p1 = "";
  string p2 = "";
  int lvl1 = 0,lvl2 = 0;
  bool is_com1,is_com2;

  while (p1 == "" || p2 == "") {
    if(p1==""){
	   cin >> p1;
    if (p1 == "human") {
      is_com1 = false;
    } else if (p1 == "computer[1]") {
      is_com1 = true;
      lvl1 = 1;
    } else if (p1 == "computer[2]") {
      is_com1 = true;
      lvl1 = 2;
    } else if (p1 == "computer[3]") {
      is_com1 = true;
      lvl1 = 3;
    } else if (p1 == "computer[4]") {
      is_com1 = true;
      lvl1 = 4;
    } else {
      p1 = "";
      continue;
    }
    }

    cin >> p2;
    if (p2 == "human"){
      is_com2 = false;
    } else if (p2 == "computer[1]") {
      is_com2 = true;
      lvl2 = 1;
    } else if (p2 == "computer[2]") {
      is_com2 = true;
      lvl2 = 2;
    } else if (p2 == "computer[3]") {
      is_com2 = true;
      lvl2 = 3;
    } else if (p2 == "computer[4]") {
      is_com2 = true;
      lvl2 = 4;
    } else { 
      p2 = "";
      continue;
    }
  }

  Checkboard cb{is_com1,is_com2,lvl1,lvl2};
  cb.init();
  cout << cb;

  int count = 0;
    while (true) {
    cin >> cmd;
    if (cin.eof()) {
      cout << "Final Score:" << endl;
      cout << "White: " << cb.getplayer("p1")->getScore() << endl;
      cout << "Black: " << cb.getplayer("p2")->getScore() << endl;
      break;
    }
    count = count + 1;
    if (cmd == "setup") {
      if(count > 1){
        cout << "Can't setup during the game!" << endl;
        --count;
        continue;
      } else {
      cb.clear();
      cout << cb;
      while (true) {
        string s;
  	    cin >> s;
        if (s == "-") {
          string pos;
  	      cin >> pos;
          cb.unset(pos);
          cout << cb;
    	  }

        if (s == "=") {
          string s11;
          cin >> s11;
          if (s11 == "B"){
            cb.setturn("p2");
          } else if (s11 == "W"){
            cb.setturn("p1");
          }
    	  }

  	    if (s == "+") {
          string piece;
          cin >> piece;
          string pos;
          cin >> pos;
          cb.setup(piece,pos);
          cout << cb;
  	    } 
        
    	  
        if (s == "done") {
          if (!cb.verify()) { 
            cout << "Cannot leave setup." << endl;
          } else {
              if (cb.getturn() == "p1") {
                if (cb.checkmate("W")){
                  cout << "Black wins. Checkmate" << endl;
                  cb.getplayer("p2")->winscore();
                  cb.clear();
                  cb.init();
                  cout << cb;
                }
                else if (cb.check("W")) {
                  cout << "In check: White" << endl;
                }

                if (cb.stalemate("W")) {
                  cout << "Stalemate" << endl;
                  cb.clear();
                  cb.init();
                  cout << cb;
                  cb.getplayer("p2")->draw();
                  cb.getplayer("p1")->draw();
                }  
              }
              
               else if (cb.getturn() == "p2") {
                if (cb.stalemate("B")) {
                  cout << "Stalemate" << endl;
                  cb.clear();
                  cb.init();
                  cout << cb;
                  cb.getplayer("p2")->draw();
                  cb.getplayer("p1")->draw();
                }
                if (cb.checkmate("B")) {
                  cout << "White wins. Checkmate" << endl;
                  cb.getplayer("p1")->winscore();
                  cb.clear();
                  cb.init();
                  cout << cb;
                }
                else if (cb.check("B")) {
                  cout << "In check: Black" << endl;
                }
              }
              break;
          }
        }
      }
    }
    }
    else if (cmd == "move") {
      cb.move();
      cout << cb;
      
      if ((cb.getplayer(cb.getturn())->getcolor() == "W" && cb.checkmate("W"))||
          (cb.getplayer(cb.getturn())->getcolor() == "B" && cb.checkmate("B")))
	    { if(cb.getplayer(cb.getturn())->getcolor() == "B"){
        cout << "White wins. Checkmate" << endl;
        cb.clear();
        cb.init();
        cb.getplayer("p1")->winscore();
        cout << cb;
      } else if(cb.getplayer(cb.getturn())->getcolor() == "W"){
        cout << "Black wins. Checkmate" << endl;
        cb.clear();
        cb.init();
        cb.getplayer("p2")->winscore();
        cout << cb;
      }
      }
      else if ((cb.getplayer(cb.getturn())->getcolor() == "W" && cb.stalemate("W")) ||
              (cb.getplayer(cb.getturn())->getcolor() == "W" && cb.stalemate("W"))) {
        cout << "Stalemate" << endl;
        cb.clear();
        cb.init();
        cout << cb;
        cb.getplayer("p2")->draw();
        cb.getplayer("p1")->draw();
      }

    }
    else if (cmd == "resign") {
      if (cb.getturn() != "p1") {
        cb.getplayer("p1")->winscore();
        cout << "White wins!" << endl;
      }
      else {
        cb.getplayer("p2")->winscore();
        cout << "Black wins!" << endl;
      }
      cb.clear();
      cb.init();
      cout << cb;
    }
    else if (cmd == "undo") {
        cb.undo();
        cout << cb;

    }
    else if (cmd == "history") {
      cb.printmoves();
    }
    else --count;   
  }
}





