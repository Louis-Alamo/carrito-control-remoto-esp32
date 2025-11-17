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

    // Ojo: En tu JS actual, el "detener" ocurre cuando sueltas el botón
    // (si implementas lógica de 'mouseup') o con otro botón.
    // Por ahora tus botones activan movimiento.
}