#include "nxdraw/event_buffer.h"
#include "nxdraw/event.h"

static nxdraw_EventBuffer buffer;

int nxdraw_event_buffer_init(void *data, unsigned int size) {
  buffer.data = data;
  buffer.items_max = size / sizeof(nxd_Event);
  buffer.begin = 0;
  buffer.end = 0;
  return 0;
}

int nxdraw_event_buffer_empty() { return buffer.begin == buffer.end; }
int nxdraw_event_buffer_push(const nxd_Event *event) {
  buffer.data[buffer.end] = *event;
  buffer.end = (buffer.end + 1) % buffer.items_max;
  if (buffer.begin == buffer.end) {
    buffer.begin = (buffer.begin + 1) % buffer.items_max;
  }
  return 0;
}

int nxdraw_event_buffer_peek(nxd_Event *event) {
  if (!nxdraw_event_buffer_empty()) {
    *event = buffer.data[buffer.begin];
  }
  return 1;
}
int nxdraw_event_buffer_drop() {
  if (!nxdraw_event_buffer_empty()) {
    buffer.begin = (buffer.begin + 1) % buffer.items_max;
  }
  return 1;
}

int nxdraw_event_buffer_pop(nxd_Event *event) {
  if (!nxdraw_event_buffer_empty()) {
    *event = buffer.data[buffer.begin];
    buffer.begin = (buffer.begin + 1) % buffer.items_max;
  }
  return 1;
}
