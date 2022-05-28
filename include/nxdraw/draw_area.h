#ifndef NXDRAW_DRAW_AREA_H
#define NXDRAW_DRAW_AREA_H

typedef struct nxd_DrawArea {
  int x1;
  int y1;
  int x2;
  int y2;
  int xt;
  int yt;
} nxd_DrawArea;

int nxdraw_draw_area_inside(nxd_DrawArea *self, int x, int y) {
  return (x >= self->x1 && x < self->x2 && y >= self->y1 && y < self->y2);
  return 0;
}

int nxdraw_draw_area_translate(nxd_DrawArea *self, int *x, int *y) {
  *x += self->xt;
  *y += self->yt;
  return 0;
}

#endif
