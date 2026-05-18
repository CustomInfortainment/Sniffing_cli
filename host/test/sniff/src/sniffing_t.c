#include "sniffing.h"

IDFile files[MAX_IDS];

int id_count = 0;
int serial_fd = 0;

FILE* get_file(int id)
{
    //이미 있는 경우
    for(int i = 0; i < id_count; i++)
    {
        if(files[i].id == id)
        {
            return files[i].fp;
        }
    }

    IDFile* entry = &files[id_count++];
    entry->id = id;

    char buf[256];
    snprintf(buf, sizeof(buf), "mkdir -p %s", SAVE_DIR_PATH);

    if(system(buf) != 0)
    {
        perror("명령 프로세스 실패");
        exit(1);
    }

    memset(buf, '\0', 256);
    snprintf(buf, sizeof(buf), "%s/CAN_%03X.txt", SAVE_DIR_PATH, id);

    entry->fp = fopen(buf, "a");

    return entry->fp;
}

void all_exit_files()
{
    for(int i = 0; i < id_count; i++)
    {
        fclose(files[i].fp);
    }
}

void all_disconnect_serialport()
{
    close(serial_fd);
}

char* do_sniffing()
{
    serial_fd = open(SERIAL_PORT_PATH, O_RDWR | O_NOCTTY);

    if(serial_fd < 0)
    {
        perror("시리얼 포트 열기 실패");
        exit(1);
    }

    struct termios tty;
    tcgetattr(serial_fd, &tty);
    cfsetspeed(&tty, B115200);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 10;
    tcsetattr(serial_fd, TCSANOW, &tty);

    write(serial_fd, "C\r", 2);
    usleep(200000);
    write(serial_fd, "S6\r", 3);
    usleep(200000);
    write(serial_fd, "O\r", 2);
    usleep(200000);

    char frame[256];
    int size = 0;
    char buf;

    while(1)
    {
        read(serial_fd, &buf, 1);
        frame[size++] = buf;

        if(frame[0] == 't' && frame[size - 1] == '\r') //명령 끝 부분
        {
            char id_str[4] = {frame[1], frame[2], frame[3], '\0'};
            int id = strtol(id_str, NULL, 16);
            int dlc = frame[4] - '0';
            char* data = frame + 5;

            char format_data[25];

            int dst_idx = 0;

            for(int i = 0; i < dlc; i++)
            {
                format_data[dst_idx] = data[i * 2];
                format_data[dst_idx + 1] = data[i * 2 + 1];
                format_data[dst_idx + 2] = ' ';

                dst_idx += 3;
            }
            format_data[dst_idx] = '\0';
            FILE* fp = get_file(id);

            if(fp != NULL)
            {
                fprintf(fp, "id:%03X DLC:%d, data:%s", id, dlc, format_data);
            }
            size = 0;
        }
    }
}

int main(void)
{
    return 0;
}