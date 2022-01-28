#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#if defined(ESP32)
#include <ESP32Servo.h>
#elif defined(TEENSY)
#include <PWMServo.h>
#define Servo PWMServo
#else
#include <Servo.h>
#endif

#include "L298N.h"
#include "Rx.h"
#include "Motion.h"

void loopRate(int freq);

#endif