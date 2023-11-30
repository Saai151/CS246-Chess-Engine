#include <X11/Xlib.h>
#include <X11/Xutil.h>
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
  char color_vals[5][10]={"white", "black", "red", "green", "blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
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
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

std::vector<int> GraphicsDisplay::map(Square s) { 
  int cell_len = 500/gridSize; 
  Location l = s.getLocation();
  int col = l.getFile() - 'A';
  int row = l.getRank() - 1; 
  int x = col * cell_len;
  int y = row * cell_len;
  std::vector<int> dimensions = {x, y, cell_len};
  return dimensions;
}

GraphicsDisplay::GraphicsDisplay(Xwindow &w) : w{w} {
  gridSize = 8; // 8 x 8 chess board
  w.fillRectangle(0, 0, 500, 500);
}

// void GraphicsDisplay::notify(Cell &c) {
//   int colour = c.getState() ? Xwindow::White : Xwindow::Black;
//   std::vector<int> dimensions = map(c);
//   int x = dimensions[0];
//   int y = dimensions[1];
//   int len = dimensions[2];
//   w.fillRectangle(x, y, len, len, colour);
// }

GraphicsDisplay::~GraphicsDisplay() {
}

// SubscriptionType GraphicsDisplay::subType() {
//   return SubscriptionType::All;
// }