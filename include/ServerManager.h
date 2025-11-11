#pragma once
#include <ESPAsyncWebServer.h> // ¡Importante! Necesita saber qué es un servidor

class ServerManager
{
private:
    // ¡El Jefe de Cocina es DUEÑO de su "horno" (el servidor)!
    AsyncWebServer server;

public:
    // Constructor: Se usa para inicializar el servidor
    ServerManager();

    // Función de arranque
    void setup();
};