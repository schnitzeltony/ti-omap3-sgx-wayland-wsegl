lib_LTLIBRARIES = libEGL.la

libEGL_la_SOURCES =		\
	egl.c			\
	$(COMMON_SOURCES)

libEGL_la_CFLAGS = 		\
	-I$(top_srcdir)/common

libEGL_la_LDFLAGS = 		\
	-version-info 1

libEGL_la_LIBADD =	\
	$(top_builddir)/common/libwlwseglcommon.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = egl.pc
