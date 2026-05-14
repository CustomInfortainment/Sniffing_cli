#include "serial.h"
#include "command.h"
#include "log.h"
#include "powercmd.h"

char* getserialport(unsigned int pid, unsigned int vid)
{
    char cmd[256];
    char* buf;

    char* result_pid;
    char* result_vid;

    if(leonardoPortName == NULL)
    {
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
            sprintf(cmd, "ls %s%s/* | grep tty", USB_PATH, result_pid);
            buf = send_linux_command(cmd);

            char log[256];

            sprintf(log, "연결된 포트 -> %s", buf);
            prt_logconsole(log);
        }
        return buf;
    }
    return leonardoPortName;
}

int init()
{
    leonardoPortName = getserialport(LEONARDO_PID, LEONARDO_VID);

    if(leonardoPortName == NULL)
    {
        prt_logconsole("시리얼 포트 불러오기 실패..");
        serialportstate = SERIAL_PORT_OPEN_FAILED;
        return serialportstate;
    }

    leonardoPortFd = open(leonardoPortName, O_RDWR | O_NOCTTY | O_NONBLOCK);

    if(leonardoPortFd < 1)
    {
        prt_logconsole("포트 열기 실패..");
        serialportstate = SERIAL_PORT_OPEN_FAILED;
        return serialportstate;
    }

    if(tcgetattr(leonardoPortFd, &old_ter) != 0)
    {
        prt_logconsole("시리얼 포트 터미널 로드 실패");
        serialportstate = TERMINULL_LOAD_FAILED;
        return serialportstate;
    }
    else
    {
        new_ter = old_ter;

        new_ter.c_cflag &= ~(PARENB | CSTOPB | CRTSCTS);
        new_ter.c_cflag |= (CS8 | CREAD | CLOCAL);

        new_ter.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL | ISIG);

        new_ter.c_iflag &= ~(IXON | IXOFF | IXANY);
        new_ter.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

        new_ter.c_oflag &= ~(OPOST | ONLCR);
        new_ter.c_cc[VTIME] = 15;
        new_ter.c_cc[VMIN] = 1;

        cfsetispeed(&new_ter, B115200);

        if(tcsetattr(leonardoPortFd, TCSANOW, &new_ter) != 0)
        {
            prt_logconsole("시리얼 포트 터미널 설정 실패");
            serialportstate = TERMINULL_SAVE_FAILED;
            return serialportstate;
        }
    }
}

void ping()
{
    
}
