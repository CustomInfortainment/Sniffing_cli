#include "handler.h"
#include "file.h"
#include "sniffing.h"
#include "utility.h"
#include "parser.h"
#include "canid.h"

void can_id_str(int id, char* log)
{
    switch(id)
    {
        case ID_ENGINE_RPM : 
            snprintf(log, sizeof(log), "%s", "RPM");
            break;
        default : 
            snprintf(log, sizeof(log), "%#05X", id);
            break;
    }
}

void can_dlc_str(int dlc, char* log)
{
    snprintf(log, sizeof(log), "%d", dlc);
}

//단순 로그 출력1
void prt_log_console(char* log)
{
    char date_buf[MAX_LOG_LENGTH];

    fflush(stdout);
    get_current_day(date_buf);

    printf("%s -> %s\n", date_buf, log);
}

//단순 로그 출력2
void prt_log_console_handler(int id, int dlc, char* data)
{
    char buf[MAX_LOG_LENGTH]; //최종 출력용 버퍼

    //CAN통신용 로그 버퍼
    char date_log[MAX_LOG_LENGTH];
    char id_log[MAX_LOG_LENGTH];
    char dlc_log[MAX_LOG_LENGTH];

    fflush(stdout);

    get_current_day(date_log);

    can_id_str(id, id_log);
    can_dlc_str(dlc, dlc_log);

    snprintf(buf, MAX_LOG_LENGTH, "%s -> id:%s dlc: %s data:%s\n", date_log, id_log, dlc_log, data);
    printf("\r%s", buf);
}

void precess_exit_handler(int sig)
{
    if(sig == SIGINT)
    {
        printf("\r프로세스을 종료합니다.");
        
        all_exit_files();
        all_disconnect_serialport();
        
        exit(sig);
    }
}