#include <iostream>
#include <xcb/xcb.h>

int main() {
    // Bağlantıyı oluştur
    xcb_connection_t* connection = xcb_connect(0, NULL);

    // Olay maskesini ayarla
    uint32_t event_mask = XCB_EVENT_MASK_FOCUS_CHANGE;

    // Pencere oluştur
    xcb_window_t window = xcb_generate_id(connection);
    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, XCB_NONE, 0, 0, 200, 200, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, XCB_COPY_FROM_PARENT, XCB_CW_EVENT_MASK, &event_mask);
        xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

    // Pencereyi harici uygulamalardan odak değişikliklerini dinlemek için kaydet
    xcb_change_window_attributes(connection, screen->root, XCB_CW_EVENT_MASK, &event_mask);
/*
   uint32_t values[] = { XCB_EVENT_MASK_PROPERTY_CHANGE };
    xcb_change_window_attributes(
        conn,
        screen->root,
        XCB_CW_EVENT_MASK,
        values);
*/

    // Bağlantıyı senkronize et
    xcb_flush(connection);

    // Olay döngüsü & ~0x80
    xcb_generic_event_t* event;
    while ((event = xcb_wait_for_event(connection))) {
        switch (event->response_type ) {
            case XCB_FOCUS_IN:
                std::cout << "Başka bir uygulama odaklandı!" << std::endl;
                break;
            default:
                // Diğer olayları işle
                break;
        }
        free(event);
    }

    // Bağlantıyı kapat
    xcb_disconnect(connection);

    return 0;
}

