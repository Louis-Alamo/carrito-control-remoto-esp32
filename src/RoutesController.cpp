#include "RoutesController.h"
#include <SPIFFS.h>
#include <Arduino.h>

// El controlador recibe el servidor Y el servicio
void RoutesController::setup(AsyncWebServer &server, CarritoService &service)
{

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    // --- RUTAS API ---

    server.on("/adelante", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        service.procesarAdelante(); // Delegamos al servicio
        request->send(200, "text/plain", "OK"); });

    server.on("/atras", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        service.procesarAtras();
        request->send(200, "text/plain", "OK"); });

    server.on("/izquierda", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        service.procesarIzquierda();
        request->send(200, "text/plain", "OK"); });

    server.on("/derecha", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        service.procesarDerecha();
        request->send(200, "text/plain", "OK"); });

    // Agregar una ruta para detener si quieres un botón de STOP explícito
    server.on("/detener", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        service.procesarDetener();
        request->send(200, "text/plain", "OK"); });

    // Nuevo endpoint: Control diferencial con parámetros
    // Ejemplo: /control?v=255&g=120
    // v = velocidad adelante (-255 a 255)
    // g = ajuste giro (-255 a 255)
    server.on("/control", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        int velocidad = 0;
        int giro = 0;
        
        if (request->hasParam("v")) {
            velocidad = request->getParam("v")->value().toInt();
        }
        if (request->hasParam("g")) {
            giro = request->getParam("g")->value().toInt();
        }
        
        service.setVelocidadAdelante(velocidad);
        service.setAjusteGiro(giro);
        
        Serial.print("Control diferencial - Vel: ");
        Serial.print(velocidad);
        Serial.print(" Giro: ");
        Serial.println(giro);
        
        request->send(200, "text/plain", "OK"); });

    // --- DIRECCIONALES ---
    server.on("/direccional/izquierda", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        service.toggleDireccionalIzquierda();
        request->send(200, "text/plain", "OK"); });

    server.on("/direccional/derecha", HTTP_GET, [&service](AsyncWebServerRequest *request)
              {
        service.toggleDireccionalDerecha();
        request->send(200, "text/plain", "OK"); });
}