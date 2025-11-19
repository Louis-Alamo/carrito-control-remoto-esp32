#pragma once
#include <BluetoothSerial.h>

class BluetoothManager
{
private:
    BluetoothSerial SerialBT;
    const char *deviceName = "Carrito_ESP32";

public:
    BluetoothManager();
    void setup();

    // Leer comando desde Bluetooth
    String readCommand();

    // Verificar si hay datos disponibles
    bool available();

    // Enviar respuesta al dispositivo conectado
    void sendResponse(const String &message);
};
