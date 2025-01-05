#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "subject.h"
class Cell;

class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
 public:
  TextDisplay(size_t n);

  void notify(Subject<Info, State> &whoNotified) override;

  std::vector<std::vector<char>> showDisplay();
};
#endif
