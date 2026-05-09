#include <Arduino.h>
#include "BootStrap.h"
#include "SerialWorker.h"

SerialWorker* serialWorker = new SerialWorker();

void setup() 
{
  BootStrap::Init();  //부팅 시 초기화
  delay(100);
}

void loop() 
{
  //serialWorker -> OnUpdate();

  Serial.write(static_cast<uint8_t>(HeartBeat::SENDING));
  Serial.write(static_cast<uint8_t>(HeartBeat::RECVING));

  delay(100);
}