#include "Jugador.h"
#include "Medidor.h"
#include <cstring>
#include <cmath>

Jugador::Jugador()
{
    fuerza = 10.0f;
    angulo = 45.0f;

    nombre = new char[8];
    std::strcpy(nombre, "Jugador");
    Medidor::asignarMemoria(8 * sizeof(char));
}

Jugador::Jugador(const Jugador& j)
{
    fuerza = j.fuerza;
    angulo = j.angulo;

    int tam = std::strlen(j.nombre);
    nombre = new char[tam + 1];
    std::strcpy(nombre, j.nombre);
    Medidor::asignarMemoria((tam + 1) * sizeof(char));
}

Jugador::~Jugador()
{
    int tam = std::strlen(nombre) + 1;
    delete[] nombre;
    Medidor::liberarMemoria(tam * sizeof(char));
}

Flecha* Jugador::disparar()
{
    Flecha* f = new Flecha();
    Medidor::asignarMemoria(sizeof(Flecha));

    float rad = angulo * 3.1416f / 180.0f;

    f->setX(0);
    f->setY(0);
    f->setVx(fuerza * std::cos(rad));
    f->setVy(fuerza * std::sin(rad));

    return f;
}

float Jugador::getFuerza()
{
    return fuerza;
}

void Jugador::setFuerza(float valor)
{
    fuerza = valor;
}

float Jugador::getAngulo()
{
    return angulo;
}

void Jugador::setAngulo(float valor)
{
    angulo = valor;
}

char* Jugador::getNombre()
{
    return nombre;
}

void Jugador::setNombre(char* nuevoNombre)
{
    int anterior = std::strlen(nombre) + 1;
    delete[] nombre;
    Medidor::liberarMemoria(anterior * sizeof(char));

    int tam = std::strlen(nuevoNombre);
    nombre = new char[tam + 1];
    std::strcpy(nombre, nuevoNombre);
    Medidor::asignarMemoria((tam + 1) * sizeof(char));
}
