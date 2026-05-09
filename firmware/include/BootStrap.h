#pragma once
#include "pininfo.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

/* 모듈 초기 실행 시, 초기화를 담당하는 클래스입니다.
1. 모든 초기화 함수는 명시적이여야 합니다.
2. 해당 클래스를 봤을 때, 초기화 순서를 짐작할 수 있어야 합니다.
3. 상수 변수가 아닌 모든 변수를 초기화 합니다.*/

// extern QueueHandle_t PowerEventQueue;
// extern QueueHandle_t CanEventQueue;

class BootStrap
{
    public:
        static void Init();
    private:
        static void InitPinMode();
        static void InitEventQueue();
        static void InitTask();                                     //멀티테스크 초기화
        static void InitSerial();                                   //SBC시리얼 통신 관련 초기화
};