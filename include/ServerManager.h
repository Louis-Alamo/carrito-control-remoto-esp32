#pragma once
#include <ESPAsyncWebServer.h>
#include "RoutesController.h"
#include "CarritoService.h" // <--- 1. IMPORTANTE: Incluir esto

class ServerManager
{
private:
    AsyncWebServer server;
    RoutesController routesController;

    // 2. IMPORTANTE: Variable para guardar al Gerente
    CarritoService &service;

public:
    // 3. IMPORTANTE: El constructor ahora pide el servicio
    ServerManager(CarritoService &service);

    void setup();
};