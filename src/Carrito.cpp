#include "Carrito.h"
#include "pins.h" // Importamos el mapa de pines

Carrito::Carrito() {}

void Carrito::setup()
{
    // Configuramos todos los pines como SALIDA
    pinMode(PIN_MOTOR_A_ENA, OUTPUT);
    pinMode(PIN_MOTOR_A_IN1, OUTPUT);
    pinMode(PIN_MOTOR_A_IN2, OUTPUT);
    pinMode(PIN_MOTOR_B_ENB, OUTPUT);
    pinMode(PIN_MOTOR_B_IN3, OUTPUT);
    pinMode(PIN_MOTOR_B_IN4, OUTPUT);

    // Estado inicial: Todo detenido
    detener();
}

// --- MANIOBRAS ---

void Carrito::moverAdelante(int velocidad)
{
    // Lado Izquierdo (Motor A) - LÓGICA INVERTIDA (LOW/HIGH = Adelante)
    digitalWrite(PIN_MOTOR_A_IN1, LOW);
    digitalWrite(PIN_MOTOR_A_IN2, HIGH);
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Lado Derecho (Motor B) - LÓGICA NORMAL (HIGH/LOW = Adelante)
    digitalWrite(PIN_MOTOR_B_IN3, HIGH);
    digitalWrite(PIN_MOTOR_B_IN4, LOW);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::moverAtras(int velocidad)
{
    // Lado Izquierdo (Motor A) - INVERTIDO (HIGH/LOW = Atras)
    digitalWrite(PIN_MOTOR_A_IN1, HIGH);
    digitalWrite(PIN_MOTOR_A_IN2, LOW);
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Lado Derecho (Motor B) - NORMAL (LOW/HIGH = Atras)
    digitalWrite(PIN_MOTOR_B_IN3, LOW);
    digitalWrite(PIN_MOTOR_B_IN4, HIGH);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::girarIzquierda(int velocidad)
{
    // Giro tipo tanque: Izq ATRAS, Der ADELANTE

    // Izq Atras (Invertido: HIGH/LOW)
    digitalWrite(PIN_MOTOR_A_IN1, HIGH);
    digitalWrite(PIN_MOTOR_A_IN2, LOW);
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Der Adelante (Normal: HIGH/LOW)
    digitalWrite(PIN_MOTOR_B_IN3, HIGH);
    digitalWrite(PIN_MOTOR_B_IN4, LOW);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::girarDerecha(int velocidad)
{
    // Giro tipo tanque: Izq ADELANTE, Der ATRAS

    // Izq Adelante (Invertido: LOW/HIGH)
    digitalWrite(PIN_MOTOR_A_IN1, LOW);
    digitalWrite(PIN_MOTOR_A_IN2, HIGH);
    analogWrite(PIN_MOTOR_A_ENA, velocidad);

    // Der Atras (Normal: LOW/HIGH)
    digitalWrite(PIN_MOTOR_B_IN3, LOW);
    digitalWrite(PIN_MOTOR_B_IN4, HIGH);
    analogWrite(PIN_MOTOR_B_ENB, velocidad);
}

void Carrito::detener()
{
    // Acelerador a 0
    analogWrite(PIN_MOTOR_A_ENA, 0);
    analogWrite(PIN_MOTOR_B_ENB, 0);

    // Apagar dirección por seguridad
    digitalWrite(PIN_MOTOR_A_IN1, LOW);
    digitalWrite(PIN_MOTOR_A_IN2, LOW);
    digitalWrite(PIN_MOTOR_B_IN3, LOW);
    digitalWrite(PIN_MOTOR_B_IN4, LOW);
}