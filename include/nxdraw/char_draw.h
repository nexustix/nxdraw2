#ifndef NXDRAW_CHAR_DRAW_H
#define NXDRAW_CHAR_DRAW_H

#include "colour.h"
#include "draw.h"

static void nxlib_bitmap_draw_line2(nxdraw_Screen *screen,
                                    unsigned char *bitmap, int offset,
                                    unsigned int fg, unsigned int bg, int x,
                                    int y) {
  int mask = 1;
  int i;
  for (i = 0; i < 8; i++) {
    if (bitmap[offset] & (mask << i)) {
      // nxlib_texture_pixel_apply(tex, col_fg, x + (7 - i), y);
      nxdraw_draw_pixel(screen, fg, x + (7 - i), y);
    } else {
      // nxlib_texture_pixel_apply(tex, col_bg, x + (7 - i), y);
      nxdraw_draw_pixel(screen, bg, x + (7 - i), y);
    }
  }
}

static void nxlib_bitmap_draw_square2(nxdraw_Screen *screen,
                                      unsigned char *bitmap, unsigned int fg,
                                      unsigned int bg, int x, int y) {
  int i;
  for (i = 0; i < 8; i++) {
    // nxlib_bitmap_draw_line2(self, tex, col_fg, col_bg, i, x, y + i);
    nxlib_bitmap_draw_line2(screen, bitmap, i, fg, bg, x, y + i);
  }
}

int nxdraw_char_draw(nxdraw_Screen *screen, unsigned char *bitmaps,
                     unsigned int fg, unsigned int bg, unsigned int stride,
                     unsigned char c, int x, int y) {
  nxlib_bitmap_draw_square2(screen, &bitmaps[stride * (unsigned int)c], fg, bg,
                            x, y);

  return 1;
}

#endif
