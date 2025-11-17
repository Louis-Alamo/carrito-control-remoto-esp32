#include "CarritoService.h"
#include <Arduino.h>

CarritoService::CarritoService(Carrito &carrito) : carrito(carrito)
{
    enMovimiento = false;
    enModoBoost = false;
    estadoActual = PARADO;
}

void CarritoService::setup()
{
    carrito.setup();
}

// --- MÉTODOS DE PROCESAMIENTO ---
// Todos siguen el mismo patrón: Activar movimiento, activar boost, guardar hora.

void CarritoService::procesarAdelante()
{
    enMovimiento = true;
    enModoBoost = true;
    inicioMovimiento = millis();
    estadoActual = ADELANTE;

    Serial.println(">> COMANDO: Adelante (Modo BOOST)");
    carrito.moverAdelante(VEL_BOOST);
}

void CarritoService::procesarAtras()
{
    enMovimiento = true;
    enModoBoost = true;
    inicioMovimiento = millis();
    estadoActual = ATRAS;

    Serial.println(">> COMANDO: Atras (Modo BOOST)");
    carrito.moverAtras(VEL_BOOST);
}

void CarritoService::procesarIzquierda()
{
    enMovimiento = true;
    enModoBoost = true;
    inicioMovimiento = millis();
    estadoActual = IZQ;

    Serial.println(">> COMANDO: Izquierda (Modo BOOST)");
    carrito.girarIzquierda(VEL_BOOST);
}

void CarritoService::procesarDerecha()
{
    enMovimiento = true;
    enModoBoost = true;
    inicioMovimiento = millis();
    estadoActual = DER;

    Serial.println(">> COMANDO: Derecha (Modo BOOST)");
    carrito.girarDerecha(VEL_BOOST);
}

void CarritoService::procesarDetener()
{
    enMovimiento = false;
    enModoBoost = false;
    estadoActual = PARADO;

    Serial.println("|| COMANDO: Detener");
    carrito.detener();
}

// --- EL BUCLE DE CONTROL ---
void CarritoService::loop()
{
    // Solo trabajamos si nos estamos moviendo y seguimos en modo boost
    if (enMovimiento && enModoBoost)
    {

        // Checamos el reloj
        if (millis() - inicioMovimiento > TIEMPO_BOOST)
        {

            // ¡Tiempo cumplido! Bajamos la potencia
            enModoBoost = false;
            Serial.println("vvv CRUCERO: Bajando velocidad para ahorrar energía");

            // Reaplicamos el movimiento actual pero con velocidad CRUCERO
            switch (estadoActual)
            {
            case ADELANTE:
                carrito.moverAdelante(VEL_CRUCERO);
                break;
            case ATRAS:
                carrito.moverAtras(VEL_CRUCERO);
                break;
            case IZQ:
                carrito.girarIzquierda(VEL_CRUCERO);
                break;
            case DER:
                carrito.girarDerecha(VEL_CRUCERO);
                break;
            default:
                break;
            }
        }
    }
}