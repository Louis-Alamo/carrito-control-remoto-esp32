#pragma once

// ==========================================
// MAPEO DE PINES (Configuración Definitiva)
// ==========================================

// --- TIERRA COMÚN ---

// --- LADO IZQUIERDO (Motor A) ---
// Pines ubicados generalmente en un lado del ESP32
#define PIN_MOTOR_A_ENA 25 // Acelerador (Control de Velocidad PWM)
#define PIN_MOTOR_A_IN1 26 // Dirección 1
#define PIN_MOTOR_A_IN2 27 // Dirección 2

// --- LADO DERECHO (Motor B) ---
// Pines ubicados generalmente al otro lado/abajo
#define PIN_MOTOR_B_ENB 14 // Acelerador (Control de Velocidad PWM)
#define PIN_MOTOR_B_IN3 12 // Dirección 1
#define PIN_MOTOR_B_IN4 13 // Dirección 2
