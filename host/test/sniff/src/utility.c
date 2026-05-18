#include "utility.h"

const char* get_current_day()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    const char buf[256];

    snprintf(buf, sizeof(buf), "%d-%d-%d", 
    tm.tm_year+1900, 
    tm.tm_mon+1, 
    tm.tm_mday);

    return buf;
}