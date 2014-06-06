/*
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Based on
 * 	https://github.com/robclark/libgbm/blob/master/backend_example.c
 * 	http://cgit.freedesktop.org/mesa/mesa/tree/src/gbm/backends/dri/gbm_dri.c
 * Authors:
 *    Andreas Müller <schnitzeltony@googlemail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <unistd.h>
#include <dlfcn.h>

#include "gbmint.h"
#include "gbm_pvr_omap3_int.h"
#include "wlwsegl-log.h"

static int
gles_init(struct gbm_pvr_omap3_device *dev)
{
   /* this should open/initialize the GLES stack.. for a DRM driver
    * at least, dev->base.base.fd will have the already opened device
    */
   return 0;
}

static int
gbm_pvr_omap3_is_format_supported(struct gbm_device *gbm,
      enum gbm_bo_format format, uint32_t usage)
{
   wsegl_debug("pvr_omap3 gbm check format");
   return 0;
}

static int
gbm_pvr_omap3_bo_write(struct gbm_bo *_bo, const void *buf, size_t count)
{
   wsegl_debug("Write pvr_omap3 gbm buffer");
/*   struct gbm_dri_bo *bo = gbm_dri_bo(_bo);

   if (bo->image != NULL) {
      errno = EINVAL;
      return -1;
   }

   memcpy(bo->map, buf, count);*/

   return 0;
}

static int
gbm_pvr_omap3_bo_get_fd(struct gbm_bo *_bo)
{
/*   struct gbm_dri_device *dri = gbm_dri_device(_bo->gbm);
   struct gbm_dri_bo *bo = gbm_dri_bo(_bo);
   int fd;

   if (bo->image == NULL)
      return -1;

   dri->image->queryImage(bo->image, __DRI_IMAGE_ATTRIB_FD, &fd);

   return fd;*/
   return NULL;
}

static void
gbm_pvr_omap3_bo_destroy(struct gbm_bo *_bo)
{
   wsegl_debug("Destroy pvr_omap3 gbm buffer");
}

static struct gbm_bo *
gbm_pvr_omap3_bo_import(struct gbm_device *gbm,
                  uint32_t type, void *buffer, uint32_t usage)
{
   wsegl_debug("Import pvr_omap3 gbm buffer");
/*   struct gbm_dri_device *dri = gbm_dri_device(gbm);
   struct gbm_dri_bo *bo;
   __DRIimage *image;
   int gbm_format;

    
   switch (type) {
#if HAVE_WAYLAND_PLATFORM
   case GBM_BO_IMPORT_WL_BUFFER:
   {
      struct wl_drm_buffer *wb;

      if (!dri->wl_drm) {
         errno = EINVAL;
         return NULL;
      }

      wb = wayland_drm_buffer_get(dri->wl_drm, (struct wl_resource *) buffer);
      if (!wb) {
         errno = EINVAL;
         return NULL;
      }

      image = dri->image->dupImage(wb->driver_buffer, NULL);

      switch (wb->format) {
      case WL_DRM_FORMAT_XRGB8888:
         gbm_format = GBM_FORMAT_XRGB8888;
         break;
      case WL_DRM_FORMAT_ARGB8888:
         gbm_format = GBM_FORMAT_ARGB8888;
         break;
      case WL_DRM_FORMAT_RGB565:
         gbm_format = GBM_FORMAT_RGB565;
         break;
      case WL_DRM_FORMAT_YUYV:
         gbm_format = GBM_FORMAT_YUYV;
         break;
      default:
         return NULL;
      }
      break;
   }
#endif

   case GBM_BO_IMPORT_EGL_IMAGE:
   {
      int dri_format;
      if (dri->lookup_image == NULL) {
         errno = EINVAL;
         return NULL;
      }

      image = dri->lookup_image(dri->screen, buffer, dri->lookup_user_data);
      image = dri->image->dupImage(image, NULL);
      dri->image->queryImage(image, __DRI_IMAGE_ATTRIB_FORMAT, &dri_format);
      gbm_format = gbm_dri_to_gbm_format(dri_format);
      if (gbm_format == 0) {
         errno = EINVAL;
         return NULL;
      }
      break;
   }

   case GBM_BO_IMPORT_FD:
   {
      struct gbm_import_fd_data *fd_data = buffer;
      int stride = fd_data->stride, offset = 0;

      image = dri->image->createImageFromFds(dri->screen,
                                             fd_data->width,
                                             fd_data->height,
                                             fd_data->format,
                                             &fd_data->fd, 1,
                                             &stride, &offset,
                                             NULL);
      gbm_format = fd_data->format;
      break;
   }

   default:
      errno = ENOSYS;
      return NULL;
   }


   bo = calloc(1, sizeof *bo);
   if (bo == NULL)
      return NULL;

   bo->image = image;

   if (usage & GBM_BO_USE_SCANOUT)
      dri_use |= __DRI_IMAGE_USE_SCANOUT;
   if (usage & GBM_BO_USE_CURSOR_64X64)
      dri_use |= __DRI_IMAGE_USE_CURSOR;
   if (dri->image->base.version >= 2 &&
       !dri->image->validateUsage(bo->image, dri_use)) {
      errno = EINVAL;
      free(bo);
      return NULL;
   }

   bo->base.base.gbm = gbm;
   bo->base.base.format = gbm_format;

   dri->image->queryImage(bo->image, __DRI_IMAGE_ATTRIB_WIDTH,
                          (int*)&bo->base.base.width);
   dri->image->queryImage(bo->image, __DRI_IMAGE_ATTRIB_HEIGHT,
                          (int*)&bo->base.base.height);
   dri->image->queryImage(bo->image, __DRI_IMAGE_ATTRIB_STRIDE,
                          (int*)&bo->base.base.stride);
   dri->image->queryImage(bo->image, __DRI_IMAGE_ATTRIB_HANDLE,
                          &bo->base.base.handle.s32);

   return &bo->base.base; */
   return NULL;
}

