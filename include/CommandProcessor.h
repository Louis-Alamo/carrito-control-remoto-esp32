#pragma once
#include "CarritoService.h"
#include <Arduino.h>

// Procesador de comandos centralizado para WiFi y Bluetooth
class CommandProcessor
{
private:
    CarritoService &service;

public:
    CommandProcessor(CarritoService &service);

    // Procesar comandos de texto (ej: "W", "STOP", "V255G120")
    bool processCommand(const String &command);

    // Procesar comandos de control diferencial (formato: V<vel>G<giro>)
    bool processDifferentialCommand(const String &command);
};
