#include "BluetoothManager.h"
#include <Arduino.h>

BluetoothManager::BluetoothManager()
{
}

void BluetoothManager::setup()
{
    // Inicializar Bluetooth Serial
    if (!SerialBT.begin(deviceName))
    {
        Serial.println("ERROR: No se pudo inicializar Bluetooth");
        return;
    }

    Serial.print("Bluetooth iniciado. Nombre del dispositivo: ");
    Serial.println(deviceName);
    Serial.println("Esperando conexión Bluetooth...");
}

String BluetoothManager::readCommand()
{
    if (SerialBT.available())
    {
        String command = SerialBT.readStringUntil('\n');
        command.trim(); // Eliminar espacios y saltos de línea

        if (command.length() > 0)
        {
            Serial.print("BT >> Comando recibido: ");
            Serial.println(command);
            return command;
        }
    }
    return "";
}

bool BluetoothManager::available()
{
    return SerialBT.available();
}

void BluetoothManager::sendResponse(const String &message)
{
    SerialBT.println(message);
}
