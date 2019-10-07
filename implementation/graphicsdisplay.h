#ifndef _GRAPHICSDISPALY_H_
#define _GRAPHICSDISPALY_H_
#include "observer.h"
#include "coordinate.h"
#include "window.h"

class GraphicsDisplay: public Observer {
  Xwindow xw;
  const int size = 8;
  public:
  void print_curr_state();
  GraphicsDisplay();
  void init();
  void notify(Subject &whoNotified) override;
};
#endif


