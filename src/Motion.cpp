#include "config.h"

void Motion::init()
{
    d1.ENA = 0;
    d1.ENB = 1;
    d1.IN1 = 17;
    d1.IN2 = 18;
    d1.IN3 = 19;
    d1.IN4 = 20;

    d2.ENA = 2;
    d2.ENB = 3;
    d2.IN1 = 4;
    d2.IN2 = 5;
    d2.IN3 = 6;
    d2.IN4 = 7;

    d1.init();
    d2.init();
}

void Motion::forward()
{
    d1.forward(speed);
    d2.forward(speed);
}

void Motion::backward()
{

    d1.backward(speed);
    d2.backward(speed);
}

void Motion::right()
{

    d1.right(speed);
    d2.right(speed);
}

void Motion::left()
{

    d2.left(speed);
    d1.left(speed);
}

void Motion::clockwise()
{
    d2.backward(speed);
    d1.forward(speed);
}

void Motion::counterClockWise()
{
    d2.forward(speed);
    d1.backward(speed);
}

void Motion::stop()
{
    d1.stop();
    d2.stop();
}

void Motion::go(Packet packet)
{
    setPriority(packet);
    if (speed == 0)
    {
        stop();
        return;
    }
    switch (priority)
    {
    case move::pitch:
        packet.pitch >= 0 ? forward() : backward();
        break;

    case move::roll:
        packet.roll >= 0 ? right() : left();
        break;

    case move::yaw:
        packet.yaw >= 0 ? clockwise() : counterClockWise();
        break;

    default:
        stop();
        break;
    }
}

void Motion::setPriority(Packet packet)
{
    int pitch = abs(packet.pitch);
    int roll = abs(packet.roll);
    int yaw = abs(packet.yaw);

    if (pitch > roll && pitch > yaw)
    {
        priority = move::pitch;
        speed = pitch;
    }
    else if (roll > pitch && roll > yaw)
    {
        priority = move::roll;
        speed = roll;
    }
    else if (yaw > pitch && yaw > roll)
    {
        priority = move::yaw;
        speed = yaw;
    }

    if (speed == 0)
    {
        priority = -1;
        speed = 0;
    }
    else
    {
        speed = map(speed, 0, 500, 175, 300);
    }
}