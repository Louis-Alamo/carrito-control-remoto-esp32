#include <Arduino.h>
#include "WifiManager.h" // ¡Importamos nuestra nueva clase!

// "Contratamos" al gerente, creamos una instancia
WifiManager wifiManager;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n--- Prueba de Ladrillo #1: WifiManager ---");

  // Le damos la orden de empezar
  wifiManager.setup();

  Serial.println("--- Prueba de WiFi terminada ---");
  Serial.println("El AP 'Carrito_ESP32' debería estar visible.");
}

void loop()
{
  // El dueño se va a dormir, el gerente ya hizo su trabajo.
}