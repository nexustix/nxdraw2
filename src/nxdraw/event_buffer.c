#include "nxdraw/event_buffer.h"
#include "nxdraw/event.h"

static nxdraw_EventBuffer buffer;

int nxdraw_event_buffer_init(void *data, unsigned int size) {
  buffer.data = data;
  buffer.items_max = size / sizeof(nxd_Event);
  buffer.items_cur = 0;
  return 0;
}

int nxdraw_event_buffer_push(const nxd_Event *event) {
  if (buffer.items_cur < buffer.items_max) {
    buffer.data[buffer.items_cur] = *event;
    buffer.items_cur++;
    return 0;
  }
  return 1;
}

int nxdraw_event_buffer_peek(nxd_Event *event) {
  if (buffer.items_cur) {
    *event = buffer.data[buffer.items_cur];
    return 0;
  }
  return 1;
}

int nxdraw_event_buffer_drop() {
  if (buffer.items_cur) {
    buffer.items_cur--;
    return 0;
  }
  return 1;
}

int nxdraw_event_buffer_pop(nxd_Event *event) {
  return nxdraw_event_buffer_peek(event) || nxdraw_event_buffer_drop();
}

unsigned int nxdraw_event_buffer_count() { return buffer.items_cur; }
