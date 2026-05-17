#include "ObjetivoMovil.h"
#include "Medidor.h"
#include <iostream>

using namespace std;

ObjetivoMovil::ObjetivoMovil() : Objetivo()
{
    velocidad = 50.0f;
    direccion = 1.0f;
    limiteIzq = 0.0f;
    limiteDer = 800.0f;
    vecesAcertado = 0;
}

ObjetivoMovil::ObjetivoMovil(float posX, float posY, float r, float vel, float limIzq, float limDer)
    : Objetivo(posX, posY, r)
{
    velocidad = vel;
    direccion = 1.0f;
    limiteIzq = limIzq;
    limiteDer = limDer;
    vecesAcertado = 0;
}

void ObjetivoMovil::percibir()
{
    // El objetivo detecta si llegó a un límite
    if (x >= limiteDer || x <= limiteIzq)
    {
        razonar();
    }
}

void ObjetivoMovil::razonar()
{
    // Decide cambiar la dirección
    direccion *= -1.0f;
}

void ObjetivoMovil::actuar()
{
    // Se mueve en la dirección actual
    x += velocidad * direccion * 0.016f;
}

void ObjetivoMovil::aprender()
{
    // Si fue acertado, aprende a moverse más rápido la próxima vez
    vecesAcertado++;
    if (vecesAcertado > 0)
    {
        velocidad += 10.0f;
    }
    cout << "El objetivo aprendio. Nueva velocidad: " << velocidad << endl;
}

void ObjetivoMovil::actualizar(float dt)
{
    percibir();
    actuar();
    Medidor::incrementarIteracion();
}

bool ObjetivoMovil::esMovil()
{
    return true;
}
