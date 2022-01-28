#include "config.h"
#include "printf.h"

uint8_t address[][6] = {"bird", "nest"};

void Rx::init()
{
    initRc();
}

Packet Rx::getPacket()
{
    return getRc();
}

void Rx::initRc()
{
    // initialize the transceiver on the SPI bus
    radio.begin();
    // radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

    // save on transmission time by setting the radio to only transmit the
    // number of bytes we need to transmit
    radio.setPayloadSize(packetSize); // default value is the maximum 32 bytes

    // set the TX address of the RX node into the TX pipe
    radio.openWritingPipe(address[radioNumber]); // always uses pipe 0

    // set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(controllerRadioNumber, address[controllerRadioNumber]); // using pipe 1

    radio.startListening(); // put radio in RX mode

    // For debugging info
    printf_begin();             // needed only once for printing details
    radio.printDetails();       // (smaller) function that prints raw register values
    radio.printPrettyDetails(); // (larger) function that prints human readable data
    rxt = micros();
}

Packet Rx::getRc()
{
    uint32_t loopTime = micros();
    // radio.flush_rx();

    if (loopTime > rxt + 2500000)
    {
        radio.failureDetected = true;
        packet.pitch = 0;
        packet.roll = 0;
        packet.yaw = 0;
        packet.thrust = 0;
    }

    if (radio.failureDetected)
    {
        radio.failureDetected = false;
        Serial.println(F("Radio failure detected, restarting radio"));
        radio.powerDown();
        delay(250);
        radio.powerUp();
        radio.flush_rx();
        initRc();
    }

    if (radio.available())
    {
        radio.read(&packet, packetSize);
        rxt = loopTime;
    }
    return packet;
}
