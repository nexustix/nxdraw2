#include "nxdraw/event.h"
#include "nxdraw/nxdraw.h"

#include "nxdraw/fonts/testfont.h"

//#include <stdio.h>

// unsigned char testfont[8 * 256];

// unsigned char screen[200 * 200 * 4];
unsigned char screen[NXDRAW_SIZE_SCREEN(200, 200)];
unsigned char palette[NXDRAW_SIZE_PALETTE(16)];
unsigned char events[64];

unsigned char image[8 * 8] = {
    3, 0, 0, 0, 0, 0, 0, 3, //
    0, 3, 3, 0, 0, 0, 0, 0, //
    0, 3, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, 0, 0, //
    3, 3, 0, 0, 0, 0, 3, 3, //
    3, 0, 0, 0, 0, 0, 0, 3, //
};

int pos_x = 0;
int pos_y = 0;

int main() {
  nxd_event_init(&events, 64);
  nxd_window(200 * 4, 200 * 4);
  nxd_screen(screen, 200, 200, 4);
  nxd_palette(palette, 16 * 4);
  nxd_palette_rgb(3, 255, 127, 0);
  nxd_palette_rgb(4, 0, 0, 255);

  // nxd_area_enable(10, 10, 8 * 8, 8 * 20);
  //  nxd_area_enable(10, 20, 3, 3);
  //  nxd_area_disable();
  nxd_palette_fg(3);
  nxd_palette_bg(451);
  nxd_palette_swap();

  nxd_draw_fill();
  while (nxd_tick()) {
    nxd_time_await_limit(30);
    while (nxd_events()) {
      nxd_event_pop();
      if (nxd_event_kind() == NXD_EVENT_MOUSE_MOVE) {
        pos_x = nxd_event_x();
        pos_y = nxd_event_y();
        // nxd_draw_pixel(pos_x, pos_y);
      }
    }
    nxd_draw_pixel(1, 1);
    nxd_draw_pixel(2, 2);
    nxd_draw_pixel(3, 3);
    nxd_draw_pixel(3, 5);

    // nxd_cursor_set(0, 0);
    //  nxd_draw_char(testfont, 0);
    //  nxd_draw_char(testfont, 1);

    nxd_draw_char(testfont, 'X', 20, 20);

    for (int i = 0; i < 255; i++) {
      nxd_draw_char(testfont, i, (i % 20) * 8, (i / 20) * 8);
    }
    nxd_draw_cstring(testfont, "the cake is a lie", 0, 0);
    /*
    nxd_draw_char(testfont, 'B');
    nxd_cursor_cr();
    nxd_draw_cstring(testfont, "THE QUICK BROWN ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "FOX JUMPS OVER ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "THE LAZY  DOG ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "012 34567 89 ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "the quick brown ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "fox jumps over ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "the lazy  dog ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, ",.! {}[]@ ()<> ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "|~? \\/#$% &*'\" ");
    // nxd_cursor_cr();
    nxd_draw_cstring(testfont, "+-^ _`;:= ");
    // nxd_cursor_cr();
    */

    // nxd_draw_rectangle(1, 3, 5, 7);

    // nxd_draw_bitmap(image, 8, 8, 0, 0);

    // nxd_palette_fg(4);
    // nxd_draw_rectangle(3, 3, 10, 10);
    // nxd_draw_pixel(0, 0);
    // nxd_draw_pixel(1, 1);
    // nxd_draw_pixel(2, 2);

    nxd_present();
  }

  return 0;
}
