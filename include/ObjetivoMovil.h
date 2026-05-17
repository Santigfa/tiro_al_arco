#ifndef OBJETIVOMOVIL_H
#define OBJETIVOMOVIL_H

#include "Objetivo.h"

class ObjetivoMovil : public Objetivo
{
private:
    float velocidad;
    float direccion;
    float limiteIzq;
    float limiteDer;
    int vecesAcertado;

public:
    ObjetivoMovil();
    ObjetivoMovil(float x, float y, float radio, float vel, float limIzq, float limDer);

    // Agente inteligente
    void percibir();
    void razonar();
    void actuar();
    void aprender();

    void actualizar(float dt) override;
    bool esMovil() override;
};

#endif
