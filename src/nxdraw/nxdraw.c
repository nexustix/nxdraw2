#include "nxdraw/nxdraw.h"

#include "nxdraw/bitmap.h"
#include "nxdraw/canvas.h"

//#include "nxdraw/colour.h"
#include "nxdraw/draw.h"
#include "nxdraw/event_buffer.h"
//#include "nxdraw/screen.h"
#include "nxdraw/pixelformat.h"
#include "nxdraw/time.h"

//#include "nxdraw/char_draw.h"
#include "nxdraw/draw_area.h"

#include "nxdraw/backend/glfw/glfw.h"

//#include <bits/types/clock_t.h>
#include <time.h>

static nxdraw_Canvas canvas_;
//  static nxdraw_Colour _fg = {{255, 255, 255, 255}, 4};
//  static nxdraw_Colour _bg = {{0, 0, 0, 255}, 4};
static unsigned int _fg = 1;
static unsigned int _bg = 2;

static nxdraw_Window _window;
static nxd_Event _event;

static int _char_w = 8;

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

  canvas_.width = width;
  canvas_.height = height;
  // canvas_.d = depth;
  canvas_.pixelformat = NXD_FORMAT_RGBA_8888;
  canvas_.pixelcount = canvas_.width * canvas_.height;
  canvas_.size = canvas_.pixelcount * nxdraw_canvas_bytes_per_pixel(&canvas_);

  canvas_.data = sprite;

  nxd_clip_disable();

  return 0;
}

int nxd_screen_info(int *width, int *height) {
  *width = canvas_.width;
  *height = canvas_.height;
  return 0;
}

int nxd_fullscreen(int state) { return state != 0; }

int nxd_tick() { return nxdraw_window_tick(&_window); }

int nxd_present() {
  nxdraw_window_render(&_window, canvas_.data, canvas_.width, canvas_.height);
  return 0;
}

//
//
// Area
//
//
int nxd_clip(int x, int y, int w, int h) {
  area_.x1 = (x >= 0) ? (x < canvas_.width) ? x : canvas_.width : 0;
  area_.y1 = (y >= 0) ? (y < canvas_.width) ? y : canvas_.height : 0;
  area_.x2 = (x + w >= 0) ? (x + w < canvas_.width) ? x + w : canvas_.width : 0;
  area_.y2 =
      (y + h >= 0) ? (y + h < canvas_.width) ? y + h : canvas_.height : 0;
  return 0;
}
int nxd_clip_disable() {
  area_.x1 = 0;
  area_.y1 = 0;
  area_.x2 = canvas_.width;
  area_.y2 = canvas_.height;

  return 0;
}

int nxd_clip_info(int *x, int *y, int *w, int *h) {
  *x = area_.x1;
  *y = area_.y1;
  *w = area_.x2 - area_.x1;
  *h = area_.y2 - area_.y1;
  return 0;
}

int nxd_translate(int x, int y) {
  area_.xt = x;
  area_.yt = y;
  return 0;
}
int nxd_translate_info(int *x, int *y) {
  *x = area_.xt;
  *y = area_.yt;
  return 0;
}

//
//
// Palette
//
//
int nxd_init_palette(unsigned char *data, unsigned int size) {
  nxdraw_palette_set(&palette_, data, size, 4);
  return 0;
}

int nxd_palette_rgb(unsigned int id, unsigned char r, unsigned char g,
                    unsigned char b) {
  nxdraw_palette_set_colour_rgb(&palette_, id, r, g, b);
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
  // nxdraw_draw_pixel(&canvas_, &_fg, x, y);
  nxdraw_canvas_put(&canvas_, _fg, x, y);
  return 0;
}

int nxd_draw_line(int x1, int y1, int x2, int y2) {
  // if (nxdraw_draw_area_translate(&x, &y))
  // nxdraw_draw_pixel(&canvas_, &_fg, x, y);
  nxdraw_draw_line(&canvas_, _fg, x1, y1, x2, y2);
  return 0;
}

int nxd_draw_rectangle(int x, int y, int w, int h) {
  nxdraw_draw_rectangle(&canvas_, _fg, x, y, w, h);
  return 0;
}
int nxd_draw_rectangleb(int x, int y, int w, int h) {
  nxdraw_draw_rectangleb(&canvas_, _fg, x, y, w, h);
  return 0;
}
int nxd_draw_clear() {
  nxdraw_draw_rectangle(&canvas_, _bg, 0 - area_.xt, 0 - area_.yt,
                        canvas_.width, canvas_.height);
  return 0;
}

int nxd_draw_bitmap(unsigned char *bitmap, int width, int height, int x,
                    int y) {
  int i = 0;
  for (int py = 0; py < height; py++) {
    for (int px = 0; px < width; px++) {

      nxdraw_canvas_put(&canvas_, bitmap[i], x + px, y + py);
      i++;
    }
  }
  return 0;
}

int nxd_draw_char(unsigned char *font, unsigned char c, int x, int y) {
  nxdraw_char_draw(&canvas_, font, _fg, _bg, 8, c, x, y);
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
