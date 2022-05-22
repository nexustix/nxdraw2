#include "nxdraw/nxdraw.h"
#include "nxdraw/colour.h"
#include "nxdraw/draw.h"
#include "nxdraw/event_buffer.h"
#include "nxdraw/screen.h"
#include "nxdraw/time.h"

#include "nxdraw/char_draw.h"
#include "nxdraw/draw_area.h"

#include "nxdraw/backend/glfw/glfw.h"

//#include <bits/types/clock_t.h>
#include <time.h>

static nxdraw_Screen _screen;
// static nxdraw_Colour _fg = {{255, 255, 255, 255}, 4};
// static nxdraw_Colour _bg = {{0, 0, 0, 255}, 4};
static unsigned int _fg = 1;
static unsigned int _bg = 2;

static nxdraw_Window _window;
static nxd_Event _event;

static int _char_w = 8;
// static int _char_h = 8;
//  static int _cursor_x = 0;
//  static int _cursor_y = 0;

//
//
// Lifecycle
//
//

int nxd_cleanup() { return 0; }
int nxd_init_window(int width, int height) {
  nxdraw_window_init(&_window, width, height);
  return 0;
}

int nxd_init_canvas(unsigned char *sprite, int width, int height, int depth) {
  _screen.width = width;
  _screen.height = height;
  _screen.d = depth;
  _screen.pixelcount = _screen.width * _screen.height;
  _screen.size = _screen.pixelcount * _screen.d;

  _screen.data = sprite;

  nxd_clip_disable();

  return 0;
}

int nxd_screen_info(int *width, int *height) {
  *width = _screen.width;
  *height = _screen.height;
  return 0;
}

int nxd_fullscreen(int state) { return state != 0; }

int nxd_tick() { return nxdraw_window_tick(&_window); }

int nxd_present() {
  nxdraw_window_render(&_window, _screen.data, _screen.width, _screen.height);
  return 0;
}

//
//
// Area
//
//
int nxd_clip(int x, int y, int w, int h) {
  _area.x1 = (x >= 0) ? (x < _screen.width) ? x : _screen.width : 0;
  _area.y1 = (y >= 0) ? (y < _screen.width) ? y : _screen.height : 0;
  _area.x2 = (x + w >= 0) ? (x + w < _screen.width) ? x + w : _screen.width : 0;
  _area.y2 =
      (y + h >= 0) ? (y + h < _screen.width) ? y + h : _screen.height : 0;
  return 0;
}
int nxd_clip_disable() {
  _area.x1 = 0;
  _area.y1 = 0;
  _area.x2 = _screen.width;
  _area.y2 = _screen.height;

  return 0;
}

int nxd_clip_info(int *x, int *y, int *w, int *h) {
  *x = _area.x1;
  *y = _area.y1;
  *w = _area.x2 - _area.x1;
  *h = _area.y2 - _area.y1;
  return 0;
}

int nxd_translate(int x, int y) {
  _area.xt = x;
  _area.yt = y;
  return 0;
}
int nxd_translate_info(int *x, int *y) {
  *x = _area.xt;
  *y = _area.yt;
  return 0;
}

//
//
// Palette
//
//
int nxd_init_palette(unsigned char *data, unsigned int size) {
  nxdraw_palette_set(data, size, 4);
  return 0;
}

int nxd_palette_rgb(unsigned int id, unsigned char r, unsigned char g,
                    unsigned char b) {
  nxdraw_palette_set_colour_rgb(id, r, g, b);
  return 0;
}

int nxd_palette_fg(unsigned int id) {
  _fg = id;
  return 0;
}

int nxd_palette_bg(unsigned int id) {
  _bg = id;
  return 0;
}

int nxd_palette_info(int *fg, int *bg) {
  *fg = _fg;
  *bg = _bg;
  return 0;
}

int nxd_palette_swap() {
  unsigned int tfg = _fg;
  _fg = _bg;
  _bg = tfg;
  return 0;
}

//
//
// Draw
//
//

