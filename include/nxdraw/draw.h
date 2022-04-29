#ifndef NXDRAW_DRAW_H
#define NXDRAW_DRAW_H

#include "colour.h"
#include "screen.h"

#include "draw_area.h"
#include "palette.h"

static int _nxlib_abs(int n) {
  if (n < 0) {
    return -n;
  }
  return n;
}

int nxdraw_draw_pixel(nxdraw_Screen *screen, unsigned int c, int x, int y) {
  // nxdraw_Depth depth = NXD_DEPTH_32;
  if (c) {
    const unsigned char *colour = nxdraw_palette_get_colour(c);

    if (nxdraw_draw_area_translate(&x, &y) && x >= 0 && y >= 0 &&
        x < screen->width && y < screen->height) {
      int index = (y * screen->width) + x;
      if (index >= 0 && index < screen->pixelcount) {
        switch (screen->d) {
        case NXD_DEPTH_8:
          screen->data[index] = colour[0];
          break;
        case NXD_DEPTH_16:
          screen->data[(index * 2) + 0] = colour[0];
          screen->data[(index * 2) + 1] = colour[1];
          break;
        case NXD_DEPTH_24:
          screen->data[(index * 3) + 0] = colour[0];
          screen->data[(index * 3) + 1] = colour[1];
          screen->data[(index * 3) + 2] = colour[2];
          break;
        case NXD_DEPTH_32:
          screen->data[(index * 4) + 0] = colour[0];
          screen->data[(index * 4) + 1] = colour[1];
          screen->data[(index * 4) + 2] = colour[2];
          screen->data[(index * 4) + 3] = colour[3];
          break;
        default:
          return 0;
          break;
        }
      }
    }
  }
  return 1;
}

void nxdraw_draw_line(nxdraw_Screen *screen, unsigned int c, int x1, int y1,
                      int x2, int y2) {

  // TODO add special case for horizontal and vertical lines
  int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

  dx = x2 - x1;            // Delta x
  dy = y2 - y1;            // Delta y
  dxabs = _nxlib_abs(dx);  // Absolute delta
  dyabs = _nxlib_abs(dy);  // Absolute delta
  sdx = (dx > 0) ? 1 : -1; // signum function
  sdy = (dy > 0) ? 1 : -1; // signum function
  x = dyabs >> 1;
  y = dxabs >> 1;
  px = x1;
  py = y1;

  nxdraw_draw_pixel(screen, c, x1, y1);

  if (dxabs >= dyabs) {
    for (i = 0; i < dxabs; i++) {
      y += dyabs;
      if (y >= dxabs) {
        y -= dxabs;
        py += sdy;
      }
      px += sdx;
      nxdraw_draw_pixel(screen, c, px, py);
    }
  } else {
    for (i = 0; i < dyabs; i++) {
      x += dxabs;
      if (x >= dyabs) {
        x -= dyabs;
        px += sdx;
      }
      py += sdy;
      nxdraw_draw_pixel(screen, c, px, py);
    }
  }
}

void nxdraw_draw_rectangle(nxdraw_Screen *screen, unsigned int c, int x, int y,
                           int w, int h) {
  int ix;
  int iy;
  for (iy = y; iy < h + y; iy++) {
    for (ix = x; ix < w + x; ix++) {
      nxdraw_draw_pixel(screen, c, ix, iy);
    }
  }
}

void nxdraw_draw_rectangleb(nxdraw_Screen *screen, unsigned int c, int x, int y,
                            int w, int h) {
  w = w - 1;
  h = h - 1;
  nxdraw_draw_line(screen, c, x, y, x + w, y);
  nxdraw_draw_line(screen, c, x, y, x, y + h);
  nxdraw_draw_line(screen, c, x + w, y + h, x + w, y);
  nxdraw_draw_line(screen, c, x + w, y + h, x, y + h);
}

#endif
