// sources:
// https://xcb.freedesktop.org/tutorial/events/
// https://xcb.freedesktop.org/manual/group__XCB____API.html
// https://github.com/wmutils/opt/blob/master/wew.c
//
// compile with:
// gcc focus.c -lxcb

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include <xcb/xcb.h>

int
main ()
{
    /* Open the connection to the X server */
    xcb_connection_t *connection = xcb_connect (NULL, NULL);

    /* Get the first screen */
    xcb_screen_t *screen = xcb_setup_roots_iterator (xcb_get_setup (connection)).data;


    /* Create the window */
    xcb_window_t window    = xcb_generate_id (connection);

    uint32_t     mask      = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t     values[2] = {screen->white_pixel,
				XCB_EVENT_MASK_FOCUS_CHANGE };

    xcb_create_window (connection,    
                       0,                             /* depth               */
                       window,                        
                       screen->root,                  /* parent window       */
                       0, 0,                          /* x, y                */
                       150, 150,                      /* width, height       */
                       10,                            /* border_width        */
                       XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                       screen->root_visual,           /* visual              */
                       mask, values );                /* masks */

    /* Map the window on the screen */
    xcb_map_window (connection, window);

    xcb_flush (connection);

    xcb_generic_event_t *event;
    while ( (event = xcb_wait_for_event (connection)) ) {
        switch (event->response_type & ~0x80) {
        case XCB_EXPOSE: {
            xcb_expose_event_t *expose = (xcb_expose_event_t *)event;

            printf ("Window %"PRIu32" exposed. Region to be redrawn at location (%"PRIu16",%"PRIu16"), with dimension (%"PRIu16",%"PRIu16")\n",
                    expose->window, expose->x, expose->y, expose->width, expose->height );
            break;
        }
        case XCB_FOCUS_IN: {
            xcb_focus_in_event_t *kr = (xcb_focus_in_event_t *)event;

            printf ("Focus In %"PRIu32"\n",
                    kr->event);
            break;
        }
        case XCB_FOCUS_OUT: {
            xcb_focus_in_event_t *kr = (xcb_focus_in_event_t *)event;

            printf ("Focus Out %"PRIu32"\n",
                    kr->event);
            break;
        }
        default:
            /* Unknown event type, ignore it */
            printf ("Unknown event: %"PRIu8"\n",
                    event->response_type);
            break;
        }

        free (event);
    }

    return 0;
}
