#include <X11/Xlib.h>
#include <iostream>
//g++ -o x x11input.c -lX11
int main() {
    Display* display = XOpenDisplay(":0");
    Window focusWindow;
    int revertTo;

    XGetInputFocus(display, &focusWindow, &revertTo);

    if (focusWindow == None) {
        std::cout << "Giriş odak noktası bulunamadı." << std::endl;
    } else {
        std::cout << "Giriş odak noktası: " << focusWindow << std::endl;
    }

    XCloseDisplay(display);
    return 0;
}

