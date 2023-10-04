#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xcb/xcb.h>

static xcb_atom_t intern_atom(xcb_connection_t *conn, const char *atom)
{
    xcb_atom_t result = XCB_NONE;
    xcb_intern_atom_reply_t *r = xcb_intern_atom_reply(conn,
            xcb_intern_atom(conn, 0, strlen(atom), atom), NULL);
    if (r)
        result = r->atom;
    free(r);
    return result;
}

int main (int argc, char **argv)
{
    xcb_connection_t* conn = xcb_connect(0, NULL);
    if (xcb_connection_has_error(conn)) {
        printf("Cannot open daemon connection.");
        return 0;
    }

    xcb_atom_t active_window = intern_atom(conn, "_NET_ACTIVE_WINDOW");
    xcb_atom_t active_input = intern_atom(conn, "XCB_FOCUS_IN");

    xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(conn)).data;

    uint32_t values[] = { XCB_EVENT_MASK_PROPERTY_CHANGE ,XCB_EVENT_MASK_FOCUS_CHANGE};
    xcb_change_window_attributes(
        conn,
        screen->root,
        XCB_CW_EVENT_MASK,
        values);

    xcb_flush(conn);

    xcb_generic_event_t *ev;
    while ((ev = xcb_wait_for_event(conn))) {
        printf("IN LOOP\n");
        switch (ev->response_type & 0x7F) {
        case XCB_PROPERTY_NOTIFY: {
           // xcb_property_notify_event_t *e = (void *) ev;
           xcb_property_notify_event_t* e = (xcb_property_notify_event_t*)ev;
            if (e->atom == active_window)
                puts("active window changed");
            /*if (e->atom == active_input)*/
                   // puts("Focus In1");

            break;
        }
        case XCB_FOCUS_IN: {
            xcb_focus_in_event_t *e = (xcb_focus_in_event_t *)ev;

           // printf ("Focus In %"PRIu32"\n",
            //        kr->event);
           // xcb_property_notify_event_t* e = (xcb_property_notify_event_t*)ev;

            // if (e->atom == active_input)
                     puts("Focus In");
            break;
        }
        default:
            printf("IN DEFAULT\n");
            break;
        }
        free(ev);
    }

    return 0;
}
