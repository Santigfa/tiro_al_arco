#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <cstddef>

class Medidor
{
private:
    static long iteraciones;
    static size_t memoriaTotal;

public:
    Medidor();

    static void incrementarIteracion();
    static void asignarMemoria(size_t);
    static void liberarMemoria(size_t);
    static void reportar();
};

#endif
