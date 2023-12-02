#include <iostream>
#include "window.h"
using namespace std;

int main(){
    Board myBoard;
    cout << myBoard;
    Xwindow w = Xwindow();
    GraphicsDisplay gd(w, myBoard);
   
    string cmd;
    while (cin >> cmd) {
        gd.DisplayUpdate();
    }
}