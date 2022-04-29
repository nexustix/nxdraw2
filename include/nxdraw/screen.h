#ifndef NXDRAW_SCREEN_H
#define NXDRAW_SCREEN_H

#include "colour.h"

typedef struct nxdraw_Screen {
  unsigned char *data;
  int width;
  int height;
  int pixelcount;
  int size;
  nxdraw_Depth d;
} nxdraw_Screen;

#endif
