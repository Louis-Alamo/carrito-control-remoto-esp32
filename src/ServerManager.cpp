#include "ServerManager.h"
#include <SPIFFS.h>  // ¡Importante! Necesita la "bodega"
#include <Arduino.h> // Para Serial.println

// --- El Constructor ---
// Aquí le decimos que el "horno" (servidor) que posee
// debe funcionar en el puerto 80
ServerManager::ServerManager() : server(80)
{
    // El ": server(80)" es la forma C++ de inicializar
    // la variable 'server' de nuestra clase.
}

// --- La Función de Arranque ---
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

    // 2. Preparar el "mostrador" (Ruta Estática)
    // Esta es la única responsabilidad de este servidor:
    // "Cualquier pedido, búscalo en SPIFFS.
    //  Si piden la raíz '/', dales 'index.html'"
    server.serveStatic("/", SPIFFS, "/")
        .setDefaultFile("index.html");

    // 3. Abrir el "restaurante" (Iniciar el servidor)
    server.begin();
    Serial.println("Servidor web (Jefe de Cocina) iniciado.");
    Serial.println("Sirviendo página estática en la raíz /");
}