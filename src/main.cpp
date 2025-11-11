#include <Arduino.h>
#include "WifiManager.h"
#include "ServerManager.h"

WifiManager wifiManager;
ServerManager serverManager;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n--- Iniciando Ladrillos #1, #2 y #3 ---");

  wifiManager.setup();
  serverManager.setup();

  Serial.println("--- Sistema Listo ---");
}

void loop()
{
  // El Dueño se va.
}