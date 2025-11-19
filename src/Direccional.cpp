#include "Direccional.h"
#include "pins.h"
#include <Arduino.h>

Direccional::Direccional()
{
    estadoActual = APAGADO;
}

void Direccional::setup()
{
    // Configurar todos los pines como salida
    pinMode(PIN_LED_IZQ_1, OUTPUT);
    pinMode(PIN_LED_IZQ_2, OUTPUT);
    pinMode(PIN_LED_DER_1, OUTPUT);
    pinMode(PIN_LED_DER_2, OUTPUT);

    // Apagar todo al inicio
    apagar();
}

void Direccional::encenderIzquierda()
{
    // Si ya está encendida la izquierda, apagarla (toggle)
    if (estadoActual == IZQUIERDA)
    {
        apagar();
        Serial.println("<< Direccional izquierda: APAGADA");
        return;
    }

    // Apagar derecha (si estaba encendida)
    digitalWrite(PIN_LED_DER_1, LOW);
    digitalWrite(PIN_LED_DER_2, LOW);

    // Encender izquierda
    digitalWrite(PIN_LED_IZQ_1, HIGH);
    digitalWrite(PIN_LED_IZQ_2, HIGH);

    estadoActual = IZQUIERDA;
    Serial.println("<< Direccional izquierda: ENCENDIDA");
}

void Direccional::encenderDerecha()
{
    // Si ya está encendida la derecha, apagarla (toggle)
    if (estadoActual == DERECHA)
    {
        apagar();
        Serial.println(">> Direccional derecha: APAGADA");
        return;
    }

    // Apagar izquierda (si estaba encendida)
    digitalWrite(PIN_LED_IZQ_1, LOW);
    digitalWrite(PIN_LED_IZQ_2, LOW);

    // Encender derecha
    digitalWrite(PIN_LED_DER_1, HIGH);
    digitalWrite(PIN_LED_DER_2, HIGH);

    estadoActual = DERECHA;
    Serial.println(">> Direccional derecha: ENCENDIDA");
}

void Direccional::apagar()
{
    digitalWrite(PIN_LED_IZQ_1, LOW);
    digitalWrite(PIN_LED_IZQ_2, LOW);
    digitalWrite(PIN_LED_DER_1, LOW);
    digitalWrite(PIN_LED_DER_2, LOW);

    estadoActual = APAGADO;
}

bool Direccional::estaEncendidoIzquierda() const
{
    return estadoActual == IZQUIERDA;
}

bool Direccional::estaEncendidoDerecha() const
{
    return estadoActual == DERECHA;
}