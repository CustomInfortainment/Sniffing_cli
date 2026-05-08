#pragma once

#include <HardwareSerial.h>

#define PIN_ACC 34
#define GATE_SWITCH 25
#define GATE_POWER 26

#define PIN_S0 27
#define PIN_S3 28
#define PIN_S4 29

#define PIN_RX2 17
#define PIN_TX2 16

#define SEND_COMMAND_CNT 5
#define RECV_COMMAND_CNT 6

enum class PowerState
{
    OFF,
    S0,
    S3,
    S4
};

enum class ConnectState
{
    NOT_CONNECTED,
    CONNECTED
};

//커맨드 구조체
struct Command 
{
    const char* commandName;                //명령어 이름
    const char* linuxCommand;               //리눅스 커맨드
};

//SBC 시리얼 통신 객체
extern HardwareSerial SBCSerial;

//송수신 명령어 모음
extern Command sendCommand[];
extern char* recvCommand[];