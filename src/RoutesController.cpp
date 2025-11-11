#include "RoutesController.h" // Incluye su propio "contrato"
#include <SPIFFS.h>           // Necesita la "bodega"
#include <Arduino.h>          // Para Serial

void RoutesController::setup(AsyncWebServer &server)
{

    // --- RESPONSABILIDAD #1: Servir la página web ---
    // (Esto antes lo hacía el ServerManager, ahora lo hace el cocinero)
    server.serveStatic("/", SPIFFS, "/")
        .setDefaultFile("index.html");

    // --- RESPONSABILIDAD #2: Atender pedidos (API) ---
    server.on("/adelante", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        Serial.println("¡Comando 'Adelante' recibido!");
        // Aquí irá la lógica para mover el motor
        request->send(200, "text/plain", "OK"); });

    server.on("/atras", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        Serial.println("¡Comando 'Atrás' recibido!");
        request->send(200, "text/plain", "OK"); });

    server.on("/izquierda", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        Serial.println("¡Comando 'Izquierda' recibido!");
        request->send(200, "text/plain", "OK"); });

    server.on("/derecha", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        Serial.println("¡Comando 'Derecha' recibido!");
        request->send(200, "text/plain", "OK"); });

    Serial.println("Cocinero (RoutesController) listo. Todas las rutas configuradas.");
}