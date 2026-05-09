#include "pininfo.h"

/*해당 파일에서는 상수 변수들만 초기화를 진행합니다. (나머지 변수들은 BootStrap에서.)*/

Command sendCommand[4] = {
    {"SHUTDOWN",   "shutdown -h now"},
    {"REBOOT",     "reboot"},
    {"SLEEP",      "systemctl suspend"},
    {"HIBERNATE",  "systemctl hibernate"}
};

char* recvCommand[6] = {
    "WAIT_RESPONSE",
    "BOOT OK",
    "SHUTDOWN OK",
    "REBOOT OK",
    "SLEEP OK",
    "HIBERNATE OK"
};