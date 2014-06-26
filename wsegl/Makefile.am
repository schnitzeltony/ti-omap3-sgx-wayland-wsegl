lib_LTLIBRARIES = waylandwsegl.la

waylandwsegl_la_SOURCES =		\
	waylandwsegl.c			\
	$(COMMON_SOURCES)

waylandwsegl_la_CFLAGS =		\
	$(WAYLAND_CLIENT_CFLAGS)	\
	$(WAYLAND_SERVER_CFLAGS)	\
	-I$(top_srcdir)/common		\
	-I$(top_srcdir)/libegl		\
	-I$(top_srcdir)/libgbm		\
	-I$(top_srcdir)/libwayland-egl

waylandwsegl_la_LIBADD =		\
	$(top_builddir)/common/libwlwseglcommon.la \
	$(top_builddir)/libwayland-egl/libwayland-egl.la \
	$(top_builddir)/libegl/libEGL.la \
	$(top_builddir)/libgbm/libgbm.la \
	$(PVR2D_LIB)

waylandwsegl_la_LDFLAGS =		\
	$(WAYLAND_CLIENT_LIBS)		\
	$(WAYLAND_SERVER_LIBS)		\
	-module				\
	-no-undefined			\
	-avoid-version

sysconf_DATA = powervr.ini
