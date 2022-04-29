#ifndef NXDRAW_DRAW_AREA_H
#define NXDRAW_DRAW_AREA_H

typedef struct nxd_DrawArea {

  int x1;
  int y1;
  int x2;
  int y2;
  int w;
  int h;
} nxd_DrawArea;

static nxd_DrawArea _area = {0};
static int _area_active = 0;

int nxdraw_draw_area_translate(int *x, int *y) {
  // if (_area_active && *x >= _area.x1 && *y >= _area.y1 && *x <= _area.x2 &&
  //    *y <= _area.y2) {
  //}

  if (_area_active) {
    *x += _area.x1;
    *y += _area.y1;
    if (_area_active && *x >= _area.x1 && *y >= _area.y1 && *x < _area.x2 &&
        *y < _area.y2) {
      return 1;
    } else {
      return 0;
    }
  }
  return 1;
}

int nxdraw_draw_area_translate_x(int *x) {
  if (_area_active) {
    *x += _area.x1;
    if (_area_active && *x >= _area.x1 && *x < _area.x2) {
      return 1;
    } else {
      return 0;
    }
  }
  return 1;
}

int nxdraw_draw_area_translate_y(int *y) {
  if (_area_active) {
    *y += _area.y1;
    if (_area_active && *y >= _area.y1 && *y < _area.y2) {
      return 1;
    } else {
      return 0;
    }
  }
  return 1;
}

#endif
