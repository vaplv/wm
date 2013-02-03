/*
 * Copyright (c) 2013 Vincent Forest
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef WM_GLFW_DEVICE_C_H
#define WM_GLFW_DEVICE_C_H

#include <sys/ref_count.h>
#include <sys/sys.h>

struct mem_allocator;
struct sl_flat_set;
struct sl_hash_table;

typedef void (*wm_callback_t)(void);
#define WM_CALLBACK(func) ((wm_callback_t)func)

struct callback { 
  wm_callback_t func; 
  void* data;
};

struct wm_device {
  struct ref ref;
  struct mem_allocator* allocator;
  struct sl_flat_set* key_clbk_list;
  struct sl_flat_set* char_clbk_list;
  struct sl_flat_set* mouse_button_clbk_list;
  struct sl_flat_set* mouse_motion_clbk_list;
  struct sl_flat_set* mouse_wheel_clbk_list;
  struct sl_hash_table* glfw_to_wm_key_htbl;
};

/* Required by GLFW. */
LOCAL_SYM struct wm_device* g_device;

#endif
