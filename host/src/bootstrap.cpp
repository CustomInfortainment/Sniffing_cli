#include "bootstrap.h"
#define MAX_LINES 256

void GetEsp32PortName()
{
    char buff[MAX_LINES];

    FILE* fp;

    fp = popen("ls /dev/tty.*", "r");

    if(fp != NULL)
    {
        while(fgets(buff, MAX_LINES, fp) != NULL)
        {
            printf("%s", buff);
        }
    }

    pclose(fp);
}