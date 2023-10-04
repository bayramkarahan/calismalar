#include <X11/Xlib.h>
#include <iostream>
#include <iostream>
#include<xcb/xcb.h>
//g++ -o x x11input.c -lX11
int main() {
  while(1){
    XNextEvent(display, &local_event);
    switch(local_event.type){
        case ConfigureNotify:
            configure_notify_handler(local_event, display);
        break;
        case MotionNotify:
            motion_handler(local_event, display);
        break;
        case CreateNotify:
            cur_win = local_event.xcreatewindow.window;
            char *window_name;
            XFetchName(display, cur_win, &window_name);
            printf("Window name: %s\n", window_name);
            if(window_name!=NULL){
                if(!strcmp(window_name, "Parent")){
                    printf("Adding borders\n");
                    XSetWindowBorderWidth(display, cur_win, 0);
                }
                XFree(window_name);
            }
        break;
        case MapNotify:
            map_notify_handler(local_event,display, infos);
        break;
        case UnmapNotify: 
            printf("UnMapNotify\n");
        break;
        case DestroyNotify:
            printf("Destroy Event\n");
            destroy_notify_handler(local_event,display);
        break;
        case ButtonPress:
            printf("Event button pressed\n");
            button_handler(local_event, display, infos);
        break;
        case KeyPress:
            printf("Keyboard key pressed\n");
            keyboard_handler(local_event, display);
        break;
        case ClientMessage:
            printf("------------ClientMessage\n");
            printf("\tMessage: %s\n", XGetAtomName(display,local_event.xclient.message_type));
            printf("\tFormat: %d\n", local_event.xclient.format); 
            Atom *atoms = (Atom *)local_event.xclient.data.l;
            int i =0;
            for(i=0; i<=5; i++){
                printf("\t\tData %d: %s\n", i, XGetAtomName(display, atoms[i]));
            }
            int nchild;
            Window *child_windows;
            Window parent_window;
            Window root_window;
            XQueryTree(display, local_event.xclient.window, &root_window, &parent_window, &child_windows, &nchild);
            printf("\tNumber of childs: %d\n", nchild);
        break;
    }    }
    return 0;
}