static struct gbm_bo *
gbm_pvr_omap3_bo_create(struct gbm_device *gbm, uint32_t width, uint32_t height,
      enum gbm_bo_format format, uint32_t usage)
{
   wsegl_debug("Create pvr_omap3 gbm buffer w: %u h: %u", width, height);
/*   struct gbm_dri_device *dri = gbm_dri_device(gbm);
   struct gbm_dri_bo *bo;
   int dri_format;
   unsigned dri_use = 0;

   if (usage & GBM_BO_USE_WRITE)
      return create_dumb(gbm, width, height, format, usage);

   bo = calloc(1, sizeof *bo);
   if (bo == NULL)
      return NULL;

   bo->base.base.gbm = gbm;
   bo->base.base.width = width;
   bo->base.base.height = height;
   bo->base.base.format = format;

   switch (format) {
   case GBM_FORMAT_RGB565:
      dri_format =__DRI_IMAGE_FORMAT_RGB565;
      break;
   case GBM_FORMAT_XRGB8888:
   case GBM_BO_FORMAT_XRGB8888:
      dri_format = __DRI_IMAGE_FORMAT_XRGB8888;
      break;
   case GBM_FORMAT_ARGB8888:
   case GBM_BO_FORMAT_ARGB8888:
      dri_format = __DRI_IMAGE_FORMAT_ARGB8888;
      break;
   case GBM_FORMAT_ABGR8888:
      dri_format = __DRI_IMAGE_FORMAT_ABGR8888;
      break;
   case GBM_FORMAT_ARGB2101010:
      dri_format = __DRI_IMAGE_FORMAT_ARGB2101010;
      break;
   case GBM_FORMAT_XRGB2101010:
      dri_format = __DRI_IMAGE_FORMAT_XRGB2101010;
      break;
   default:
      errno = EINVAL;
      goto failed;
   }

   if (usage & GBM_BO_USE_SCANOUT)
      dri_use |= __DRI_IMAGE_USE_SCANOUT;
   if (usage & GBM_BO_USE_CURSOR_64X64)
      dri_use |= __DRI_IMAGE_USE_CURSOR;

   bo->image =
      dri->image->createImage(dri->screen,
                              width, height,
                              dri_format, dri_use,
                              bo);
   if (bo->image == NULL)
      goto failed;

   dri->image->queryImage(bo->image, __DRI_IMAGE_ATTRIB_HANDLE,
                          &bo->base.base.handle.s32);
   dri->image->queryImage(bo->image, __DRI_IMAGE_ATTRIB_STRIDE,
                          (int *) &bo->base.base.stride);

   return &bo->base.base;

failed:
   free(bo);*/
   return NULL;
}

static struct gbm_surface *
gbm_pvr_omap3_surface_create(struct gbm_device *gbm,
                       uint32_t width, uint32_t height,
		       uint32_t format, uint32_t flags)
{
   struct gbm_pvr_omap3_surface *surf;

   wsegl_debug("Create pvr_omap3 gbm surface w: %u h: %u", width, height);
   surf = calloc(1, sizeof *surf);
   if (surf == NULL)
      return NULL;

   surf->base.gbm = gbm;
   surf->base.width = width;
   surf->base.height = height;
   surf->base.format = format;
   surf->base.flags = flags;

   return &surf->base;
}

static void
gbm_pvr_omap3_surface_destroy(struct gbm_surface *_surf)
{
   struct gbm_pvr_omap3_surface *surf = gbm_pvr_omap3_surface(_surf);

   free(surf);
}

static void
gbm_pvr_omap3_destroy(struct gbm_device *gbm)
{
   wsegl_info("Destroy pvr_omap3 gbm device");
}

static struct gbm_device *
pvr_omap3_device_create(int fd)
{
   wsegl_info("Create pvr_omap3 gbm device");
   struct gbm_pvr_omap3_device *dev;
   int ret;

   dev = calloc(1, sizeof *dev);

   dev->base.base.fd = fd;
   dev->base.base.bo_create = gbm_pvr_omap3_bo_create;
   dev->base.base.bo_import = gbm_pvr_omap3_bo_import;
   dev->base.base.is_format_supported = gbm_pvr_omap3_is_format_supported;
   dev->base.base.bo_write = gbm_pvr_omap3_bo_write;
   dev->base.base.bo_get_fd = gbm_pvr_omap3_bo_get_fd;
   dev->base.base.bo_destroy = gbm_pvr_omap3_bo_destroy;
   dev->base.base.destroy = gbm_pvr_omap3_destroy;
   dev->base.base.surface_create = gbm_pvr_omap3_surface_create;
   dev->base.base.surface_destroy = gbm_pvr_omap3_surface_destroy;

   dev->base.type = GBM_DRM_DRIVER_TYPE_CUSTOM;
   dev->base.base.name = "pvr_omap3";

   ret = gles_init(dev);
   if (ret) {
      free(dev);
      return NULL;
   }

   return &dev->base.base;
}

/* backend loader looks for symbol "gbm_backend" */
GBM_EXPORT struct gbm_backend gbm_backend = {
   .backend_name = "pvr_omap3",
   .create_device = pvr_omap3_device_create,
};
