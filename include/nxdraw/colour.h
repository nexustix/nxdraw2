#ifndef NXDRAW_COLOUR_H
#define NXDRAW_COLOUR_H

typedef enum nxdraw_Depth {
  NXD_DEPTH_VOID = 0,
  // NXD_DEPTH_1,
  // NXD_DEPTH_2,
  // NXD_DEPTH_4,
  NXD_DEPTH_8,
  NXD_DEPTH_16,
  NXD_DEPTH_24,
  NXD_DEPTH_32,
} nxdraw_Depth;

typedef struct nxdraw_Colour {
  unsigned int c[4];
  int d;
} nxdraw_Colour;

#endif
