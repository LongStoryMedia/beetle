#ifndef MOTION_H
#define MOTION_H

class Motion
{
private:
    L298N d1;
    L298N d2;
    enum move
    {
        pitch,
        roll,
        yaw
    };

    int priority = move::pitch;
    int speed;

    void setPriority(Packet packet);
    void forward();
    void backward();
    void right();
    void left();
    void clockwise();
    void counterClockWise();

public:
    void init();
    void go(Packet packet);
    void stop();
};

#endif