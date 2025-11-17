#include "ServerManager.h"
#include <SPIFFS.h>
#include <Arduino.h>

// 1. Constructor Actualizado
// Usamos la lista de inicialización (: service(service)) para guardar la referencia
ServerManager::ServerManager(CarritoService &service)
    : server(80), service(service)
{
}

void ServerManager::setup()
{
    Serial.println("Abriendo bodega (SPIFFS)...");
    if (!SPIFFS.begin(true))
    {
        Serial.println("¡Error al montar SPIFFS!");
        return;
    }
    Serial.println("Bodega montada.");

    Serial.println("Configurando rutas...");

    // 2. IMPORTANTE: Ahora le pasamos el servicio al cocinero (RoutesController)
    // (Esto requiere que ya hayas arreglado RoutesController como vimos antes)
    routesController.setup(server, service);

    server.begin();
    Serial.println("Servidor web iniciado.");
}