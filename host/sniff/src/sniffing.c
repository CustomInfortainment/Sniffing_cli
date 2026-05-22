#include "sniffing.h"
#include "handler.h"
#include "file.h"

int id_count = 0;
int serial_fd = 0;

void all_disconnect_serialport()
{
    close(serial_fd);
}

void do_sniffing()
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
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_oflag &= ~OPOST;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 1;
    tcsetattr(serial_fd, TCSANOW, &tty);

    write(serial_fd, "C\r", 2);
    usleep(500000);
    write(serial_fd, "S6\r", 3);
    usleep(500000);
    write(serial_fd, "O\r", 2);
    usleep(500000);

    char frame[256];
    int size = 0;
    char buf[256];

    printf("CAN 통신 시작..\n");

    signal(SIGINT, precess_exit_handler);

    while(1)
    {  
        int read_bytes = read(serial_fd, buf, sizeof(buf));

        if (read_bytes <= 0) {
            prt_log_console("데이터 로드 대기 중...");
            usleep(200000);
            continue; // 읽기 실패거나 데이터가 없으면 다시 대기
        }

        for(int b = 0; b < read_bytes; b++)
        {
            char current_byte = buf[b];

            if (size >= 256) 
            {
                size = 0; 
            }

            if(size == 0 && current_byte != 't')
            {
                frame[0] = '\0';
                size = 0;
                continue;
            }
            frame[size++] = current_byte;

            if(frame[0] == 't' && frame[size - 1] == '\r') 
            {
                char id_str[4] = {frame[1], frame[2], frame[3], '\0'};
                int id = strtol(id_str, NULL, 16);
                int dlc = frame[4] - '0';
                char* data = frame + 5;

                char format_data[40];

                int dst_idx = 0;
                
                for(int i = 0; i < dlc; i++)
                {
                    format_data[dst_idx] = data[i * 2];
                    format_data[dst_idx + 1] = data[i * 2 + 1];
                    format_data[dst_idx + 2] = ' ';

                    dst_idx += 3;
                }
                format_data[dst_idx - 1] = '\0';
                FILE* fp = get_file(id);

                // if(id == DATA_RPM)
                // {
                //     char rpm_ch1[3] = {data[2], data[3], '\0'};
                //     char rpm_ch2[3] = {data[4], data[5], '\0'};
                //     int rpm_data1 = strtol(rpm_ch1, NULL, 16);
                //     int rpm_data2 = strtol(rpm_ch2, NULL, 16);

                //     int rpm_result = (rpm_data1 << 8 | rpm_data2);

                //     //printf("\rrpm : %4d.   ", rpm_result / 4);
                // }
                // fflush(stdout);

                if(fp != NULL)
                {
                    fprintf(fp, "id:%03X DLC:%d, data:%s\n", id, dlc, format_data);
                    prt_log_console_handler(id, dlc, format_data);
                }
                size = 0;
                frame[0] = '\0';
                //tcflush(serial_fd, TCIFLUSH);
            }
        }
    }
}