#include "nxdraw/event.h"
#include "nxdraw/nxdraw.h"

#include "nxdraw/fonts/testfont.h"

#include <stdio.h>

//#include <stdio.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
//#define SCREEN_HEIGHT 200

unsigned char screen[NXDRAW_SIZE_SCREEN(SCREEN_WIDTH, SCREEN_HEIGHT)];
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

void testdraw(int row) {
  // nxd_draw_cstring(testfont, " 1. Longername FIGHT", 8 * 17, (8 * (1 +
  // row)));
  // nxd_draw_cstring(testfont, " 1. Longername SHOOT", 8 * 17, (8 * (1 +
  // row)));
  nxd_draw_cstring(testfont, " 1. Longername PARRY", 8 * 17, (8 * (1 + row)));
  nxd_draw_cstring(testfont, "    9999 9999  XXXX+", 8 * 17, (8 * (2 + row)));
}

int main() {
  nxd_init_event(&events, 64);
  nxd_init_window(SCREEN_WIDTH * 4, SCREEN_HEIGHT * 4);
  nxd_init_canvas(screen, SCREEN_WIDTH, SCREEN_HEIGHT, 4);
  nxd_init_palette(palette, 16 * 4);

  nxd_palette_rgb(3, 255, 127, 0);
  nxd_palette_rgb(4, 16, 16, 16);

  // nxd_area_enable(10, 10, 8 * 8, 8 * 20);
  // nxd_area_enable(10, 20, 3, 3);
  // nxd_area_disable();
  nxd_palette_fg(4);
  nxd_palette_bg(3);
  nxd_palette_swap();

  // nxd_translate(-10, -5);
  // nxd_clip(5, 1, 10, 20);

  nxd_draw_clear();
  while (nxd_tick()) {
    nxd_time_await_limit(30);
    while (nxd_events()) {
      nxd_event_pop();
      if (nxd_event_kind() == NXD_EVENT_MOUSE_MOVE) {
        pos_x = nxd_event_x();
        pos_y = nxd_event_y();
        nxd_draw_pixel(pos_x, pos_y);
      }
      if (nxd_event_kind() == NXD_EVENT_KEY_DOWN) {
        printf("hmm\n");
      }
    }
    // nxd_draw_pixel(1, 1);
    // nxd_draw_pixel(2, 2);
    // nxd_draw_pixel(3, 3);
    // nxd_draw_pixel(3, 5);

    // nxd_draw_char(testfont, 'X', 20, 20);

    for (int i = 0; i < 255; i++) {
      // nxd_draw_char(testfont, i, (i % 20) * 8, (i / 20) * 8);
    }
    // nxd_draw_cstring(testfont, "the cake is a lie", 0, SCREEN_HEIGHT - (8 *
    // 1)); nxd_draw_cstring(testfont, "the cake is a lie", 0, SCREEN_HEIGHT -
    // (8 * 2)); nxd_draw_cstring(testfont, "the cake is a lie", 0,
    // SCREEN_HEIGHT - (8 * 3)); nxd_draw_cstring(testfont, "the cake is a lie",
    // 0, SCREEN_HEIGHT - (8 * 4)); nxd_draw_cstring(testfont, "the cake is a
    // lie", 0, SCREEN_HEIGHT - (8 * 5)); nxd_draw_cstring(testfont, "the cake
    // is a lie", 0, SCREEN_HEIGHT - (8 * 6));

    nxd_draw_rectangle(8, 8, 8 * 15, 8 * 15);
    nxd_draw_rectangle(8, 8 * 18, 8 * 38, 8 * 6);

    testdraw(0);
    testdraw(2);
    testdraw(4);
    testdraw(6);
    testdraw(8);
    testdraw(10);
    testdraw(12);
    testdraw(14);

    nxd_draw_cstring(testfont, "->", 8 * 16, (8 * 1));
    nxd_draw_cstring(testfont, "<", 8 * 20, (8 * 1));

    // nxd_draw_cstring(testfont, "Koah       FIGHT", 8 * 21, (8 * 3));
    // nxd_draw_cstring(testfont, "[|||||][|||||] 3", 8 * 21, (8 * 4));
    // nxd_draw_cstring(testfont, "Koah       FIGHT", 8 * 21, (8 * 5));
    // nxd_draw_cstring(testfont, "[|||||][|||||] 3", 8 * 21, (8 * 6));
    // nxd_draw_cstring(testfont, "Koah       FIGHT", 8 * 21, (8 * 7));
    // nxd_draw_cstring(testfont, "[|||||][|||||] 3", 8 * 21, (8 * 8));
    // nxd_draw_cstring(testfont, "Koah       FIGHT", 8 * 21, (8 * 9));
    // nxd_draw_cstring(testfont, "[|||||][|||||] 3", 8 * 21, (8 * 10));
    // nxd_draw_cstring(testfont, "Koah       FIGHT", 8 * 21, (8 * 11));
    // nxd_draw_cstring(testfont, "[|||||][|||||] 3", 8 * 21, (8 * 12));

    // nxd_draw_rectangle(1, 3, 5, 7);

    // nxd_draw_bitmap(image, 8, 8, 0, 0);

    // nxd_palette_fg(4);
    // nxd_draw_rectangle(3, 3, 10, 10);

    nxd_present();
  }

  return 0;
}
