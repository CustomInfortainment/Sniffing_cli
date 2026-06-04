#include <stdio.h>
#include "file.h"
#include "sniffing.h"
#include "utility.h"

int main(void)
{
    //데이터 수집 시작
    printf("\033[2J");
    all_init();
    data_recv();

    return 0;
}