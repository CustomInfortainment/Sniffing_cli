#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ESP32_VID 0x10c4
#define ESP32_PID 0xea60

#define VID_PATH "/sys/bus/usb/devices/*/idVendor"
#define PID_PATH "/sys/bus/usb/devices/*/idProduct"
#define USB_PATH "/sys/bus/usb/devices/"
#define MAX_LINE_CNT 256

void prt_logconsole(char* log)
{
    time_t current;
    time(&current);
    struct tm* t = localtime(&current);

    printf("%02d:%02d:%02d : %s\n", t->tm_hour, t->tm_min, t->tm_sec, log);
}

void* resize_memory(void* ptr, size_t cursize)
{
    void* save = realloc(ptr, cursize * 2);

    if(save == NULL)
    {
        prt_logconsole("메모리 할당에 실패했습니다.");
        return NULL;
    }
    return save;
}

char* send_linux_command(char* cmd)
{
    char* buf = (char*)malloc(MAX_LINE_CNT);
    size_t totalsize = 0;

    FILE* pipe = NULL;
    pipe = popen(cmd, "r");

    if(pipe != NULL)
    {
        while(fgets(buf, MAX_LINE_CNT, pipe) != NULL)
        {
            totalsize += strlen(buf);
            if(totalsize > MAX_LINE_CNT)
            {
                buf = resize_memory(buf, totalsize);

                if(buf == NULL)
                {
                    pclose(pipe);
                    return NULL;
                }
            }
        }
    }
    pclose(pipe);
    return buf;
}

char* getesp32port()
{
    char cmd[256];
    char* buf;

    char* result_pid;

    sprintf(cmd, "grep -r \"%x\" %s", ESP32_PID, PID_PATH);
    buf = send_linux_command(cmd);

    if(buf == NULL) return NULL;

    result_pid = strstr(buf, USB_PATH) + strlen(USB_PATH);
    buf = result_pid;
    result_pid[strcspn(buf, "/")] = '\0';

    prt_logconsole(result_pid);

    return result_pid;
}

int main(void)
{
    getesp32port();

    return 0;
}