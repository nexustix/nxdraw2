#ifndef NXDRAW_EVENT_H
#define NXDRAW_EVENT_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum nxd_EventKind {
  NDX_EVENT_VOID = 0,
  NXD_EVENT_UNKNOWN,
  NXD_EVENT_KEY_DOWN,
  NXD_EVENT_KEY_UP,
  NXD_EVENT_KEY_HELT,
  NXD_EVENT_TEXT,
  NXD_EVENT_MOUSE_MOVE,
  NXD_EVENT_MOUSE_DOWN,
  NXD_EVENT_MOUSE_UP,
  NDX_EVENT_N,
} nxd_EventKind;

typedef struct nxd_Event {
  nxd_EventKind kind;      // kind
  int x;                   // x
  int y;                   // y
  unsigned int mods;       // modifier keys
  unsigned int key;        // sym of key pressed
  unsigned char ascii_low; // lowercase ASCII from sym
  unsigned int text;       // adjusted ASCII (masked UTF-n, will garble)
} nxd_Event;

#if defined(__cplusplus)
}
#endif

#endif
