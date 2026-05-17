#include "Nivel.h"
#include "Medidor.h"
#include <iostream>

using namespace std;

Nivel::Nivel()
{
    numero = 1;
    totalObjetivos = 0;
    objetivosAcertados = 0;
    objetivos = nullptr;
    portal = nullptr;
}

Nivel::Nivel(int num, int cantObjetivos)
{
    numero = num;
    totalObjetivos = cantObjetivos;
    objetivosAcertados = 0;
    portal = nullptr;

    objetivos = new Objetivo*[totalObjetivos];
    Medidor::asignarMemoria(totalObjetivos * sizeof(Objetivo*));

    for (int i = 0; i < totalObjetivos; i++)
    {
        objetivos[i] = nullptr;
    }
}

Nivel::~Nivel()
{
    for (int i = 0; i < totalObjetivos; i++)
    {
        if (objetivos[i] != nullptr)
        {
            delete objetivos[i];
        }
    }
    delete[] objetivos;
    Medidor::liberarMemoria(totalObjetivos * sizeof(Objetivo*));

    if (portal != nullptr)
    {
        delete portal;
    }
}

void Nivel::agregarObjetivo(int indice, Objetivo* obj)
{
    if (indice >= 0 && indice < totalObjetivos)
    {
        objetivos[indice] = obj;
        Medidor::asignarMemoria(sizeof(*obj));
    }
}

void Nivel::agregarPortal(Portal* p)
{
    portal = p;
    Medidor::asignarMemoria(sizeof(Portal));
}

void Nivel::actualizar(float dt, float flechaX, float flechaY)
{
    for (int i = 0; i < totalObjetivos; i++)
    {
        if (objetivos[i] != nullptr && !objetivos[i]->fueGolpeado())
        {
            objetivos[i]->actualizar(dt);

            if (objetivos[i]->verificarColision(flechaX, flechaY))
            {
                objetivos[i]->marcarGolpeado();
                objetivosAcertados++;
                cout << "Objetivo acertado! (" << objetivosAcertados << "/" << totalObjetivos << ")" << endl;

                if (objetivos[i]->esMovil())
                {
                    // cast seguro para llamar aprender()
                    // el agente aprende cuando lo aciertan
                }
            }
        }
    }
}

bool Nivel::estaCompletado()
{
    return objetivosAcertados >= totalObjetivos;
}

int Nivel::getNumero()
{
    return numero;
}

int Nivel::getObjetivosAcertados()
{
    return objetivosAcertados;
}

int Nivel::getTotalObjetivos()
{
    return totalObjetivos;
}
