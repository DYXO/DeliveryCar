#include "serial.h"


SerialPort::SerialPort()
{
    if (!gpioInitialise()) 
    {
        printf("erro!gpio_init failed!\n");
    }
    gpioSetMode(rxPin, PI_INPUT);
    gpioSetMode(txPin, PI_OUTPUT);
    if (gpioSerialReadOpen(rxPin, baudRate, 8) < 0) 
    {
        printf("read open failed!\n");
    }
}

SerialPort::~SerialPort() {
    gpioSerialReadClose(rxPin);
    gpioTerminate();
}

void SerialPort::send(const std::string& data) {
    gpioWaveClear();
    char* charData = const_cast<char*>(data.c_str());
    gpioWaveAddSerial(txPin, baudRate, 8, 2, 0, data.size(), charData);
    //gpioWaveAddSerial(txPin, baudRate, 8, -1, 0,data.size(), reinterpret_cast<const unsigned char*>(data.c_str()));
    int waveId = gpioWaveCreate();
    if (waveId >= 0) {
        gpioWaveTxSend(waveId, PI_WAVE_MODE_ONE_SHOT);
        while (gpioWaveTxBusy()) {
            time_sleep(0.1);
        }
        gpioWaveDelete(waveId);
    }
}
std::string SerialPort::receive() {
    char buf[256];
    int bytesRead = gpioSerialRead(rxPin, buf, sizeof(buf));
    return std::string(buf, bytesRead);
}
