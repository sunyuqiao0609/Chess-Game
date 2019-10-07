#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;
class Coordinate;

class Observer {
 public:
  virtual void notify(Subject &whoFrom) = 0;
  virtual ~Observer() = default;
};

#endif


