#include "Carrito.h"
#include "pins.h"
#include <Arduino.h>

Carrito::Carrito() {}

void Carrito::setup()
{
    pinMode(PIN_MOTOR_A_ENA, OUTPUT);
    pinMode(PIN_MOTOR_A_IN1, OUTPUT);
    pinMode(PIN_MOTOR_A_IN2, OUTPUT);
    pinMode(PIN_MOTOR_B_ENB, OUTPUT);
    pinMode(PIN_MOTOR_B_IN3, OUTPUT);
    pinMode(PIN_MOTOR_B_IN4, OUTPUT);
    detener();
}

// --- MANIOBRAS CORREGIDAS ---

void Carrito::moverAdelante(int velocidad)
{
    // Lado Izquierdo (Motor A) - ¡CAMBIADO A LÓGICA NORMAL!
    // Si antes iba al revés, ahora esto lo arregla.
    digitalWrite(PIN_MOTOR_A_IN1, HIGH); // <-- CAMBIADO
    digitalWrite(PIN_MOTOR_A_IN2, LOW);  // <-- CAMBIADO
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Lado Derecho (Motor B) - SE QUEDA IGUAL (Funcionaba bien)
    digitalWrite(PIN_MOTOR_B_IN3, HIGH);
    digitalWrite(PIN_MOTOR_B_IN4, LOW);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::moverAtras(int velocidad)
{
    // Lado Izquierdo (Motor A) - ¡CAMBIADO!
    digitalWrite(PIN_MOTOR_A_IN1, LOW);  // <-- CAMBIADO
    digitalWrite(PIN_MOTOR_A_IN2, HIGH); // <-- CAMBIADO
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Lado Derecho (Motor B) - SE QUEDA IGUAL
    digitalWrite(PIN_MOTOR_B_IN3, LOW);
    digitalWrite(PIN_MOTOR_B_IN4, HIGH);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::girarIzquierda(int velocidad)
{
    // Izquierda ATRAS (Usamos la nueva lógica de atrás: LOW/HIGH)
    digitalWrite(PIN_MOTOR_A_IN1, LOW);
    digitalWrite(PIN_MOTOR_A_IN2, HIGH);
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Derecha ADELANTE
    digitalWrite(PIN_MOTOR_B_IN3, HIGH);
    digitalWrite(PIN_MOTOR_B_IN4, LOW);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::girarDerecha(int velocidad)
{
    // Izquierda ADELANTE (Usamos la nueva lógica de adelante: HIGH/LOW)
    digitalWrite(PIN_MOTOR_A_IN1, HIGH);
    digitalWrite(PIN_MOTOR_A_IN2, LOW);
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Derecha ATRAS
    digitalWrite(PIN_MOTOR_B_IN3, LOW);
    digitalWrite(PIN_MOTOR_B_IN4, HIGH);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::detener()
{
    analogWrite(PIN_MOTOR_A_ENA, 0);
    analogWrite(PIN_MOTOR_B_ENB, 0);
    digitalWrite(PIN_MOTOR_A_IN1, LOW);
    digitalWrite(PIN_MOTOR_A_IN2, LOW);
    digitalWrite(PIN_MOTOR_B_IN3, LOW);
    digitalWrite(PIN_MOTOR_B_IN4, LOW);
}

// --- CONTROL DIFERENCIAL ---

void Carrito::setMotorIzquierdo(int velocidad)
{
    // Limitar rango
    velocidad = constrain(velocidad, -255, 255);

    if (velocidad > 0)
    {
        // Adelante
        digitalWrite(PIN_MOTOR_A_IN1, HIGH);
        digitalWrite(PIN_MOTOR_A_IN2, LOW);
        analogWrite(PIN_MOTOR_A_ENA, velocidad);
    }
    else if (velocidad < 0)
    {
        // Atrás
        digitalWrite(PIN_MOTOR_A_IN1, LOW);
        digitalWrite(PIN_MOTOR_A_IN2, HIGH);
        analogWrite(PIN_MOTOR_A_ENA, -velocidad);
    }
    else
    {
        // Detenido
        digitalWrite(PIN_MOTOR_A_IN1, LOW);
        digitalWrite(PIN_MOTOR_A_IN2, LOW);
        analogWrite(PIN_MOTOR_A_ENA, 0);
    }
}

void Carrito::setMotorDerecho(int velocidad)
{
    // Limitar rango
    velocidad = constrain(velocidad, -255, 255);

    if (velocidad > 0)
    {
        // Adelante
        digitalWrite(PIN_MOTOR_B_IN3, HIGH);
        digitalWrite(PIN_MOTOR_B_IN4, LOW);
        analogWrite(PIN_MOTOR_B_ENB, velocidad);
    }
    else if (velocidad < 0)
    {
        // Atrás
        digitalWrite(PIN_MOTOR_B_IN3, LOW);
        digitalWrite(PIN_MOTOR_B_IN4, HIGH);
        analogWrite(PIN_MOTOR_B_ENB, -velocidad);
    }
    else
    {
        // Detenido
        digitalWrite(PIN_MOTOR_B_IN3, LOW);
        digitalWrite(PIN_MOTOR_B_IN4, LOW);
        analogWrite(PIN_MOTOR_B_ENB, 0);
    }
}