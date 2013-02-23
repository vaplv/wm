#ifndef WM_H
#define WM_H

#include "wm_error.h"
#include <snlsys/snlsys.h>

#ifndef NDEBUG
  #define WM(func) ASSERT(WM_NO_ERROR == wm_##func)
#else
  #define WM(func) wm_##func
#endif /* NDEBUG */

#if defined(WM_SHARED_BUILD)
  #define WM_API EXPORT_SYM
#else
  #define WM_API IMPORT_SYM
#endif

#endif /* WM_H */