int nxd_draw_pixel(int x, int y) {
  // if (nxdraw_draw_area_translate(&x, &y))
  // nxdraw_draw_pixel(&_screen, &_fg, x, y);
  nxdraw_draw_pixel(&_screen, _fg, x, y);
  return 0;
}

int nxd_draw_line(int x1, int y1, int x2, int y2) {
  // if (nxdraw_draw_area_translate(&x, &y))
  // nxdraw_draw_pixel(&_screen, &_fg, x, y);
  nxdraw_draw_line(&_screen, _fg, x1, y1, x2, y2);
  return 0;
}

int nxd_draw_rectangle(int x, int y, int w, int h) {
  nxdraw_draw_rectangle(&_screen, _fg, x, y, w, h);
  return 0;
}
int nxd_draw_rectangleb(int x, int y, int w, int h) {
  nxdraw_draw_rectangleb(&_screen, _fg, x, y, w, h);
  return 0;
}
int nxd_draw_clear() {
  // nxd_draw_rectangle(0, 0, _screen.width, _screen.height);
  // nxd_draw_rectangle(0 - _area.xt, 0 - _area.yt, _screen.width,
  // _screen.height);
  nxdraw_draw_rectangle(&_screen, _bg, 0 - _area.xt, 0 - _area.yt,
                        _screen.width, _screen.height);
  return 0;
}

int nxd_draw_bitmap(unsigned char *bitmap, int width, int height, int x,
                    int y) {
  int i = 0;
  for (int py = 0; py < height; py++) {
    for (int px = 0; px < width; px++) {

      nxdraw_draw_pixel(&_screen, bitmap[i], x + px, y + py);
      i++;
    }
  }
  return 0;
}

int nxd_draw_char(unsigned char *font, unsigned char c, int x, int y) {
  nxdraw_char_draw(&_screen, font, _fg, _bg, 8, c, x, y);
  return 0;
}

int nxd_draw_cstring(unsigned char *font, const char *cstring, int x, int y) {
  unsigned char c = 0;
  for (int i = 0;; i++) {
    if ((c = cstring[i])) {
      nxd_draw_char(font, (unsigned char)c, x + (_char_w * i), y);
    } else {
      break;
    }
  }
  return 0;
}

//
//
// Event
//
//

int nxd_init_event(void *data, unsigned int size) {
  return nxdraw_event_buffer_init(data, size);
}

int nxd_event_peek() { return nxdraw_event_buffer_peek(&_event); }

int nxd_event_pop() { return nxdraw_event_buffer_pop(&_event); }

int nxd_event_get(nxd_Event *event) {
  *event = _event;
  return 0;
}

int nxd_events() {
  // return nxdraw_event_buffer_count() > 0;
  return !nxdraw_event_buffer_empty();
}

int nxd_event_kind() { return _event.kind; }
int nxd_event_x() { return _event.x / _window.pixel_width; }
int nxd_event_y() { return _event.y / _window.pixel_height; }
unsigned int nxd_event_mods() { return _event.mods; }
unsigned int nxd_event_key() { return _event.key; }
unsigned char nxd_event_ascii_low() { return _event.ascii_low; }
unsigned int nxd_event_text() { return _event.text; }

//
//
// Time
//
//
int nxd_time_sleep(int ms) {
  nxlib_sleep(ms);
  return 0;
}

int nxd_time_await_limit(int fps) {
  static clock_t lastTime = 0;
  static clock_t dt = 0;
  static clock_t nowTime = 0;

  clock_t clocks_per_frame = (CLOCKS_PER_SEC / fps);

  nowTime = clock();
  dt = (nowTime - lastTime);
  clock_t remain = clocks_per_frame - dt;
  if (remain > 0) {
    clock_t sleeptime = remain / (CLOCKS_PER_SEC / 1000);
    nxlib_sleep(sleeptime);

    dt = ((nowTime + remain) - lastTime);
    lastTime = clock();
    return (int)dt / (CLOCKS_PER_SEC / 1000);
  }

  lastTime = clock();

  return (int)dt / (CLOCKS_PER_SEC / 1000);
}
