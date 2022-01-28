#include "config.h"

Rx rx;
uint32_t t, loopRateEnd;
Packet packet;
Motion motion;

void setup()
{
  Serial.begin(115200);
  motion.init();
  rx.init();
}

void loop()
{
  t = micros();
  packet = rx.getPacket();
  if (packet.pitch == 0 && packet.roll == 0 && packet.yaw == 0)
  {
    motion.stop();
  }
  else
  {
    motion.go(packet);
  }
  loopRate(2000); // do not exceed 2000Hz, all filter parameters tuned to 2000Hz by default
}

void loopRate(int freq)
{
  float invFreq = 1.0 / freq * 1000000.0;
  uint32_t checker = micros();

  // Sit in loop until appropriate time has passed
  while (invFreq > (checker - t))
  {
    checker = micros();
  }
  loopRateEnd = micros();
}
/*
L298N H-Bridge driving DC motor on Arduino
*/
