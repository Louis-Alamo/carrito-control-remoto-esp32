#include <Arduino.h>
#include "WifiManager.h"
#include "ServerManager.h"
#include "Carrito.h"
#include "CarritoService.h"

// --- INYECCIÓN DE DEPENDENCIAS ---
Carrito carrito;
CarritoService carritoService(carrito);
WifiManager wifiManager;
// ServerManager necesita el servicio para pasárselo al RoutesController
ServerManager serverManager(carritoService);

void setup()
{
  Serial.begin(115200);
  Serial.println("\n--- INICIANDO SISTEMA ---");

  // 1. Hardware
  carritoService.setup(); // Configura pines y estado inicial

  // 2. Conectividad
  wifiManager.setup();   // Crea el AP
  serverManager.setup(); // Inicia servidor y rutas

  Serial.println("--- SISTEMA OPERATIVO ---");
}

void loop()
{
  // El ciclo de vida del servicio debe correr siempre
  // para controlar el temporizador del modo Boost
  carritoService.loop();

  // (Opcional) Un pequeño delay para no saturar la CPU innecesariamente,
  // aunque el ESP32 lo maneja bien.
  delay(10);
}