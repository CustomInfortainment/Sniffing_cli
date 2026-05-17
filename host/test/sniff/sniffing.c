#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define MAX_IDS 2048  //최대 로그 저장 카운트

#define LOG_PATH "/Users/choemingyu/can_logs"

typedef struct
{
    int id;
    FILE* fp;
    char filename[256];
} IDFile;

IDFile id_files[MAX_IDS];
int id_count = 0;

FILE* get_file(int id)
{
    if(id_count >= MAX_IDS)
    {
        perror("배열 범위 초과");
        return NULL;
    }

    for(int i = 0; i < id_count; i++)
    {
        if(id_files[i].id == id)
        {
            return id_files[i].fp;
        }
    }

    //없으면 파일 생성
    IDFile* entry = &id_files[id_count++];
    entry->id = id;

    snprintf(entry->filename, sizeof(entry->filename), "%s/can_0x%03X.txt", LOG_PATH, id);
    entry->fp = fopen(entry->filename, "a");

    if(entry->fp == NULL)
    {
        perror("파일 열기 실패");
        return NULL;
    }
    printf("새 ID 발견 : 0x%03X -> %s\n", id, entry->filename);
    fflush(stdout);

    return entry->fp;
}

void close_all_files()
{
    for(int i = 0; i < id_count; i++)
    {
        if(id_files[i].fp != NULL)
        {
            fclose(id_files[i].fp);
        }
    }
}

int main(void)
{
    const char* port = "/dev/cu.usbmodem2056369243431";

    system("mkdir -p /Users/choemingyu/can_logs");

    int fd = open(port, O_RDWR | O_NOCTTY);
    if(fd < 0)
    {
        perror("포트 열기 실패");
        return 1;
    }

    // 시리얼 통신 설정
    struct termios tty;
    tcgetattr(fd, &tty);
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
    tcsetattr(fd, TCSANOW, &tty);

    write(fd, "C\r", 2); //CAN 통신 초기화
    usleep(200000);
    write(fd, "S6\r", 3); //CAN 통신 속도 설정, 500kbps
    usleep(200000);
    write(fd, "O\r", 2);  //데이터 읽어내기
    usleep(200000);

    printf("CAN 통신 시작, 데이터 로드 중...(500kbps)\n\n");

    char frame[256];
    char buf;
    int size = 0;

    while(1)
    {
        read(fd, &buf, 1);
        frame[size++] = buf;

        if(size > 255)
        {
            perror("배열 인덱스 크기 초과");
            return 1;
        }

        if(frame[size - 1] == '\r' && frame[0] == 't') //표준 프레임인지 확인
        {
            char id_str[4] = {frame[1], frame[2], frame[3], '\0'};
            int id = strtol(id_str, NULL, 16); //id값 16진수로 변환
            int dlc = frame[4] - '0'; //char 변환
            char* data = frame + 5; //데이터는 5부터 시작

            FILE *fp = get_file(id);

            if(fp == NULL)
            {
                perror("파일 열기 실패");
                return 1;
            }
            fprintf(fp, "ID:%3X DLC:%d DATA:%s", id, dlc, data);
            fflush(fp);
        }
        size = 0;
    }
    return 0;
}