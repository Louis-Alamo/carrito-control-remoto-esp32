#include "CarritoService.h"
#include <Arduino.h>

CarritoService::CarritoService(Carrito &carrito, Direccional &direccional)
    : carrito(carrito), direccional(direccional)
{
    velocidadAdelante = 0;
    ajusteGiro = 0;
    enModoBoost = false;
    inicioMovimiento = 0;
}

void CarritoService::setup()
{
    carrito.setup();
    direccional.setup();
}

// --- MÉTODO INTERNO: COMBINA VELOCIDAD Y GIRO ---
void CarritoService::aplicarVelocidades()
{
    // Calcular velocidad base (con boost o crucero)
    int velBase = enModoBoost ? VEL_ADELANTE : VEL_CRUCERO;
    int velGiro = enModoBoost ? VEL_GIRO : VEL_GIRO_CRUCERO;

    // Si no hay movimiento, detener
    if (velocidadAdelante == 0 && ajusteGiro == 0)
    {
        carrito.detener();
        return;
    }

    // Calcular velocidad efectiva (escalar según velocidadAdelante)
    int velocidadEfectiva = (velocidadAdelante * velBase) / 255;

    // Calcular ajuste de giro (escalar según ajusteGiro)
    int ajusteEfectivo = (ajusteGiro * velGiro) / 255;

    // Motor izquierdo = velocidad base - ajuste (girar derecha reduce izq)
    // Motor derecho = velocidad base + ajuste (girar derecha aumenta der)
    int velIzq = velocidadEfectiva - ajusteEfectivo;
    int velDer = velocidadEfectiva + ajusteEfectivo;

    // Aplicar a los motores
    carrito.setMotorIzquierdo(velIzq);
    carrito.setMotorDerecho(velDer);

    Serial.print("Motor Izq: ");
    Serial.print(velIzq);
    Serial.print(" | Motor Der: ");
    Serial.println(velDer);
}

// --- COMANDOS ---

void CarritoService::procesarAdelante()
{
    velocidadAdelante = 255; // Máximo adelante
    enModoBoost = true;
    inicioMovimiento = millis();
    aplicarVelocidades();
    Serial.println(">> COMANDO: Adelante");
}

void CarritoService::procesarAtras()
{
    velocidadAdelante = -255; // Máximo atrás
    enModoBoost = true;
    inicioMovimiento = millis();
    aplicarVelocidades();
    Serial.println(">> COMANDO: Atrás");
}

void CarritoService::procesarIzquierda()
{
    ajusteGiro = -255; // Girar a la izquierda
    if (velocidadAdelante == 0)
    {
        // Giro en sitio
        velocidadAdelante = 128; // Velocidad media para giro
    }
    enModoBoost = true;
    inicioMovimiento = millis();
    aplicarVelocidades();
    Serial.println(">> COMANDO: Izquierda");
}

void CarritoService::procesarDerecha()
{
    ajusteGiro = 255; // Girar a la derecha
    if (velocidadAdelante == 0)
    {
        // Giro en sitio
        velocidadAdelante = 128; // Velocidad media para giro
    }
    enModoBoost = true;
    inicioMovimiento = millis();
    aplicarVelocidades();
    Serial.println(">> COMANDO: Derecha");
}

void CarritoService::procesarDetener()
{
    velocidadAdelante = 0;
    ajusteGiro = 0;
    enModoBoost = false;
    carrito.detener();
    Serial.println("|| COMANDO: Detener");
}

// --- BUCLE DE CONTROL ---
void CarritoService::loop()
{
    // Transición de boost a crucero
    if (enModoBoost && millis() - inicioMovimiento > TIEMPO_BOOST)
    {
        enModoBoost = false;
        Serial.println("vvv CRUCERO: Bajando velocidad");
        aplicarVelocidades(); // Reaplicar con velocidad crucero
    }
}

// --- CONTROL DIFERENCIAL DIRECTO ---

void CarritoService::setVelocidadAdelante(int vel)
{
    velocidadAdelante = constrain(vel, -255, 255);
    enModoBoost = true;
    inicioMovimiento = millis();
    aplicarVelocidades();
}

void CarritoService::setAjusteGiro(int giro)
{
    ajusteGiro = constrain(giro, -255, 255);
    aplicarVelocidades();
}

// --- CONTROL DE DIRECCIONALES ---

void CarritoService::toggleDireccionalIzquierda()
{
    direccional.encenderIzquierda();
}

void CarritoService::toggleDireccionalDerecha()
{
    direccional.encenderDerecha();
}