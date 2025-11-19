#include <Arduino.h>
#include "BluetoothManager.h"
#include "CommandProcessor.h"
#include "Carrito.h"
#include "CarritoService.h"
#include "Direccional.h"

// --- INYECCIÓN DE DEPENDENCIAS ---
Carrito carrito;
Direccional direccional;
CarritoService carritoService(carrito, direccional);

// Bluetooth (control de baja latencia)
BluetoothManager bluetoothManager;
CommandProcessor commandProcessor(carritoService);

// Timeout de seguridad
unsigned long ultimoComando = 0;
const unsigned long TIMEOUT_COMANDO = 500; // 500ms sin comando = detener

void setup()
{
  Serial.begin(115200);
  Serial.println("\n--- INICIANDO SISTEMA BLUETOOTH ---");

  // 1. Hardware
  carritoService.setup(); // Configura pines y estado inicial

  // 2. Conectividad Bluetooth
  bluetoothManager.setup(); // Inicia Bluetooth Serial

  Serial.println("--- SISTEMA OPERATIVO ---");
  Serial.println("Bluetooth: Conecta desde tu teléfono al dispositivo 'Carrito_ESP32'");
}

void loop()
{
  // Comandos Bluetooth (baja latencia)
  String btCommand = bluetoothManager.readCommand();
  if (btCommand.length() > 0)
  {
    ultimoComando = millis(); // Actualizar timestamp
    bool success = commandProcessor.processCommand(btCommand);
    if (success)
    {
      bluetoothManager.sendResponse("OK");
    }
    else
    {
      bluetoothManager.sendResponse("ERROR: Comando desconocido");
    }
  }

  // Timeout de seguridad: Si pasan 500ms sin comando, detener
  if (millis() - ultimoComando > TIMEOUT_COMANDO)
  {
    carritoService.procesarDetener();
    ultimoComando = millis(); // Resetear para no llamar detener constantemente
  }

  // Ciclo de vida del servicio (boost timer, etc.)
  carritoService.loop();

  delay(10); // Pequeño delay para no saturar CPU
}