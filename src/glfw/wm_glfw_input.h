#ifndef WM_GLFW_INPUT_H
#define WM_GLFW_INPUT_H

#include "../wm_error.h"
#include <snlsys/snlsys.h>

struct wm_device;

LOCAL_SYM enum wm_error
wm_init_inputs
  (struct wm_device* device);

LOCAL_SYM enum wm_error
wm_shutdown_inputs
  (struct wm_device* device);

#endif /* WM_GLFW_INPUT_H */

