#include "serial.h"
#include "command.h"
#include "log.h"

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

int getserialportstate()
{
    int state = INIT_OK;

    if(leonardoPortName == NULL)
    {
        state = SERIAL_PORT_LOAD_FAILED;
        prt_logconsole("시리얼 포트 불러오기 실패..");
        serialportstate = state;
        return state;
    }
    if(leonardoPortFd < 1)
    {
        prt_logconsole("포트 열기 실패..");
        state = SERIAL_PORT_OPEN_FAILED;
        serialportstate = state;
        return state;
    }
}

int startserial()
{
    leonardoPortName = getserialport(LEONARDO_PID, LEONARDO_VID);

    if(getserialportstate() != 0)
    {
        return;
    }

    leonardoPortFd = open(leonardoPortName, O_RDWR | O_NOCTTY | O_NONBLOCK);

    if(getserialportstate() != 0)
    {
        return;
    }

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

    if(tcgetattr(leonardoPortFd, &old_ter) != 0)
    {
        prt_logconsole("시리얼 포트 터미널 로드 실패");
        serialportstate = SERIAL_PORT_LOAD_FAILED;
        return serialportstate;
    }
    if(tcsetattr(leonardoPortFd, TCSANOW, &new_ter) != 0)
    {
        prt_logconsole("시리얼 포트 터미널 설정 실패");
        serialportstate = TERMINULL_SAVE_FAILED;
        return serialportstate;
    }
    serialportstate = INIT_OK;
    return serialportstate;
}

uint8_t senddata(uint8_t data)
{
    char logbuf[256];
    uint8_t sig = 0;

    memset(logbuf, 0, sizeof(logbuf));

    if(leonardoPortFd < 1)
    {
        prt_logconsole("포트 열기 실패..");
        serialportstate = SERIAL_PORT_OPEN_FAILED;
        return serialportstate;
    }
    if(leonardoPortName == NULL)
    {
        prt_logconsole("시리얼 포트 불러오기 실패..");
        serialportstate = SERIAL_PORT_LOAD_FAILED;
        return serialportstate;
    }

    sig = data;
    
    if(write(leonardoPortFd, &sig, 1) > 0)
    {
        sprintf(logbuf, "명령 실행 완료, 응답 보내는 중...%d", sig);
    }
    return sig;
}

uint8_t recvdata()
{
    uint8_t cmd = 0;
    char logbuf[256];

    memset(logbuf, 0, sizeof(logbuf));

    if(serialportstate == INIT_OK)
    {
        if(read(leonardoPortFd, &cmd, 1) > 0)
        {
            sprintf(logbuf, "현재 받은 명령 -> %s", getpowercmdtostr(cmd));
            prt_logconsole(logbuf);

            send_linux_command(getpowercmdtolinux(cmd));

            memset(&logbuf, 0, sizeof(logbuf));
            sprintf(logbuf, "명령 프로세스 종료 -> %d", process_exit_code);

            if(process_exit_code != 0)
            {
                prt_logconsole("프로세스 진행 오류 발생!");
                senddata(ACK_FAIL);
            }
            else
            {
                senddata(ACK_OK);
            }
        }
    }
    return cmd;
}

int endserial()
{
    close(leonardoPortFd);
}
