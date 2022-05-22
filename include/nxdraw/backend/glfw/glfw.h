#ifndef NXDRAW_BACKEND_GLFW_GLFW_H
#define NXDRAW_BACKEND_GLFW_GLFW_H

#include "event_bridge.h"

#include <GLFW/glfw3.h>

typedef struct nxdraw_Window {
  GLFWwindow *window;
  int screen_width;
  int screen_height;
  double pixel_width;
  double pixel_height;
  char *title;
} nxdraw_Window;

int nxdraw_window_init(nxdraw_Window *self, int width, int height) {
  // nxdraw_Window self;
  self->screen_width = width;
  self->screen_height = height;
  self->pixel_width = (double)self->screen_width / (double)width;
  self->pixel_height = (double)self->screen_height / (double)height;

  if (!glfwInit()) {
    // FIXME add error
  }

  // if (resizable) {
  //  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  //} else {
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  //}

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  self->window = glfwCreateWindow(self->screen_width, self->screen_height,
                                  "nxdraw", NULL, NULL);

  if (!self->window) {
    glfwTerminate();
    // FIXME add error
  }

  glfwSetKeyCallback(self->window, nxlib_event_bridge_key);
  glfwSetCharCallback(self->window, nxlib_event_bridge_character);
  glfwSetCursorPosCallback(self->window, nxlib_event_bridge_mousepos);
  glfwSetMouseButtonCallback(self->window, nxlib_event_bridge_mousebutton);

  glfwMakeContextCurrent(self->window);

  glEnable(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glfwSwapInterval(1);

  // return self;
  return 0;
}

void nxdraw_window_render(nxdraw_Window *self, void *data, int width,
                          int height) {
  /*
  static const GLfloat coords[2 * 6] = {
  0.0, 1.0, //
  0.0, 0.0, //
  1.0, 1.0, //
  1.0, 1.0, //
  0.0, 0.0, //
  1.0, 0.0, //
  };

  static const GLfloat vertexes[2 * 6] = {
  -1.0f, -1.0f, //
  -1.0f, 1.0f,  //
  1.0f,  -1.0f, //
  1.0f,  -1.0f, //
  -1.0f, 1.0f,  //
  1.0f,  1.0f,  //
  };
  */

  self->pixel_width = (double)self->screen_width / (double)width;
  self->pixel_height = (double)self->screen_height / (double)height;

  glClear(GL_COLOR_BUFFER_BIT);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

  /*
  glClientActiveTexture(GL_TEXTURE0 + 1);
  glVertexPointer(2, GL_FLOAT, 0, &vertexes);
  glTexCoordPointer(2, GL_FLOAT, 0, &coords);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  */

  glBegin(GL_TRIANGLES);
  glTexCoord2f(0.0, 1.0); // 01
  glVertex2f(-1.0f, -1.0f);
  glTexCoord2f(0.0, 0.0); // 00
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0, 1.0); // 11
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(1.0, 1.0); // 11
  glVertex2f(1.0f, -1.0f);
  glTexCoord2f(0.0, 0.0); // 00
  glVertex2f(-1.0f, 1.0f);
  glTexCoord2f(1.0, 0.0); // 10
  glVertex2f(1.0f, 1.0f);
  glEnd();

  glfwSwapBuffers(self->window);
}

int nxdraw_window_tick(nxdraw_Window *self) {
  glfwPollEvents();
  return !glfwWindowShouldClose(self->window);
}

#endif
