gbmdir = $(libdir)/gbm

lib_LTLIBRARIES = libgbm.la

AUTOMAKE_OPTIONS = subdir-objects

libgbm_la_SOURCES =	\
	$(top_srcdir)/common/log.c \
	gbm.c		\
	backend.c	\
	common.c

libgbm_la_LIBADD =	\
	@UDEV_LIBS@

libgbm_la_CFLAGS =	\
	-I$(top_srcdir)/common	\
	@UDEV_CFLAGS@	\
	-D_OS_UNIX=1	\
	-DMODULEDIR='"$(gbmdir)"'

extdir = $(includedir)/gbm
ext_HEADERS =		\
	gbm.h		\
	gbmint.h	\
	common_drm.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gbm.pc


gbm_LTLIBRARIES = gbm_pvr_omap3.la

gbm_pvr_omap3_la_SOURCES =	\
	$(top_srcdir)/common/log.c \
	backend_pvr_omap3.c

gbm_pvr_omap3_la_CFLAGS =	\
	-I$(top_srcdir)/common	\
	$(AM_CFLAGS) 		\
	$(LIBDRM_CFLAGS)

gbm_pvr_omap3_la_LDFLAGS =	\
	-module			\
	-no-undefined		\
	-avoid-version

