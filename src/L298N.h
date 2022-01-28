#ifndef L298N_H
#define L298N_H

class L298N
{
public:
    int ENA;
    int ENB;
    int IN1;
    int IN2;
    int IN3;
    int IN4;
    void init();
    void forward(int speed);
    void backward(int speed);
    void left(int speed);
    void right(int speed);
    void stop();
};

#endif