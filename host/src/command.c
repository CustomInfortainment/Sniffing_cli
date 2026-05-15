#include "command.h"
#include "utility.h"
#include "log.h"

char* getpowercmdtostr(uint8_t sig)
{
    switch(sig)
    {
        case CMD_ACC_ON:
            return "ACC_ON";
        case CMD_ACC_OFF:
            return "ACC_OFF";
        case CMD_SHUTDOWN:
            return "SHUTDOWN";
        case CMD_SLEEP:
            return "SLEEP";
        case CMD_HIBERNATE:
            return "HIBERNATE";        
    }
}

char* getpowercmdtolinux(uint8_t sig)
{
    switch(sig)
    {
        case CMD_SHUTDOWN:
            return "shutdown";
        case CMD_SLEEP:
            return "systemctl hibernate";
        case CMD_HIBERNATE:
            return "systemctl hybrid-sleep";        
    }
}

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
    process_exit_code = pclose(pipe);
    return buf;
}