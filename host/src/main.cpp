#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#include "bootstrap.h"

int main(void)
{
    GetEsp32PortName();
    return 0;
}