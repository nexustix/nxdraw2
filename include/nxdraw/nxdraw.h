#ifndef NXDRAW_NXDRAW_H
#define NXDRAW_NXDRAW_H

#define NXDRAW_SIZE_SCREEN(w, h) ((w) * (h)*4)
#define NXDRAW_SIZE_PALETTE(n) ((n)*4)

#include "event.h"

int nxd_window(int width, int height);
int nxd_cleanup();

int nxd_screen(unsigned char *sprite, int width, int height, int depth);
int nxd_screen_info(int *width, int *height);
int nxd_fullscreen(int state);
int nxd_tick();
int nxd_present();

//// clip area
int nxd_clip_enable(int x, int y, int w, int h);
int nxd_clip_disable();
int nxd_clip_info(int *x, int *y, int *w, int *h);

// stuff format
// int nxd_format(int w, int h, int d);
// int nxd_format_info(int *w, int *h, int *d);
int nxd_format_char(int w, int h);

//// palette
int nxd_palette(unsigned char *data, unsigned int size);
// int nxd_palette_set(int id, int d, unsigned char v);
int nxd_palette_rgb(unsigned int id, unsigned char r, unsigned char g,
                    unsigned char b);
int nxd_palette_fg(unsigned int id);
int nxd_palette_bg(unsigned int id);
int nxd_palette_swap();

// drawing
int nxd_draw_pixel(int x, int y);
int nxd_draw_line(int x1, int y1, int x2, int y2);
// int nxd_draw_lineh(int x, int y, int w);
// int nxd_draw_linev(int x, int y, int h);
int nxd_draw_rectangle(int x, int y, int w, int h);
int nxd_draw_rectangleb(int x, int y, int w, int h);
int nxd_draw_fill();
// int nxd_draw_circle(int x, int y, int r);
// int nxd_draw_circleb(int x, int y, int r);
// int nxd_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);
// int nxd_draw_triangleb(int x1, int y1, int x2, int y2, int x3, int y3);
// int nxd_draw_sprite(void *sprite, int x, int y);
// int nxd_draw_tile(void *tilemap, int index, int x, int y);
int nxd_draw_bitmap(unsigned char *bitmap, int width, int height, int x, int y);
int nxd_draw_char(unsigned char *font, unsigned char c, int x, int y);
int nxd_draw_cstring(unsigned char *font, const char *cstring, int x, int y);

// event
int nxd_event_init(void *data, unsigned int size);
// int nxd_event_push(const nxd_Event *event);
int nxd_event_get(nxd_Event *event);
int nxd_event_peek();
int nxd_event_pop();
int nxd_events();
int nxd_event_kind();
int nxd_event_x();
int nxd_event_y();
unsigned int nxd_event_mods();
unsigned int nxd_event_key();
unsigned char nxd_event_ascii_low();
unsigned int nxd_event_text();

//// time
int nxd_time_sleep(int ms);
// int nxd_time_await();
int nxd_time_await_limit(int fps);
// int nxd_time_delta();

#endif
