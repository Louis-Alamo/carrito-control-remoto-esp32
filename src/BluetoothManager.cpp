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
    if (!SerialBT.available())
    {
        return "";
    }

    char c = SerialBT.read();

    if (c == '\n')
    {
        // Fin de comando multi-carácter
        if (commandBuffer.length() > 0)
        {
            String cmd = commandBuffer;
            commandBuffer = "";
            Serial.print("BT >> Comando: ");
            Serial.println(cmd);
            return cmd;
        }
        return "";
    }

    if (c == '\r')
    {
        return ""; // Ignorar retorno de carro
    }

    // Protección contra desbordamiento de buffer
    if (commandBuffer.length() >= 32)
    {
        Serial.println("⚠ Buffer overflow: limpiando");
        commandBuffer = "";
        return "";
    }

    commandBuffer += c;

    // Devolver inmediatamente los comandos de un solo carácter conocidos
    // para mantener la baja latencia. Los comandos multi-carácter (ej. V255G0)
    // esperan el salto de línea '\n'.
    if (commandBuffer.length() == 1 &&
        (c == 'W' || c == 'S' || c == 'A' || c == 'D' ||
         c == 'X' || c == ' ' || c == 'I' || c == 'J'))
    {
        String cmd = commandBuffer;
        commandBuffer = "";
        Serial.print("BT >> Comando: ");
        Serial.println(cmd);
        return cmd;
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
    // Limpiar cualquier dato acumulado en el buffer serial y en el buffer interno
    while (SerialBT.available())
    {
        SerialBT.read();
    }
    commandBuffer = "";
    Serial.println("Buffer Bluetooth limpiado");
}
