#pragma once
#include <ESPAsyncWebServer.h>
#include "RoutesController.h" // <-- ¡Ahora conoce el "contrato" del Cocinero!

class ServerManager
{
private:
    AsyncWebServer server;
    RoutesController routesController; // <-- ¡El Jefe de Cocina TIENE UN Cocinero!

public:
    ServerManager();
    void setup();
};