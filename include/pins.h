#pragma once

// --- TIERRA COMÚN ---
// ...

// --- LADO IZQUIERDO (Motor A) ---
#define PIN_MOTOR_A_ENA 25
// ¡INTERCAMBIAMOS ESTOS DOS!
#define PIN_MOTOR_A_IN1 27 // Antes era 26 (Ahora pon 27)
#define PIN_MOTOR_A_IN2 26 // Antes era 27 (Ahora pon 26)

// --- LADO DERECHO (Motor B) ---
// Este déjalo igual, parece que funciona bien
#define PIN_MOTOR_B_ENB 14
#define PIN_MOTOR_B_IN3 12
#define PIN_MOTOR_B_IN4 13

#define PIN_BUZZER 15 // Pin para el buzzer pasivo

// --- DIRECCIONALES (LEDs) ---
#define PIN_LED_IZQ_1 32 // LED izquierdo 1
#define PIN_LED_IZQ_2 33 // LED izquierdo 2
#define PIN_LED_DER_1 4  // LED derecho 1
#define PIN_LED_DER_2 2  // LED derecho 2