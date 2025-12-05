#include "CommandProcessor.h"
#include <Arduino.h>

CommandProcessor::CommandProcessor(CarritoService &service) : service(service)
{
}

bool CommandProcessor::processCommand(const String &command)
{
    // Comandos de UN SOLO CARÁCTER para mínima latencia
    if (command == "W")
    {
        service.procesarAdelante();
        return true;
    }
    else if (command == "S")
    {
        service.procesarAtras();
        return true;
    }
    else if (command == "A")
    {
        service.procesarIzquierda();
        return true;
    }
    else if (command == "D")
    {
        service.procesarDerecha();
        return true;
    }
    else if (command == "X" || command == " ")
    {
        service.procesarDetener();
        return true;
    }
    else if (command == "I")
    {
        service.toggleDireccionalIzquierda();
        return true;
    }
    else if (command == "J")
    {
        service.toggleDireccionalDerecha();
        return true;
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
