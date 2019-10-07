#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>

class Piece;
class Observer;
class Subject {
  std::vector<Observer*> observers;
  public:
  void attach(Observer* o);
  void notifyObservers();
  virtual char getc() const = 0;
  virtual char getr() const = 0;
  virtual std::string getcolor() const = 0;
  virtual bool hasoccupied() const = 0;
  virtual Piece* getoccupied() const = 0;
};


#endif


