gbmdir = $(libdir)/gbm

lib_LTLIBRARIES = libgbm.la

libgbm_la_SOURCES =	\
	gbm.c		\
	backend.c	\
	common.c

libgbm_la_LIBADD =	\
	$(top_builddir)/common/libwlwseglcommon.la \
	@UDEV_LIBS@

libgbm_la_CFLAGS =	\
	-I$(top_srcdir)/common	\
	@UDEV_CFLAGS@	\
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
	backend_pvr_omap3.c

gbm_pvr_omap3_la_CFLAGS =	\
	-I$(top_srcdir)/common	\
	-I$(top_srcdir)/libegl	\
	$(AM_CFLAGS) 		\
	$(LIBDRM_CFLAGS)

gbm_pvr_omap3_la_LDFLAGS =	\
	-module			\
	-no-undefined		\
	-avoid-version

gbm_pvr_omap3_la_LIBADD =	\
	$(top_builddir)/libegl/libEGL.la \
	$(top_builddir)/common/libwlwseglcommon.la

