#ifndef LOG_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void
wsegl_info(const char *fmt, ...);
void
wsegl_debug(const char *fmt, ...);

#ifdef  __cplusplus
}
#endif

#endif

