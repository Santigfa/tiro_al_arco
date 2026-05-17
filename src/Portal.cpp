#include "Portal.h"
#include <cmath>

Portal::Portal()
{
    entradaX = 200.0f;
    entradaY = 300.0f;
    salidaX = 600.0f;
    salidaY = 100.0f;
    radio = 40.0f;
}

Portal::Portal(float ex, float ey, float sx, float sy, float r)
{
    entradaX = ex;
    entradaY = ey;
    salidaX = sx;
    salidaY = sy;
    radio = r;
}

bool Portal::detectarFlecha(Flecha* f)
{
    float dist = std::sqrt((f->getX() - entradaX) * (f->getX() - entradaX)
                           + (f->getY() - entradaY) * (f->getY() - entradaY));
    return dist <= radio;
}

void Portal::teletransportar(Flecha* f)
{
    f->setX(salidaX);
    f->setY(salidaY);
}

float Portal::getEntradaX()
{
    return entradaX;
}

float Portal::getEntradaY()
{
    return entradaY;
}
