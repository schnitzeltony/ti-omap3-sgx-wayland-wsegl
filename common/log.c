#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

static int logLevel = -1;
static int cached_tm_mday = -1;

static void log_timestamp(void)
{
	struct timeval tv;
	struct tm *brokendown_time;
	char string[128];

	gettimeofday(&tv, NULL);

	brokendown_time = localtime(&tv.tv_sec);
	if (brokendown_time == NULL)
	{
		printf("[(NULL)localtime] sgx");
		return;
	}

	if (brokendown_time->tm_mday != cached_tm_mday) {
		strftime(string, sizeof string, "%Y-%m-%d %Z", brokendown_time);
		printf("Date sgx: %s\n", string);

		cached_tm_mday = brokendown_time->tm_mday;
	}

	strftime(string, sizeof string, "%H:%M:%S", brokendown_time);

	printf("[%s.%03li] sgx: ", string, tv.tv_usec/1000);
}

static void
log_init()
{
    if (logLevel == -1) {
        const char *dbg = getenv("WSEGL_DEBUG");
        if (dbg)
            logLevel = atoi(dbg);
        else
            logLevel = 0;
    }
}

void
wsegl_info(const char *fmt, ...)
{
    log_init();

    if (logLevel == 0)
        return;

    log_timestamp();
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}

void
wsegl_debug(const char *fmt, ...)
{
    log_init();

    if (logLevel < 2)
        return;

    log_timestamp();
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}

