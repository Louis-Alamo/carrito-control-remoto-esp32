#pragma once
#include "Carrito.h"
#include "Direccional.h"

class CarritoService
{
private:
    Carrito &carrito;
    Direccional &direccional;

    // --- PARÁMETROS DE TUNING ---
    const int VEL_ADELANTE = 255;            // Velocidad adelante/atrás
    const int VEL_GIRO = 120;                // Reducción de velocidad al girar
    const int VEL_CRUCERO = 180;             // Velocidad crucero
    const int VEL_GIRO_CRUCERO = 100;        // Velocidad giro en crucero
    const unsigned long TIEMPO_BOOST = 2000; // 2 segundos de boost

    // Estado del control diferencial
    int velocidadAdelante; // -255 a 255 (negativo = atrás)
    int ajusteGiro;        // -255 a 255 (negativo = izq, positivo = der)

    // Control de boost
    unsigned long inicioMovimiento;
    bool enModoBoost;

    // Método interno para aplicar velocidades
    void aplicarVelocidades();

public:
    CarritoService(Carrito &carrito, Direccional &direccional);
    void setup();
    void loop();

    // Comandos de alto nivel
    void procesarAdelante();
    void procesarAtras();
    void procesarIzquierda();
    void procesarDerecha();
    void procesarDetener();

    // Control diferencial directo
    void setVelocidadAdelante(int vel); // -255 a 255
    void setAjusteGiro(int giro);       // -255 a 255

    // Control de direccionales
    void toggleDireccionalIzquierda();
    void toggleDireccionalDerecha();
};