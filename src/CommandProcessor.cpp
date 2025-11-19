#include "CommandProcessor.h"
#include <Arduino.h>

CommandProcessor::CommandProcessor(CarritoService &service) : service(service)
{
}

bool CommandProcessor::processCommand(const String &command)
{
    // Comandos de movimiento básicos
    if (command == "W" || command == "ADELANTE")
    {
        service.procesarAdelante();
        return true;
    }
    else if (command == "S" || command == "ATRAS")
    {
        service.procesarAtras();
        return true;
    }
    else if (command == "A" || command == "IZQUIERDA")
    {
        service.procesarIzquierda();
        return true;
    }
    else if (command == "D" || command == "DERECHA")
    {
        service.procesarDerecha();
        return true;
    }
    else if (command == "STOP" || command == "DETENER")
    {
        service.procesarDetener();
        return true;
    }
    // Direccionales
    else if (command == "DI" || command == "DIR_IZQ")
    {
        service.toggleDireccionalIzquierda();
        return true;
    }
    else if (command == "DD" || command == "DIR_DER")
    {
        service.toggleDireccionalDerecha();
        return true;
    }
    // Control diferencial: formato V<velocidad>G<giro>
    // Ejemplo: V255G-120 (velocidad 255, giro izquierda 120)
    else if (command.startsWith("V") && command.indexOf("G") > 0)
    {
        return processDifferentialCommand(command);
    }

    return false; // Comando no reconocido
}

bool CommandProcessor::processDifferentialCommand(const String &command)
{
    // Parsear formato V<velocidad>G<giro>
    int vIndex = command.indexOf('V');
    int gIndex = command.indexOf('G');

    if (vIndex == -1 || gIndex == -1)
    {
        return false;
    }

    // Extraer valores
    String velStr = command.substring(vIndex + 1, gIndex);
    String giroStr = command.substring(gIndex + 1);

    int velocidad = velStr.toInt();
    int giro = giroStr.toInt();

    // Aplicar control diferencial
    service.setVelocidadAdelante(velocidad);
    service.setAjusteGiro(giro);

    Serial.print("Control diferencial - V:");
    Serial.print(velocidad);
    Serial.print(" G:");
    Serial.println(giro);

    return true;
}
