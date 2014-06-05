lib_LTLIBRARIES = libwlwseglcommon.la

wayland_protocoldir = $(top_srcdir)/protocol
include $(wayland_protocoldir)/wayland-scanner.mk

BUILT_SOURCES = \
	wayland-sgx-protocol.c		\
	wayland-sgx-client-protocol.h	\
	wayland-sgx-server-protocol.h

CLEANFILES = $(BUILT_SOURCES)

libwlwseglcommon_la_SOURCES =		\
	$(BUILT_SOURCES)		\
	server_wlegl_buffer.cpp		\
	server_wlegl_buffer.h		\
	server_wlegl.cpp		\
	server_wlegl.h			\
       	server_wlegl_private.h		\
	wlwsegl-log.c			\
	wlwsegl-log.h

