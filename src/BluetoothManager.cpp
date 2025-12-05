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
        // Leer UN SOLO carácter (sin esperar salto de línea)
        char c = SerialBT.read();

        if (c != '\n' && c != '\r') // Ignorar saltos de línea
        {
            String command = String(c);
            Serial.print("BT >> Comando: ");
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
    if (SerialBT.connected())
    {
        SerialBT.println(message);
    }
}

bool BluetoothManager::isConnected()
{
    return SerialBT.connected();
}

void BluetoothManager::clearBuffer()
{
    // Limpiar cualquier dato acumulado en el buffer
    while (SerialBT.available())
    {
        SerialBT.read();
    }
    Serial.println("Buffer Bluetooth limpiado");
}
