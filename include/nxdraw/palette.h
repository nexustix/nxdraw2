#ifndef NXDRAW_PALETTE_H
#define NXDRAW_PALETTE_H

#include "colour.h"

//#define NXDRAW_PALETTE_DEPTH 4

typedef struct nxdraw_Palette {
  nxdraw_Depth depth;
  unsigned int count;
  unsigned char *data;
} nxdraw_Palette;

static nxdraw_Palette _palette = {0, 0, 0};

static const unsigned char black[4] = {0, 0, 0, 255};
static const unsigned char white[4] = {0xee, 0xee, 0xee, 255};
static const unsigned char zilch[4] = {127, 0, 127, 255};

int nxdraw_palette_set(unsigned char *data, unsigned int size,
                       unsigned int depth) {
  _palette.depth = depth;
  _palette.count = size / depth;
  _palette.data = data;
  return 0;
}

const unsigned char *nxdraw_palette_get_colour(unsigned int id) {

  if (_palette.data) {
    if (id < _palette.count) {
      return &_palette.data[_palette.depth * id];
    }
  } else if (id == 0) {
    return black;
  } else if (id == 1) {
    return white;
  }

  return zilch;
}

int nxdraw_palette_set_colour_rgb(unsigned int id, unsigned char r,
                                  unsigned char g, unsigned char b) {

  if (_palette.data && id < _palette.count) {
    _palette.data[_palette.depth * id + 0] = r;
    _palette.data[_palette.depth * id + 1] = g;
    _palette.data[_palette.depth * id + 2] = b;
    _palette.data[_palette.depth * id + 3] = 255;
    return 0;
  }

  return 1;
}

#endif
