#include "Objetivo.h"
#include <cmath>

Objetivo::Objetivo()
{
    x = 0;
    y = 0;
    radio = 30.0f;
    golpeado = false;
}

Objetivo::Objetivo(float posX, float posY, float r)
{
    x = posX;
    y = posY;
    radio = r;
    golpeado = false;
}

Objetivo::~Objetivo()
{
}

bool Objetivo::verificarColision(float fx, float fy)
{
    float distancia = std::sqrt((fx - x) * (fx - x) + (fy - y) * (fy - y));
    return distancia <= radio;
}

float Objetivo::getX()
{
    return x;
}

float Objetivo::getY()
{
    return y;
}

bool Objetivo::fueGolpeado()
{
    return golpeado;
}

void Objetivo::marcarGolpeado()
{
    golpeado = true;
}
