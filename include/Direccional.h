#pragma once
#include <Arduino.h>

class Direccional
{
private:
    // Estados
    enum Estado
    {
        APAGADO,
        IZQUIERDA,
        DERECHA
    };
    Estado estadoActual;

public:
    Direccional();
    void setup();

    // Control de direccionales
    void encenderIzquierda();
    void encenderDerecha();
    void apagar();

    // Consulta de estado
    bool estaEncendidoIzquierda() const;
    bool estaEncendidoDerecha() const;
};
