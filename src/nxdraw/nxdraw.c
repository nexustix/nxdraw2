#include "nxdraw/nxdraw.h"
#include "nxdraw/colour.h"
#include "nxdraw/draw.h"
#include "nxdraw/event_buffer.h"
#include "nxdraw/screen.h"
#include "nxdraw/time.h"

#include "nxdraw/char_draw.h"
#include "nxdraw/draw_area.h"

#include "nxdraw/backend/glfw/glfw.h"

#include <bits/types/clock_t.h>
#include <time.h>

static nxdraw_Screen _screen;
// static nxdraw_Colour _fg = {{255, 255, 255, 255}, 4};
// static nxdraw_Colour _bg = {{0, 0, 0, 255}, 4};
static unsigned int _fg = 1;
static unsigned int _bg = 2;

static nxdraw_Window _window;
static nxd_Event _event;

static int _char_w = 8;
static int _char_h = 8;
static int _cursor_x = 0;
static int _cursor_y = 0;

//
//
// Lifecycle
//
//

int nxd_cleanup() { return 0; }
int nxd_window(int width, int height) {
  nxdraw_window_init(&_window, width, height);
  return 0;
}

int nxd_screen(unsigned char *sprite, int width, int height, int depth) {
  _screen.width = width;
  _screen.height = height;
  _screen.d = depth;
  _screen.pixelcount = _screen.width * _screen.height;
  _screen.size = _screen.pixelcount * _screen.d;

  _screen.data = sprite;

  nxd_area_disable();

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
int nxd_area_enable(int x, int y, int w, int h) {
  _area.x1 = x;
  _area.y1 = y;
  _area.x2 = x + w;
  _area.y2 = y + h;
  _area.w = w;
  _area.h = h;
  _area_active = 1;
  return 0;
}
int nxd_area_disable() {
  _area.x1 = 0;
  _area.y1 = 0;
  _area.x2 = _screen.width;
  _area.y2 = _screen.height;
  _area.w = _screen.width;
  _area.h = _screen.height;
  _area_active = 1;
  return 0;
}
int nxd_area_info(int *x, int *y, int *w, int *h) {
  *x = _area.x1;
  *y = _area.y1;
  *w = _area.w;
  *h = _area.h;
  return 0;
}

//
//
// Palette
//
//
int nxd_palette(unsigned char *data, unsigned int size) {
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

int nxd_palette_swap() {
  unsigned int tfg = _fg;
  _fg = _bg;
  _bg = tfg;
  return 0;
}

//
//
// Cursor
//
//

int nxd_cursor_set_x(int x) {
  _cursor_x = x * _char_w;
  return _cursor_x;
}
int nxd_cursor_set_y(int y) {
  _cursor_y = y * _char_h;
  return _cursor_y;
}
// int nxd_cursor_getr_x(){
//  return _cursor_x;
//}
// int nxd_cursor_getr_y(){
//  return _cursor_y;
//}
int nxd_cursor_set(int x, int y) {
  _cursor_x = x * _char_w;
  _cursor_y = y * _char_h;
  return 0;
}
int nxd_cursor_setraw(int x, int y) {
  _cursor_x = x;
  _cursor_y = y;
  return 0;
}
int nxd_cursor_move(int dx, int dy) {
  _cursor_x += dx * _char_w;
  _cursor_y += dy * _char_h;
  return 0;
}
int nxd_cursor_cr() {
  _cursor_x = 0;
  _cursor_y += _char_h;
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
int nxd_draw_fill() {
  nxd_draw_rectangle(0, 0, _screen.width, _screen.height);
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

int nxd_draw_char(unsigned char *font, unsigned char c) {
  nxdraw_char_draw(&_screen, font, _fg, _bg, 8, c, _cursor_x, _cursor_y);

  _cursor_x += _char_w;
  int tmpx = _cursor_x;
  if (!nxdraw_draw_area_translate_x(&tmpx)) {
    _cursor_x = 0;
    _cursor_y += _char_h;
  }
  // int tmpy = _cursor_y;
  // if (!nxdraw_draw_area_translate_y(&tmpy)) {
  //  _cursor_x = 0;
  //  _cursor_y = 0;
  //}
  return 0;
}

int nxd_draw_cstring(unsigned char *font, const char *cstring) {
  unsigned char c = 0;
  for (int i = 0;; i++) {
    if ((c = cstring[i])) {
      nxd_draw_char(font, (unsigned char)c);
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

int nxd_event_init(void *data, unsigned int size) {
  return nxdraw_event_buffer_init(data, size);
}

int nxd_event_peek() { return nxdraw_event_buffer_peek(&_event); }

int nxd_event_pop() { return nxdraw_event_buffer_pop(&_event); }

int nxd_event_get(nxd_Event *event) {
  *event = _event;
  return 0;
}

int nxd_events() { return nxdraw_event_buffer_count() > 0; }

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
