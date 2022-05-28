#ifndef NXDRAW_PIXELFORMAT_H
#define NXDRAW_PIXELFORMAT_H

typedef enum nxdraw_Pixelformat {
  NXD_FORMAT_VOID = 0,
  NXD_FORMAT_8,
  NXD_FORMAT_88,
  NXD_FORMAT_888,
  NXD_FORMAT_8888,

  NXD_FORMAT_RGB_888,
  NXD_FORMAT_RGBA_8888,
} nxdraw_Pixelformat;

#endif
