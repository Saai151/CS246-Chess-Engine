#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Board.h"

class Board;

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  //std::vector<std::string> readXPMFile(const std::string& filename);

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Beige, Tan, Brown}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  // Places a piece on a square;
  //void placePiece(const char* xpm_data[], int x, int y);
};

class GraphicsDisplay {
  Xwindow w;
  Board b;
  int gridSize;
  std::vector<int> map(Square s);
  void drawBorders(int width, int colour);
  //const char *nameToimgPath(std::string name, pieceColor color);

 public:
  GraphicsDisplay(Xwindow &w, Board &b);
  void DisplayUpdate();
  //void notify(Cell &c) override;
  //SubscriptionType subType() override;

  ~GraphicsDisplay();
};

int fileToInt(File file); 

#endif
