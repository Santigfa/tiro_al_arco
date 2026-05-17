#ifndef NIVEL_H
#define NIVEL_H

#include "Objetivo.h"
#include "Portal.h"

class Nivel
{
private:
    int numero;
    int totalObjetivos;
    int objetivosAcertados;
    Objetivo** objetivos;
    Portal* portal;

public:
    Nivel();
    Nivel(int num, int cantObjetivos);
    ~Nivel();

    void agregarObjetivo(int indice, Objetivo* obj);
    void agregarPortal(Portal* p);

    void actualizar(float dt, float flechaX, float flechaY);
    bool estaCompletado();

    int getNumero();
    int getObjetivosAcertados();
    int getTotalObjetivos();
};

#endif
