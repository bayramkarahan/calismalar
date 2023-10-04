#include <iostream>
#include <xcb/xcb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include<xcb/xproto.h>
#include <X11/Xatom.h>
#include <X11/Xlib-xcb.h>
int main() {
    // X sunucusuna bağlanma
    xcb_connection_t* connection = xcb_connect(0, NULL);
    
    // Olay maskesini oluşturma
    uint32_t event_mask = XCB_EVENT_MASK_PROPERTY_CHANGE;
    
    // Olay maskesini ayarlama
    //xcb_change_window_attributes(connection, XCB_WINDOW_ROOT, XCB_CW_EVENT_MASK, &event_mask);
    xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
xcb_window_t rootWindow = screen->root;
xcb_change_window_attributes(connection, rootWindow, XCB_CW_EVENT_MASK, &event_mask);

    // Olay döngüsü
    xcb_generic_event_t* event;
    while ((event = xcb_wait_for_event(connection))) {
        switch (event->response_type & ~0x80) {
            case XCB_PROPERTY_NOTIFY: {
                xcb_property_notify_event_t* property_event = (xcb_property_notify_event_t*)event;
                std::cout << "Özellik değişikliği olayı alındı: " << property_event->atom << std::endl;
                break;
            }
            default:
            std::cout << "Özellik değişikliği olayı alındı: " << std::endl;
                // Diğer olayları işleme
                break;
        }
        free(event);
    }
    
    // Bağlantıyı kapatma
    xcb_disconnect(connection);
    
    return 0;
}
