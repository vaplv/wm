#ifndef WM_GLFW_ERROR_H
#define WM_GLFW_ERROR_H

#include "../wm_error.h"
#include <sl/sl_error.h>
#include <snlsys/snlsys.h>

LOCAL_SYM enum wm_error
sl_to_wm_error
  (enum sl_error sl_err);

#endif /* WM_GLFW_ERROR_H */

