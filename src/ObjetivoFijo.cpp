#include "ObjetivoFijo.h"

ObjetivoFijo::ObjetivoFijo() : Objetivo()
{
}

ObjetivoFijo::ObjetivoFijo(float posX, float posY, float r)
    : Objetivo(posX, posY, r)
{
}

void ObjetivoFijo::actualizar(float dt)
{
    // Los objetivos fijos no se mueven
}

bool ObjetivoFijo::esMovil()
{
    return false;
}
