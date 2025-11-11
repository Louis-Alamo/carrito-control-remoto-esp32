#include "ServerManager.h"
#include <SPIFFS.h>
#include <Arduino.h>

ServerManager::ServerManager() : server(80)
{
    // El constructor sigue igual
}

void ServerManager::setup()
{

    // 1. Abrir la "bodega" (SPIFFS)
    Serial.println("Abriendo bodega (SPIFFS)...");
    if (!SPIFFS.begin(true))
    {
        Serial.println("¡Error al montar SPIFFS!");
        return;
    }
    Serial.println("Bodega montada.");

    // 2. ¡DELEGAR!
    // El Jefe de Cocina le pasa el "horno" (server)
    // a su "Cocinero" (routesController) para que él configure todo.
    Serial.println("Llamando al Cocinero (RoutesController)...");
    routesController.setup(server); // <-- ¡Aquí está la magia!

    // 3. Abrir el "restaurante"
    server.begin();
    Serial.println("Servidor web (Jefe de Cocina) iniciado.");
}