#ifndef SERIAL_H
#define SERIAL_H

#include <string>
#include <stdio.h>
#include <pigpio.h>
#include <stdexcept>
#include <iostream>

class SerialPort {
public:
    SerialPort();
    ~SerialPort();
    void send(const std::string& data);
    std::string receive();

private:
    int rxPin = 15;
    int txPin = 14;
    int baudRate = 9600;
};

#endif
