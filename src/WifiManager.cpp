#include "WifiManager.h" // Incluye su propia definición
#include <WiFi.h>
#include <Arduino.h> // Para poder usar Serial

// Constantes privadas que solo este archivo necesita saber
const char *ap_ssid = "Carrito_ESP32";
const char *ap_password = "password123";

void WifiManager::setup()
{
    Serial.println("Iniciando Punto de Acceso (AP)...");

    // ¡Esta es su única responsabilidad!
    WiFi.softAP(ap_ssid, ap_password);

    Serial.print("AP IP (Conéctate a esta): ");
    Serial.println(WiFi.softAPIP());
}