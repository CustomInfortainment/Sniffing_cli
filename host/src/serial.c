#include "serial.h"
#include "command.h"
#include "log.h"

char* getserialport(unsigned int pid, unsigned int vid)
{
    char cmd[256];
    char* buf;

    char* result_pid;
    char* result_vid;

    sprintf(cmd, "grep -r \"%x\" %s", pid, PID_PATH);
    buf = send_linux_command(cmd);

    result_pid = strstr(buf, USB_PATH) + strlen(USB_PATH);
    buf = result_pid;
    result_pid[strcspn(buf, "/")] = '\0';

    sprintf(cmd, "grep -r \"%x\" %s", vid, VID_PATH);
    buf = send_linux_command(cmd);

    result_vid = strstr(buf, USB_PATH) + strlen(USB_PATH);
    buf = result_vid;
    result_vid[strcspn(buf, "/")] = '\0';

    // PID와 VID가 같은 경로에 있으면 포트가 유효함.
    if(strcmp(result_pid, result_vid) == 0)
    {
        sprintf(cmd, "ls %s%s | grep tty", USB_PATH, result_pid);
        buf = send_linux_command(cmd);

        char log[256];

        sprintf(log, "연결된 포트 -> %s", buf);
        prt_logconsole(log);
    }
    return buf;
}