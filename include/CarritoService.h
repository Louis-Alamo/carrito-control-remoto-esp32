#pragma once
#include "Carrito.h"

class CarritoService
{
private:
    Carrito &carrito; // Referencia al técnico

    // --- PARÁMETROS DE TUNING ---
    const int VEL_BOOST = 255;               // 100% Potencia para arrancar
    const int VEL_CRUCERO = 180;             // ~70% Potencia para mantener (ajustable)
    const unsigned long TIEMPO_BOOST = 2000; // 2 segundos de boost

    // Variables de estado
    unsigned long inicioMovimiento;
    bool enModoBoost;
    bool enMovimiento;

    // Enum para saber qué movimiento mantener
    enum EstadoMovimiento
    {
        PARADO,
        ADELANTE,
        ATRAS,
        IZQ,
        DER
    };
    EstadoMovimiento estadoActual;

public:
    CarritoService(Carrito &carrito);
    void setup();

    // Método vital para el temporizador
    void loop();

    // Comandos de alto nivel
    void procesarAdelante();
    void procesarAtras();
    void procesarIzquierda();
    void procesarDerecha();
    void procesarDetener();
};