#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Event.h"
#include "BootStrap.h"

class CThread
{
    public:
        virtual char* GetEventName(Event e) 
        {
            switch(e)
            {
                //-------- 여기서 부터 전원 관련 이벤트 --------------
                case Event::BOOT_ACK:
                    return "BOOT_ACK";
                case Event::BOOT_SEND:
                    return "BOOT_SEND";
                case Event::SHUTDOWN_ACK:
                    return "SHUTDOWN_ACK";
                case Event::SHUTDOWN_SEND:
                    return "SHUTDOWN_SEND";
                case Event::SLEEPING_ACK:
                    return "SLEEPING_ACK";
                case Event::SLEEPING_SEND:
                    return "SLEEPING_SEND";
                case Event::HIVERNATE_ACK:
                    return "HIVERNATE_ACK";
                case Event::HIVERNATE_SEND:
                    return "HIVERNATE_SEND";
                case Event::REBOOT_ACK:
                    return "REBOOT_ACK";
                case Event::REBOOT_SEND:
                    return "REBOOT_SEND";

                //--------- 여기서 부터 CAN 통신 관련 이벤트 --------------
            }
        }
        virtual void RegisterPowerEvent(Event e) 
        {
            Event event = e;
            char consolebuf[50];

            if(xQueueSend(PowerEventQueue, &event, (TickType_t) 10) == pdPASS)
            {
                sprintf(consolebuf, "Event : %s", GetEventName(e));
                Serial.println(consolebuf);
            }
        }
        virtual void RegisterCanEvent(Event e)
        {
            Event event = e;
            char consolebuf[50];

            if(xQueueSend(CanEventQueue, &event, (TickType_t) 10) == pdPASS)
            {
                sprintf(consolebuf, "Event : %s", GetEventName(e));
                Serial.println(consolebuf);
            }
        }
        virtual void OnUpdate() {}
};