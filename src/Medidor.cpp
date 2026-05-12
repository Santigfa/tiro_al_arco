#include "Medidor.h"
#include <iostream>

using namespace std;

long Medidor::iteraciones = 0;
size_t Medidor::memoriaTotal = 0;

Medidor::Medidor()
{
}

void Medidor::incrementarIteracion()
{
    iteraciones++;
}

void Medidor::asignarMemoria(size_t bytes)
{
    memoriaTotal += bytes;
}

void Medidor::liberarMemoria(size_t bytes)
{
    if (memoriaTotal >= bytes)
    {
        memoriaTotal -= bytes;
    }
}

void Medidor::reportar()
{
    cout << "Metricas del sistema" << endl;
    cout << "Iteraciones: " << iteraciones << endl;
    cout << "Memoria dinamica: " << memoriaTotal << " bytes" << endl;
}
