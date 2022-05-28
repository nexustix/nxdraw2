#ifndef NXDRAW_BITMAP_H
#define NXDRAW_BITMAP_H

#include "nxdraw/canvas.h"

static void nxlib_bitmap_draw_line2(nxdraw_Canvas *canvas,
                                    unsigned char *bitmap, int offset,
                                    unsigned int fg, unsigned int bg, int x,
                                    int y) {
  int mask = 1;
  int i;
  for (i = 0; i < 8; i++) {
    if (bitmap[offset] & (mask << i)) {
      nxdraw_canvas_put(canvas, fg, x + (7 - i), y);
    } else {
      nxdraw_canvas_put(canvas, bg, x + (7 - i), y);
    }
  }
}

static void nxlib_bitmap_draw_square2(nxdraw_Canvas *canvas,
                                      unsigned char *bitmap, unsigned int fg,
                                      unsigned int bg, int x, int y) {
  int i;
  for (i = 0; i < 8; i++) {
    nxlib_bitmap_draw_line2(canvas, bitmap, i, fg, bg, x, y + i);
  }
}

int nxdraw_char_draw(nxdraw_Canvas *canvas, unsigned char *bitmaps,
                     unsigned int fg, unsigned int bg, unsigned int stride,
                     unsigned char c, int x, int y) {
  nxlib_bitmap_draw_square2(canvas, &bitmaps[stride * (unsigned int)c], fg, bg,
                            x, y);

  return 1;
}

#endif
