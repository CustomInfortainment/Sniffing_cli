#include "log.h"

void prt_logconsole(char* log)
{
    time_t current;
    time(&current);
    struct tm* t = localtime(&current);

    printf("%02d:%02d:%02d > %s\n", t->tm_hour, t->tm_min, t->tm_sec, log);
}