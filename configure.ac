# Initialize Autoconf
AC_PREREQ([2.60])
AC_INIT([ti-omap3-sgx-wayland-wsegl], [0.2.0])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])

# Initialize Automake
AM_INIT_AUTOMAKE([foreign dist-bzip2])
AM_MAINTAINER_MODE

# Initialize libtool
AC_PROG_LIBTOOL

# check for compilers
AC_PROG_CC
AC_PROG_CXX

# weston requires mesa version for egl
MESA_VERSION=10.1.3
AC_SUBST([MESA_VERSION])

# Checks for all headers/libraries/packages we need
AC_CHECK_HEADERS([EGL/egl.h EGL/eglext.h pvr2d.h wsegl.h])

AC_CHECK_LIB([pvr2d], [PVR2DEnumerateDevices], [PVR2D_LIB=-lpvr2d])
AC_SUBST([PVR2D_LIB])

PKG_CHECK_MODULES(UDEV, libudev)
PKG_CHECK_MODULES(DRM, libdrm)
PKG_CHECK_MODULES(WAYLAND_CLIENT, wayland-client)
PKG_CHECK_MODULES(WAYLAND_SERVER, wayland-server)

AC_PATH_PROG([wayland_scanner], [wayland-scanner])
if test x$wayland_scanner = x; then
	AC_MSG_ERROR([wayland-scanner is needed to compile wayland-egl and wsegl])
fi

# variable substitutions for templates
AC_CONFIG_FILES([Makefile
		libegl/Makefile
		libegl/egl.pc
		libwayland-egl/Makefile
		libwayland-egl/wayland-egl.pc
		wsegl/Makefile])

# We generate the protocol files and need to tell automake/autoconf to include
# them from the builddir
AC_SUBST([AM_CPPFLAGS], [-I\$\(top_builddir\)/common])

AC_OUTPUT
