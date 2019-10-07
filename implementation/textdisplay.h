#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include <string>
#include "subject.h"

class Coordinate;

class TextDisplay : public Observer {
  std::vector<std::vector<char>> theDisplay;
  const int size = 8;
 public:
   TextDisplay();
   void init();
   void notify(Subject &whoNotified) override;
   void print_curr_state();
  
   friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif


