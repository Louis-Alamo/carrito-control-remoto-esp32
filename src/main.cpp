#include <Arduino.h>
#include "WifiManager.h"   // ¡Nuestro Ladrillo #1!
#include "ServerManager.h" // ¡Nuestro Ladrillo #2!

// "Contratamos" a los dos gerentes:
WifiManager wifiManager;
ServerManager serverManager;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n--- Iniciando Ladrillo #1 y #2 ---");

  // El Dueño da las órdenes de arranque:
  wifiManager.setup();   // 1. "Gerente de Sala, abre la cafetería (AP)"
  serverManager.setup(); // 2. "Jefe de Cocina, abre la cocina (Servidor)"

  Serial.println("--- Sistema Listo ---");
  Serial.println("Deberías poder ver la red Y la página web.");
}

void loop()
{
  // El Dueño se va. Los gerentes se quedan trabajando solos.
}