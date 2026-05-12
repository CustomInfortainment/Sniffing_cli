#include "serial.h"
#include "command.h"

char* getesp32port()
{
    char cmd[256];
    char* buf;

    char* result_pid;
    char* result_vid;

    sprintf(cmd, "grep -r \"%x\" %s", ESP32_PID, PID_PATH);
    buf = send_linux_command(cmd);

    result_pid = strstr(buf, USB_PATH) + strlen(USB_PATH);
    buf = result_pid;
    result_pid[strcspn(buf, "/")] = '\0';

    sprintf(cmd, "grep -r \"%x\" %s", ESP32_VID, VID_PATH);
    buf = send_linux_command(cmd);


}