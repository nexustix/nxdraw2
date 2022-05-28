#ifndef NXDRAW_PALETTE_H
#define NXDRAW_PALETTE_H

#include "nxdraw/pixelformat.h"

typedef struct nxdraw_Palette {
  // nxdraw_Pixelformat format;
  unsigned int depth;
  unsigned int count;
  unsigned char *data;
} nxdraw_Palette;

static const unsigned char black[4] = {0, 0, 0, 0xff};
static const unsigned char white[4] = {0xee, 0xee, 0xee, 0xff};
static const unsigned char zilch[4] = {0x7f, 0, 0x7f, 0xff};

int nxdraw_palette_set(nxdraw_Palette *self, unsigned char *data,
                       unsigned int size, unsigned int depth) {
  self->depth = depth;
  self->count = size / depth;
  self->data = data;
  return 0;
}

const unsigned char *nxdraw_palette_get_colour(nxdraw_Palette *self,
                                               unsigned int id) {

  if (self->data) {
    if (id < self->count) {
      return &self->data[self->depth * id];
    }
  } else if (id == 0) {
    return black;
  } else if (id == 1) {
    return white;
  }

  return zilch;
}

int nxdraw_palette_set_colour_rgb(nxdraw_Palette *self, unsigned int id,
                                  unsigned char r, unsigned char g,
                                  unsigned char b) {

  if (self->data && id < self->count) {
    self->data[self->depth * id + 0] = r;
    self->data[self->depth * id + 1] = g;
    self->data[self->depth * id + 2] = b;
    self->data[self->depth * id + 3] = 0xff;
    return 0;
  }

  return 1;
}

#endif
