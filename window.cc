#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL); 
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[8][10]={"white", "black", "red", "green", "blue", "beige", "tan", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 8; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  // Load a bold font with a larger size
  XFontStruct *fontInfo;
  fontInfo = XLoadQueryFont(d, "lucidasanstypewriter-bold-24"); // This is an example font name
  // Set the font for the graphics context
  XSetFont(d, DefaultGC(d, s), fontInfo->fid);
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
  // Free the font structure when done
  XFreeFont(d, fontInfo);
}

std::vector<int> GraphicsDisplay::map(Square* s) { 
  int cell_len = 500/gridSize; 
  Location l = s->getLocation();
  int col = fileToInt(l.getFile());
  int row = l.getRank(); 
  int x = col * cell_len;
  int y = (gridSize - row - 1) * cell_len;
  std::vector<int> dimensions = {x, y, cell_len};
  return dimensions;
}

void GraphicsDisplay::drawBorders(int width, int colour) {
  w.fillRectangle(0, 0, 500, width, colour);
  w.fillRectangle(0, 500-width, 500, width, colour);
  w.fillRectangle(0, 0, width, 500, colour);
  w.fillRectangle(500-width, 0, width, 500, colour);
}

GraphicsDisplay::GraphicsDisplay(Xwindow &w) : w{w} {
  gridSize = 8; // 8 x 8 chess board
  w.fillRectangle(0, 0, 500, 500);
}

void GraphicsDisplay::handleStateChange(Square* s) {
    std::vector<int> dimensions = map(s);
    int x = dimensions[0];
    int y = dimensions[1];
    int len = dimensions[2];
    int colour = s->getColor() == ChessColor::White ? Xwindow::Beige : Xwindow::Tan;
    w.fillRectangle(x, y, len, len, colour);

    if (s->isOccupied()) {
      string message = s->getOccupant()->printable();
      w.drawString(x + (len/2 - 5), y + len - (len / 2 - 5), message);
    }
}

GraphicsDisplay::~GraphicsDisplay() {
}
