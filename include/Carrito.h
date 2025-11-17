#pragma once
#include <Arduino.h>

class Carrito
{
public:
    // Constructor
    Carrito();

    // Configuración inicial
    void setup();

    // --- Métodos de Maniobra (con velocidad) ---
    // Aceptan un valor de 0 a 255 para controlar la potencia
    void moverAdelante(int velocidad);
    void moverAtras(int velocidad);
    void girarIzquierda(int velocidad);
    void girarDerecha(int velocidad);
    void detener();
};