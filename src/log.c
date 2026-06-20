#include "log.h"
#include "file.h"
#include "sniffing.h"
#include "utility.h"
#include "parser.h"
#include "canid.h"

void can_id_str(int id, char* data, char* outlog)
{
    switch(id)
    {
        case ID_ENGINE_RPM : 
            snprintf(outlog, MAX_LOG_LENGTH, "id:%s data:%d", "ID_ENGINE_RPM", get_rpm_data(id, data));
            break;
        case ID_COOLENT_TEMP:
            snprintf(outlog, MAX_LOG_LENGTH, "id:%s data:%d", "ID_COOLENT_TEMP", get_coolent_data(id, data));
            break;
        default : 
            snprintf(outlog, MAX_LOG_LENGTH, "%#05X", id); //기본 id값을 16진수로 출력한다.
            break;
    }
}

void can_dlc_str(int dlc, char* log)
{
    snprintf(log, MAX_LOG_LENGTH, "%d", dlc);
}

//단순 로그 출력1
void prt_log_console(char* log)
{
    char date_buf[MAX_LOG_LENGTH];
    get_current_time(date_buf);

    printf("%s -> %s\n", date_buf, log);
}

//단순 로그 출력2, 실시간 파싱되지 않은 데이터 출력용.
void prt_log_console_handler(int id, int dlc, char* data)
{
    char buf[MAX_LOG_LENGTH]; //최종 출력용 버퍼

    //CAN통신용 로그 버퍼
    char date_log[MAX_LOG_LENGTH];
    char id_log[MAX_LOG_LENGTH];
    char dlc_log[MAX_LOG_LENGTH];

    get_current_time(date_log);

    can_id_str(id, data, id_log);
    can_dlc_str(dlc, dlc_log);

    //snprintf(buf, MAX_LOG_LENGTH, "%s -> id:%s dlc: %s data:%s\n", date_log, id_log, dlc_log, data);
    //printf("\r%s", buf);
}

//파싱된 데이터 출력용
void prt_parsing_to_console(int id, char* data)
{
    char buf[MAX_LOG_LENGTH];
    char date_log[MAX_LOG_LENGTH];
    char data_log[MAX_LOG_LENGTH];

    can_id_str(id, data, data_log);
    get_current_time(date_log);

    snprintf(buf, MAX_LOG_LENGTH, "%s -> %s\n", date_log, data_log);

    //파싱 되지 않은 데이터는 거른다.
    if(strstr(buf, "0x") != NULL || strstr(buf, "0X") != NULL)
        return;

    static int current_rpm;
    static int current_temp;

    current_rpm = get_rpm_data(id, data);
    current_temp = get_coolent_data(id, data);
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
