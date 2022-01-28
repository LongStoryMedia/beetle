#ifndef RX_H
#define RX_H

typedef struct
{
    int32_t yaw;
    int32_t pitch;
    int32_t roll;
    int32_t thrust;
} Packet;

class Rx
{
private:
    RF24 radio = RF24(CE_PIN, CSN_PIN);
    static const uint8_t radioNumber = 0;
    static const uint8_t controllerRadioNumber = 1;
    static const uint8_t packetSize = sizeof(Packet);
    Packet getRc();
    void initRc();
    void initLora();
    uint32_t rxt;
    Packet packet;

public:
    Packet getPacket();
    void init();
};

#endif