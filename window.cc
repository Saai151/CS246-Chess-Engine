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

void Xwindow::placePiece(int x, int y, int cell_len, const char* piecePath) {
  // Load the image
  Pixmap pixmap;
  XpmCreatePixmapFromData(d, w, (char**)(const char*)piecePath, &pixmap, NULL, NULL);

  // Draw the image on the specified square
  XCopyArea(d, pixmap, w, gc, 0, 0, cell_len, cell_len, x, y);
  XFreePixmap(d, pixmap);
}

std::vector<int> GraphicsDisplay::map(Square s) { 
  int cell_len = 500/gridSize; 
  Location l = s.getLocation();
  int col = static_cast<char>(l.getFile()) - 'A';
  int row = l.getRank(); 
  int x = col * cell_len;
  int y = (gridSize - row) * cell_len;
  std::vector<int> dimensions = {x, y, cell_len};
  return dimensions;
}

// assume name is a valid chess piece name.
const char* GraphicsDisplay::nameToimgPath(string name, pieceColor color) {
  if (name == "Pawn") {
    if (color == pieceColor::White) {
      return "./pieces_images/Chess_plt60.png";
    }
    return "./pieces_images/Chess_pdt60.png";
  } else if (name == "Knight") {
    if (color == pieceColor::White) {
      return "./pieces_images/Chess_nlt60.png";
    }
    return "./pieces_images/Chess_ndt60.png";
  } else if (name == "Bishop") {
    if (color == pieceColor::White) {
      return "./pieces_images/Chess_blt60.png";
    }
    return "./pieces_images/Chess_bdt60.png";
  } else if (name == "Rook") {
    if (color == pieceColor::White) {
      return "./pieces_images/Chess_rlt60.png";
    }
    return "./pieces_images/Chess_rdt60.png";
  } else if (name == "Queen") {
    if (color == pieceColor::White) {
      return "./pieces_images/Chess_qlt60.png";
    }
    return "./pieces_images/Chess_qdt60.png";
  } else { // must be King
    if (color == pieceColor::White) {
      return "./pieces_images/Chess_klt60.png";
    }
    return "./pieces_images/Chess_kdt60.png";
  }
}

GraphicsDisplay::GraphicsDisplay(Xwindow &w, Board &b) : w{w}, b{b} {
  gridSize = 8; // 8 x 8 chess board
  w.fillRectangle(0, 0, 500, 500);
}

void GraphicsDisplay::DisplayUpdate() {
  for (Square s : b.squares) {
    std::vector<int> dimensions = map(s);
    int x = dimensions[0];
    int y = dimensions[1];
    int len = dimensions[2];
    //cout << "x,y = " << x << "," << y << endl;
    int colour = s.getColor() == color::light ? Xwindow::White : Xwindow::Black;
    w.fillRectangle(x, y, len, len, colour);
  }
  for (AbstractPiece p : b.pieces) {
    //Square s = b.squares[0];
    // std::vector<int> dimensions = map(s);
    // int x = dimensions[0];
    // int y = dimensions[1];
    // int len = dimensions[2];
    // const char *img_path = nameToimgPath(p.getName(), p.getPieceColor());
    // w.placePiece(x, y, len, img_path);
    break;
  }
}

GraphicsDisplay::~GraphicsDisplay() {
}

// SubscriptionType GraphicsDisplay::subType() {
//   return SubscriptionType::All;
// }