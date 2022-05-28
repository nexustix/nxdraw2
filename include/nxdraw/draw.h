#ifndef NXDRAW_DRAW_H
#define NXDRAW_DRAW_H

#include "nxdraw/canvas.h"

#define nxlib_abs(n) (((n) < 0) ? -(n) : (n))

void nxdraw_draw_line(nxdraw_Canvas *canvas, unsigned int colour_id, int x1,
                      int y1, int x2, int y2) {

  // TODO add special case for horizontal and vertical lines
  int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

  dx = x2 - x1;            // Delta x
  dy = y2 - y1;            // Delta y
  dxabs = nxlib_abs(dx);   // Absolute delta
  dyabs = nxlib_abs(dy);   // Absolute delta
  sdx = (dx > 0) ? 1 : -1; // signum function
  sdy = (dy > 0) ? 1 : -1; // signum function
  x = dyabs >> 1;
  y = dxabs >> 1;
  px = x1;
  py = y1;

  nxdraw_canvas_put(canvas, colour_id, x1, y1);

  if (dxabs >= dyabs) {
    for (i = 0; i < dxabs; i++) {
      y += dyabs;
      if (y >= dxabs) {
        y -= dxabs;
        py += sdy;
      }
      px += sdx;
      nxdraw_canvas_put(canvas, colour_id, px, py);
    }
  } else {
    for (i = 0; i < dyabs; i++) {
      x += dxabs;
      if (x >= dyabs) {
        x -= dyabs;
        px += sdx;
      }
      py += sdy;
      nxdraw_canvas_put(canvas, colour_id, px, py);
    }
  }
}

void nxdraw_draw_rectangle(nxdraw_Canvas *canvas, unsigned int colour_id, int x,
                           int y, int w, int h) {
  int ix;
  int iy;
  for (iy = y; iy < h + y; iy++) {
    for (ix = x; ix < w + x; ix++) {
      nxdraw_canvas_put(canvas, colour_id, ix, iy);
    }
  }
}

void nxdraw_draw_rectangleb(nxdraw_Canvas *canvas, unsigned int colour_id,
                            int x, int y, int w, int h) {
  w = w - 1;
  h = h - 1;
  nxdraw_draw_line(canvas, colour_id, x, y, x + w, y);
  nxdraw_draw_line(canvas, colour_id, x, y, x, y + h);
  nxdraw_draw_line(canvas, colour_id, x + w, y + h, x + w, y);
  nxdraw_draw_line(canvas, colour_id, x + w, y + h, x, y + h);
}

#endif
