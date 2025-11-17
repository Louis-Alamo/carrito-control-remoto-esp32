#pragma once
#include <ESPAsyncWebServer.h> // Necesita saber qué es un "servidor"
#include "CarritoService.h"

class RoutesController
{
public:
    // Su única promesa: una función 'setup'
    // que recibe el "horno" (servidor) para poder cocinar en él.
    void setup(AsyncWebServer &server, CarritoService &service);
};