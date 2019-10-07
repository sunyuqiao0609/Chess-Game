#include "textdisplay.h"
using namespace std;
#include "piece.h"
TextDisplay::TextDisplay(): theDisplay{}, size{8} {
  int i = 0;

  while(i < 8){
   int j = 0;
    vector<char> v;
    while(j < 8){
      if((i + j) % 2 == 1) {
        v.emplace_back('-');
      } else {
        v.emplace_back(' ');
      }
      ++j;
    }
    theDisplay.emplace_back(v);
    ++i;
  }
}

void TextDisplay::init() {
  int i = 0;
  while(i < 8){
    int j = 0;
    while(j < 8){
      if(i == 0){
        if (j == 0) theDisplay[i][j] = 'r';
        if (j == 1) theDisplay[i][j] = 'n';
        if (j == 2) theDisplay[i][j] = 'b';
        if (j == 3) theDisplay[i][j] = 'q';
        if (j == 4) theDisplay[i][j] = 'k';
        if (j == 5) theDisplay[i][j] = 'b';
        if (j == 6) theDisplay[i][j] = 'n';
        if (j == 7) theDisplay[i][j] = 'r';
      } else
      if(i == 7){
        if (j == 0) theDisplay[i][j] = 'R';
        if (j == 1) theDisplay[i][j] = 'N';
        if (j == 2) theDisplay[i][j] = 'B';
        if (j == 3) theDisplay[i][j] = 'Q';
        if (j == 4) theDisplay[i][j] = 'K';
        if (j == 5) theDisplay[i][j] = 'B';
        if (j == 6) theDisplay[i][j] = 'N';
        if (j == 7) theDisplay[i][j] = 'R';
      } else
      if(i == 6){
        theDisplay[i][j] = 'P';
      } else
      if(i == 1){
        theDisplay[i][j] = 'p';
      } else
      if((i + j) % 2 == 1){
        theDisplay[i][j] = '-';
      } else if((i + j) % 2 == 0){
        theDisplay[i][j] = ' ';
      }
      ++j;
    }
    ++i;
  }
}


void TextDisplay::print_curr_state(){
  std::cout<<"The above funtion works properly"<<endl;
}


void TextDisplay::notify(Subject &whoNotified) {
  int c = whoNotified.getc() - 'a';
  int r = whoNotified.getr() - '1';
  if (whoNotified.hasoccupied()) theDisplay[7 - r][c] = (whoNotified.getoccupied())->getname();
  else if (whoNotified.getcolor() == "B") theDisplay[7 - r][c] = '-';
  else theDisplay[7-r][c] = ' '; 
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  int i = 0;
  while(i < td.size){
	int j = 0;
    while(j < td.size){
      if (j == 0) {
        int r = 8 - i;
        cout << r << " ";
      }
      cout << td.theDisplay[i][j];
      if (j == td.size - 1) {
        cout << endl;
      }
      if (i == td.size - 1 && j == td.size - 1) {
        cout << endl;
        cout << " ";
        char c = 'a';
        int p = 0;
        while(p < td.size){
          char n = c + p;
          cout << n;
          if (p == td.size - 1) {
            cout << endl;
          }
          ++p;
        }
        
      }
      ++j;
    }
    ++i;
  }
  return out;
}



