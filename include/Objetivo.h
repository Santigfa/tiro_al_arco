#ifndef OBJETIVO_H
#define OBJETIVO_H

class Objetivo
{
protected:
    float x;
    float y;
    float radio;
    bool golpeado;

public:
    Objetivo();
    Objetivo(float x, float y, float radio);
    virtual ~Objetivo();

    virtual void actualizar(float dt) = 0;
    virtual bool esMovil() = 0;

    bool verificarColision(float fx, float fy);

    float getX();
    float getY();
    bool fueGolpeado();
    void marcarGolpeado();
};

#endif
