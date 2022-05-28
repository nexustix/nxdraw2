#ifndef NXDRAW_CANVAS_H
#define NXDRAW_CANVAS_H

#include "nxdraw/draw_area.h"
#include "nxdraw/palette.h"
#include "nxdraw/pixelformat.h"

typedef struct nxdraw_Canvas {
  unsigned char *data;
  int width;
  int height;
  int pixelcount;
  int size;
  nxdraw_Pixelformat pixelformat;
} nxdraw_Canvas;

nxd_DrawArea area_ = {0};
nxdraw_Palette palette_ = {0};

int nxdraw_canvas_put(nxdraw_Canvas *canvas, unsigned int colour_id, int x,
                      int y) {
  if (colour_id) {
    const unsigned char *pcol = nxdraw_palette_get_colour(&palette_, colour_id);
    nxdraw_draw_area_translate(&area_, &x, &y);
    if (nxdraw_draw_area_inside(&area_, x, y)) {
      int index = (y * canvas->width) + x;
      if (index >= 0 && index < canvas->pixelcount) {
        switch (canvas->pixelformat) {
        case NXD_FORMAT_8:
          canvas->data[index] = pcol[0];
          break;
        case NXD_FORMAT_88:
          canvas->data[(index * 2) + 0] = pcol[0];
          canvas->data[(index * 2) + 1] = pcol[1];
          break;
        case NXD_FORMAT_RGB_888:
        case NXD_FORMAT_888:
          canvas->data[(index * 3) + 0] = pcol[0];
          canvas->data[(index * 3) + 1] = pcol[1];
          canvas->data[(index * 3) + 2] = pcol[2];
          break;
        case NXD_FORMAT_RGBA_8888:
        case NXD_FORMAT_8888:
          canvas->data[(index * 4) + 0] = pcol[0];
          canvas->data[(index * 4) + 1] = pcol[1];
          canvas->data[(index * 4) + 2] = pcol[2];
          canvas->data[(index * 4) + 3] = pcol[3];
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

int nxdraw_canvas_bytes_per_pixel(nxdraw_Canvas *canvas) {
  switch (canvas->pixelformat) {
  case NXD_FORMAT_8:
    return 1;
    break;
  case NXD_FORMAT_88:
    return 2;
    break;
  case NXD_FORMAT_RGB_888:
  case NXD_FORMAT_888:
    return 3;
    break;
  case NXD_FORMAT_RGBA_8888:
  case NXD_FORMAT_8888:
    return 4;
    break;
  case NXD_FORMAT_VOID:
    break;
  }
  return 4;
}

#endif
