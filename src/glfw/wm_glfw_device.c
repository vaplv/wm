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
#include "glfw/wm_glfw_device_c.h"
#include "glfw/wm_glfw_error.h"
#include "glfw/wm_glfw_input.h"
#include "wm.h"
#include "wm_device.h"

#include <sl/sl.h>
#include <sys/mem_allocator.h>
#include <sys/sys.h>

#include <GL/glfw.h>
#include <stdlib.h>

struct wm_device* g_device = NULL;

/*******************************************************************************
 *
 * Helper functions.
 *
 ******************************************************************************/
static void
release_device(struct ref* ref)
{
  struct wm_device* device = NULL;
  ASSERT(ref);

  device = CONTAINER_OF(ref, struct wm_device, ref);

  WM(shutdown_inputs(device));
  if(g_device) {
    ASSERT(device == g_device);
    g_device = NULL;
    glfwSetKeyCallback(NULL);
    glfwSetCharCallback(NULL);
    glfwTerminate();
  }
  MEM_FREE(device->allocator, device);
}

/*******************************************************************************
 *
 * Device functions.
 *
 ******************************************************************************/
EXPORT_SYM enum wm_error
wm_create_device
  (struct mem_allocator* specific_allocator,
   struct wm_device** out_device)
{
  struct mem_allocator* allocator = NULL;
  struct wm_device* device = NULL;
  enum wm_error err = WM_NO_ERROR;

  if(!out_device) {
    err = WM_INVALID_ARGUMENT;
    goto error;
  }
  if(NULL != g_device) {
    err = WM_INVALID_CALL;
    goto error;
  }
  allocator = specific_allocator ? specific_allocator : &mem_default_allocator;
  device = MEM_ALLOC(allocator, sizeof(struct wm_device));
  if(!device) {
    err = WM_MEMORY_ERROR;
    goto error;
  }
  device->allocator = allocator;
  ref_init(&device->ref);

  if(GL_FALSE == glfwInit()) {
    err = WM_INTERNAL_ERROR;
    goto error;
  }
  glfwOpenWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_VERSION_MINOR, 3);
  glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

  err = wm_init_inputs(device);
  if(err != WM_NO_ERROR)
    goto error;

  g_device = device;

exit:
  if(out_device)
    *out_device = device;
  return err;

error:
  if(device) {
    WM(device_ref_put(device));
    device = NULL;
  }
  goto exit;
}

EXPORT_SYM enum wm_error
wm_device_ref_get(struct wm_device* device)
{
  if(!device)
    return WM_INVALID_ARGUMENT;
  ref_get(&device->ref);
  return WM_NO_ERROR;
}

EXPORT_SYM enum wm_error
wm_device_ref_put(struct wm_device* device)
{
  if(!device)
    return WM_INVALID_ARGUMENT;
  ref_put(&device->ref, release_device);
  return WM_NO_ERROR;
}

EXPORT_SYM enum wm_error
wm_flush_events(struct wm_device* device)
{
  if(!device)
    return WM_INVALID_ARGUMENT;

  glfwPollEvents();
  return WM_NO_ERROR;
}

