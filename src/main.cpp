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

// Control de conexión Bluetooth
bool bluetoothWasConnected = false;
unsigned long ultimaActividad = 0;
const unsigned long TIMEOUT_INACTIVIDAD = 5000; // 5 segundos sin actividad

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
  // Monitorear estado de conexión Bluetooth
  bool conectado = bluetoothManager.isConnected();

  // Detectar nueva conexión
  if (conectado && !bluetoothWasConnected)
  {
    Serial.println("✓ Cliente Bluetooth conectado");
    bluetoothManager.clearBuffer(); // Limpiar buffer al conectar
    ultimaActividad = millis();
  }
  // Detectar desconexión
  else if (!conectado && bluetoothWasConnected)
  {
    Serial.println("✗ Cliente Bluetooth desconectado");
    carritoService.procesarDetener(); // Detener por seguridad
  }

  bluetoothWasConnected = conectado;

  // Comandos Bluetooth (baja latencia)
  String btCommand = bluetoothManager.readCommand();
  if (btCommand.length() > 0)
  {
    ultimaActividad = millis();
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

  // Limpiar buffer si lleva mucho tiempo sin actividad (evita acumulación)
  if (conectado && (millis() - ultimaActividad > TIMEOUT_INACTIVIDAD))
  {
    if (bluetoothManager.available())
    {
      Serial.println("⚠ Limpiando buffer por inactividad");
      bluetoothManager.clearBuffer();
    }
    ultimaActividad = millis();
  }

  // Ciclo de vida del servicio (boost timer, etc.)
  carritoService.loop();

  delay(10); // Pequeño delay para no saturar CPU
}