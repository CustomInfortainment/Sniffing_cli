#include "command.h"
#include "utility.h"
#include "log.h"

const char* send_linux_command(char* cmd)
{
    char* buf = (char*)malloc(MAX_LINE_CNT);
    size_t totalsize = 0;

    FILE* pipe = NULL;

    if(popen(pipe, "r") != NULL)
    {
        while(fgets(buf, MAX_LINE_CNT, pipe) != NULL)
        {
            totalsize += strlen(buf);
            if(totalsize > MAX_LINE_CNT)
            {
                resize_memory(buf, totalsize);
            }
        }
    }
    return buf;
}