#ifndef PORTAL_H
#define PORTAL_H

#include "Flecha.h"

class Portal
{
private:
    float entradaX;
    float entradaY;
    float salidaX;
    float salidaY;
    float radio;

public:
    Portal();
    Portal(float ex, float ey, float sx, float sy, float r);

    bool detectarFlecha(Flecha* f);
    void teletransportar(Flecha* f);

    float getEntradaX();
    float getEntradaY();
};

#endif
