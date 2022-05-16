#ifndef NXDRAW_EVENT_BUFFER_H
#define NXDRAW_EVENT_BUFFER_H

#include "event.h"

/*
typedef struct nxdraw_EventBuffer {
  nxd_Event *data;
  unsigned int items_max;
  unsigned int items_cur;
  // int top;
} nxdraw_EventBuffer;
*/

typedef struct nxdraw_EventBuffer {
  nxd_Event *data;
  unsigned int begin;
  unsigned int end;
  unsigned int items_max;
  // int top;
} nxdraw_EventBuffer;

int nxdraw_event_buffer_init(void *data, unsigned int size);
int nxdraw_event_buffer_empty();

int nxdraw_event_buffer_push(const nxd_Event *event);
int nxdraw_event_buffer_peek(nxd_Event *event);
int nxdraw_event_buffer_drop();
int nxdraw_event_buffer_pop(nxd_Event *event);
// unsigned int nxdraw_event_buffer_count();

#endif
