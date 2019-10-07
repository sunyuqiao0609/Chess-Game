#include "graphicsdisplay.h"
#include <string>
#include "piece.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(): xw{} {
  
  int a = 0;
  while(a < 8){
    int b = 0;
      while(b < 8){
        if ((a + b) % 2 == 1) xw.fillRectangle(b*50, a*50, 50, 50, Xwindow::Black);
        else xw.fillRectangle(b*50, a*50, 50, 50, Xwindow::White);
        ++b;
      }
      ++a;
  }
}
  	
void GraphicsDisplay::init() {
  int i = 0;
  while(i < 8){
	int j = 0;
      while(j < 8){
          if ((i + j) % 2 == 1) xw.fillRectangle(j*50, i*50, 50, 50, Xwindow::Black);
          else xw.fillRectangle(j*50, i*50, 50, 50, Xwindow::White);
          if(i == 1) xw.drawBigString((2*j+1)*25, (2*i+1)*25, "p", Xwindow::Green);
          else if(i == 6) xw.drawBigString((2*j+1)*25, (2*i+1)*25, "P", Xwindow::Red);
          else if(i == 0){
            if(j == 0){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "r", Xwindow::Green);
            } else if(j == 1){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "n", Xwindow::Green);
            } else if(j == 2){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "b", Xwindow::Green);
            } else if(j == 3){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "q", Xwindow::Green);
            } else if(j == 4){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "k", Xwindow::Green);
            } else if(j == 5){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "b", Xwindow::Green);
            } else if(j == 6){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "n", Xwindow::Green);
            } else if(j == 7){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "r", Xwindow::Green);
            }
          }
          else if(i == 7){
            if(j == 0){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "R", Xwindow::Red);
            } else if(j == 1){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "N", Xwindow::Red);
            } else if(j == 2){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "B", Xwindow::Red);
            } else if(j == 3){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "Q", Xwindow::Red);
            } else if(j == 4){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "K", Xwindow::Red);
            } else if(j == 5){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "B", Xwindow::Red);
            } else if(j == 6){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "N", Xwindow::Red);
            } else if(j == 7){
              xw.drawBigString((2*j+1)*25, (2*i+1)*25, "R", Xwindow::Red);
            }
          }
          ++j;
      }
      ++i;
  }
}


void GraphicsDisplay::print_curr_state(){
  std::cout<<"The above funtion works properly"<<endl;
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  int c = whoNotified.getc() - 'a';
  int r = 7 - (whoNotified.getr() - '1');
  string color = whoNotified.getcolor();
  if (color == "W") xw.fillRectangle(c*50, r*50, 50, 50, Xwindow::White);
  else xw.fillRectangle(c*50, r*50, 50, 50, Xwindow::Black);
  if (whoNotified.hasoccupied()) {
    string p_color = (whoNotified.getoccupied())->getcolor();
    string name = "a";
    name[0] = (whoNotified.getoccupied())->getname();
    if (p_color == "B") xw.drawBigString((2*c+1)*25, (2*r+1)*25, name, Xwindow::Green);
    else if (p_color == "W") xw.drawBigString((2*c+1)*25, (2*r+1)*25, name, Xwindow::Red);
  }
}



