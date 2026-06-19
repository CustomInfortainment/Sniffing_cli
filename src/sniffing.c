#include "sniffing.h"
#include "log.h"
#include "file.h"
#include "parser.h"
#include "utility.h"

int id_count = 0;
int serial_fd = 0;

RingBuffer* ringbuf;

char id_str[4];

void all_init()
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

    //링버퍼 초기화
    ringbuf_init(&ringbuf);
    printf("CAN 통신 시작..\n");
    signal(SIGINT, precess_exit_handler);
}

void all_disconnect_serialport()
{
    close(serial_fd);

    //나중에 지웁시다...
    free(ringbuf);
}

//수집한 데이터를 알아보기 쉽게 수정한다.
void data_save(CANFrame* frame)
{
    char format_data[40];
    FILE* fp = NULL;

    int dst_idx = 0;
    
    for(int i = 0; i < frame->dlc; i++)
    {
        format_data[dst_idx] = frame->raw_data[i * 2];
        format_data[dst_idx + 1] = frame->raw_data[i * 2 + 1];
        format_data[dst_idx + 2] = ' ';

        dst_idx += 3;
    }
    format_data[dst_idx - 1] = '\0';

    fp = get_file(frame->id);

    if(fp != NULL)
    {
        fprintf(fp, "id:%03X DLC:%d, data:%s\n", frame->id, frame->dlc, format_data);
        prt_log_console_handler(frame->id, frame->dlc, format_data);
    }
}

void data_recv()
{
    char buf[256];
    char raw_frame[256];

    int raw_frame_size = 0;

    CANFrame frame;

    while(1)
    {  
        // 256byte 만큼 읽고
        int read_bytes = read(serial_fd, buf, sizeof(buf));

        if (read_bytes <= 0) {
            prt_log_console("데이터 로드 대기 중...");
            usleep(200000);
            continue; // 읽기 실패거나 데이터가 없으면 다시 대기
        }
        
        // 1바이트씩 불러와서 읽음.
        for(int b = 0; b < read_bytes; b++)
        {
            char current_byte = buf[b];

            if (raw_frame_size >= 255) 
            {
                raw_frame_size = 0; 
            }

            if(raw_frame_size == 0 && current_byte != 't')
            {
                raw_frame[0] = '\0';
                raw_frame_size = 0;
                continue;
            }
            raw_frame[raw_frame_size++] = current_byte;

            // 표준 CAN 데이터만 거름. 소문자가 't', frame 배열 완성.
            if(raw_frame[0] == 't' && raw_frame[raw_frame_size - 1] == '\r') 
            {
                memset(&frame, 0, sizeof(CANFrame));
                
                id_str[0] = raw_frame[1];
                id_str[1] = raw_frame[2];
                id_str[2] = raw_frame[3];
                id_str[3] = '\0';

                frame.id = 
                HEX_TO_NUM(raw_frame[1]) << 8 | 
                HEX_TO_NUM(raw_frame[2]) << 4 | 
                HEX_TO_NUM(raw_frame[3]);

                frame.dlc = raw_frame[4] - '0';
                
                //2byte = dlc = 1
                memcpy(frame.raw_data, raw_frame + 5, frame.dlc * 2);

                //버퍼에 저장
                ringbuf_register_data(ringbuf, &frame);

                //파싱한 데이터 출력
                prt_parsing_to_console(frame.id, frame.raw_data);

                raw_frame_size = 0;
                raw_frame[0] = '\0';
            }
        }
        
        //버퍼 데이터 비움
        while(ringbuf_isempty(ringbuf) == 0)
        {
            char ringbuf_frame[256];
            CANFrame frame_buf;

            ringbuf_get_data(ringbuf, &frame_buf);
            data_save(&frame_buf);
        }
    }
}