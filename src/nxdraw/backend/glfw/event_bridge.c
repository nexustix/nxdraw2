#include "nxdraw/backend/glfw/event_bridge.h"
#include "nxdraw/event.h"
#include "nxdraw/event_buffer.h"

#include <GLFW/glfw3.h>

// handles key events
void nxlib_event_bridge_key(GLFWwindow *window, int rune, int scancode,
                            int action, int mods) {
  nxd_Event tmp;
  switch (action) {
  case GLFW_PRESS:
    tmp.kind = NXD_EVENT_KEY_DOWN;
    break;
  case GLFW_RELEASE:
    tmp.kind = NXD_EVENT_KEY_UP;
    break;
  case GLFW_REPEAT:
    tmp.kind = NXD_EVENT_KEY_HELT;
    break;
  default:
    tmp.kind = NXD_EVENT_UNKNOWN;
    break;
  }
  if (rune >= 65 && rune <= 90) {
    tmp.ascii_low = rune + 32;
  } else {
    tmp.ascii_low = rune;
  }
  tmp.text = rune;
  tmp.key = scancode;
  tmp.mods = mods;
  // assert(_event_buffer_initialized);
  // event_buffer_push_event(_event_buffer, tmp);
  // nxlib_event_buffer_push(tmp);
  nxdraw_event_buffer_push(&tmp);
}

// handles text input events
void nxlib_event_bridge_character(GLFWwindow *window, unsigned int codepoint) {
  nxd_Event tmp;
  tmp.kind = NXD_EVENT_TEXT;
  tmp.text = codepoint;

  // event_buffer_push_event(_event_buffer, tmp);
  // nxlib_event_buffer_push(tmp);
  nxdraw_event_buffer_push(&tmp);
}

// handles mouse cursor movement
void nxlib_event_bridge_mousepos(GLFWwindow *window, double xpos, double ypos) {
  nxd_Event tmp;
  tmp.kind = NXD_EVENT_MOUSE_MOVE;
  tmp.x = xpos;
  tmp.y = ypos;
  // nxlib_event_buffer_push(tmp);
  nxdraw_event_buffer_push(&tmp);
}

// handles mousebuttons
void nxlib_event_bridge_mousebutton(GLFWwindow *window, int button, int action,
                                    int mods) {
  nxd_Event tmp;
  switch (action) {
  case GLFW_PRESS:
    tmp.kind = NXD_EVENT_MOUSE_DOWN;
    break;
  case GLFW_RELEASE:
    tmp.kind = NXD_EVENT_MOUSE_UP;
    break;
  default:
    tmp.kind = NXD_EVENT_UNKNOWN;
    break;
  }
  tmp.key = button;
  tmp.mods = mods;
  // nxlib_event_buffer_push(tmp);
  nxdraw_event_buffer_push(&tmp);
}
