#ifndef OBJETIVOFIJO_H
#define OBJETIVOFIJO_H

#include "Objetivo.h"

class ObjetivoFijo : public Objetivo
{
public:
    ObjetivoFijo();
    ObjetivoFijo(float x, float y, float radio);

    void actualizar(float dt) override;
    bool esMovil() override;
};

#endif
