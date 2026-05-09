#include "BootStrap.h"

HardwareSerial SBCSerial(2);                    //2번 채널 사용

void BootStrap::Init()
{
    //InitEventQueue();
    //InitPinMode();
    //InitTask();
    InitSerial();
}

void BootStrap::InitPinMode()
{
    pinMode(PIN_ACC, INPUT);

    pinMode(PIN_S0, INPUT);
    pinMode(PIN_S3, INPUT);
    pinMode(PIN_S4, INPUT);
}

void BootStrap::InitTask()
{
    
}

void BootStrap::InitEventQueue()
{
    // PowerEventQueue = xQueueCreate(8, sizeof(uint32_t));
    // CanEventQueue = xQueueCreate(8, sizeof(uint32_t));

    // if(PowerEventQueue != NULL) Serial.println("전원 이벤트 큐 생성 완료...");
    // if(CanEventQueue != NULL) Serial.println("CAN 통신 이벤트 큐 생성 완료...");
}

void BootStrap::InitSerial()
{
    Serial.begin(115200);                                       //ESP32 기본 시리얼 번호
    SBCSerial.begin(115200, SERIAL_8N1, PIN_RX2, PIN_TX2);      //ESP32 <-> SBC 간 시리얼 통신
}
