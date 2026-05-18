#include "handler.h"
#include "file.h"
#include "sniffing.h"

void precess_exit_handler(int sig)
{
    if(sig == SIGINT)
    {
        printf("프로세스을 종료합니다.");
        
        all_exit_files();
        all_disconnect_serialport();
        
        exit(sig);
    }
}