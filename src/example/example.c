#include "nxdraw/event.h"
#include "nxdraw/nxdraw.h"

#include "nxdraw/fonts/testfont.h"

#include <stdio.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
//#define SCREEN_HEIGHT 200
#define EVENTS_SIZE 512

unsigned char screen[NXDRAW_SIZE_SCREEN(SCREEN_WIDTH, SCREEN_HEIGHT)];
unsigned char palette[NXDRAW_SIZE_PALETTE(16)];
unsigned char events[EVENTS_SIZE];

typedef enum MyColours {
  C___ = 0, // NOne
  CWHT = 1, // WHite
  CBLK = 2, // BlacK
  CLBK,     // Light blacK
  CRED,     // ReD
  CORG,     // OranGe

} MyColours;

unsigned char example_image[8 * 8] = {
    CRED, C___, C___, C___, C___, C___, C___, CBLK, //
    C___, CRED, CRED, C___, C___, C___, C___, C___, //
    C___, CRED, C___, C___, C___, C___, C___, C___, //
    C___, C___, C___, C___, C___, C___, C___, C___, //
    C___, C___, C___, C___, C___, C___, C___, C___, //
    C___, C___, C___, C___, C___, C___, C___, C___, //
    CWHT, CWHT, C___, C___, C___, C___, CORG, CORG, //
    CWHT, C___, C___, C___, C___, C___, C___, CORG, //
};

int pos_x = 0;
int pos_y = 0;

int main() {
  int dt;

  // tell nxdraw where to store it's data
  nxd_init_event(events, EVENTS_SIZE);
  nxd_init_window(SCREEN_WIDTH * 4, SCREEN_HEIGHT * 4);
  nxd_init_canvas(screen, SCREEN_WIDTH, SCREEN_HEIGHT, 4);
  nxd_init_palette(palette, 16 * 4);

  // initialize palette colours
  nxd_palette_rgb(CWHT, 255, 255, 255);
  nxd_palette_rgb(CBLK, 0, 0, 0);
  nxd_palette_rgb(CLBK, 16, 16, 16);
  nxd_palette_rgb(CRED, 127, 0, 0);
  nxd_palette_rgb(CORG, 255, 127, 0);

  // set foreground and background colours
  nxd_palette_fg(CORG);
  nxd_palette_bg(CLBK);

  // clear
  nxd_draw_clear();
  // while the program is ticking...
  while (nxd_tick()) {
    // limit to 30 FPS
    dt = nxd_time_await_limit(30);

    nxd_palette_fg(CRED);
    nxd_palette_bg(CLBK);

    // while there are events
    while (nxd_events()) {
      // pop an event
      nxd_event_pop();
      // check for type and act
      if (nxd_event_kind() == NXD_EVENT_MOUSE_MOVE) {
        pos_x = nxd_event_x();
        pos_y = nxd_event_y();
        nxd_draw_pixel(pos_x, pos_y);
      }
      if (nxd_event_kind() == NXD_EVENT_KEY_DOWN) {
        printf("pressed key %i\n", nxd_event_key());
      }
    }

    // draw all characters in font
    nxd_palette_fg(CORG);
    nxd_palette_bg(C___);
    for (int i = 0; i < 255; i++) {
      nxd_draw_char(testfont, i, (i % 20) * 8, (i / 20) * 8);
    }
    nxd_palette_bg(CRED);

    nxd_draw_bitmap(example_image, 8, 8, 30, 60);

    // draw rectangle
    nxd_draw_rectangle(80, 60, 10, 25);
    // swap foreground an background colours
    nxd_palette_swap();
    // draw rectangle border
    nxd_draw_rectangleb(82, 62, 10, 25);

    // clip drawing to an area
    nxd_clip(13, 100, 100, 50);
    // add a global translation to simplify coordinates
    nxd_translate(10, 90);

    // draw some text
    nxd_draw_cstring(testfont, "the quick brown", 0, 8 * 1);
    nxd_draw_cstring(testfont, "fox jumps over", 0, 8 * 2);
    nxd_draw_cstring(testfont, "the lazy dog", 0, 8 * 3);
    nxd_draw_cstring(testfont, "THE QUICK BROWN", 0, 8 * 4);
    nxd_draw_cstring(testfont, "FOX JUMPS OVER", 0, 8 * 5);
    nxd_draw_cstring(testfont, "THE LAZY DOG", 0, 8 * 6);

    // reset global translation
    nxd_translate(0, 0);
    // disable clip area
    nxd_clip_disable();

    nxd_palette_fg(CWHT);
    // draw a box around where the clip area was
    nxd_draw_rectangleb(13 - 1, 100 - 1, 100 + 2, 50 + 2);

    nxd_present();
  }

  return 0;
}
