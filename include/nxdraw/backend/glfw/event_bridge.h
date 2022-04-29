#ifndef NXDRAW_BACKEND_GLFW_EVENT_BRIDGE_H
#define NXDRAW_BACKEND_GLFW_EVENT_BRIDGE_H

#include <GLFW/glfw3.h>

// handles key events
void nxlib_event_bridge_key(GLFWwindow *window, int key, int scancode,
                            int action, int mods);
// handles text input events
void nxlib_event_bridge_character(GLFWwindow *window, unsigned int codepoint);

// handles mouse cursor movement
void nxlib_event_bridge_mousepos(GLFWwindow *window, double xpos, double ypos);

// handles mousebuttons
void nxlib_event_bridge_mousebutton(GLFWwindow *window, int button, int action,
                                    int mods);

#endif
