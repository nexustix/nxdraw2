#ifndef NXDRAW_TIME_H
#define NXDRAW_TIME_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void nxlib_sleep(unsigned ms) {
#ifdef _WIN32
  Sleep(ms);
#else
  usleep(ms * 1000);
#endif
}

#endif
