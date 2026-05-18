#ifndef SNIFFING_H
#define SNIFFING_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define SERIAL_PORT_PATH "/dev/cu.usbmodem2056369243431"
#define SAVE_DIR_PATH "/Users/choemingyu/Infortainment/esp32-power-sequencer/host/test/sniff/data2"
#define MAX_IDS 2048

typedef struct
{
    int id;
    FILE* fp;
    char filename[256];
} IDFile;

FILE* get_file(int fd);
void all_exit_files();
char* do_sniffing();

#endif