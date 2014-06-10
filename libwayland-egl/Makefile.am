lib_LTLIBRARIES = libwayland-egl.la

libwayland_egl_la_SOURCES =	\
	wayland-egl.c		\
	wayland-egl-priv.h

libwayland_egl_la_CFLAGS =	\
	-I$(top_srcdir)/common	\
	-I$(top_srcdir)/libegl

libwayland_egl_la_LDFLAGS = 	\
	-version-info 1

libwayland_egl_la_LIBADD =	\
	$(top_builddir)/common/libwlwseglcommon.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = wayland-egl.pc
