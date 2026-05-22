#ifndef FILE_H
#define FILE_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define SAVE_PATH "/Users/choemingyu/Infortainment/esp32-power-sequencer/host/test/sniff/data"

#define MAX_DIR 1024 //최대 폴더 갯수
#define MAX_IDS 2048 //최대 로그 파일 갯수

typedef struct
{
    int id;
    FILE* fp;
    char filename[256];
} IDFile;

int check_dir(char* name);
FILE* check_file(int id);

FILE* get_file(int fd);
void save_file();
void all_exit_files();

#endif