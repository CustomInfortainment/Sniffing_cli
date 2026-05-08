#pragma once
#include <freertos/FreeRTOS.h>

//SBC에 보내지 않음
enum class Event : uint32_t
{
    NONE,

    SHUTDOWN_SEND,
    SHUTDOWN_ACK,

    BOOT_SEND,               
    BOOT_ACK,

    REBOOT_SEND,
    REBOOT_ACK,
    
    SLEEPING_SEND,
    SLEEPING_ACK,

    HIVERNATE_SEND,
    HIVERNATE_ACK,

    HEARTBEAT_TIMEOUT,
};

//SBC에 직접 보냄
enum class HeartBeat : uint8_t 
{
    RECVING = 0,
    SENDING = 1
};