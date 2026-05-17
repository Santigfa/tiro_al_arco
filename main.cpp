#include <iostream>

#include "Jugador.h"
#include "Flecha.h"
#include "Nivel.h"
#include "ObjetivoFijo.h"
#include "ObjetivoMovil.h"
#include "Portal.h"
#include "Medidor.h"

using namespace std;

int main()
{
    cout << "=== Tiro con Arco - Prueba logica ===" << endl;
    cout << endl;

    // --- Nivel 1: objetivos fijos ---
    cout << "Nivel 1: objetivos fijos" << endl;

    Nivel nivel1(1, 2);
    nivel1.agregarObjetivo(0, new ObjetivoFijo(100.0f, 100.0f, 30.0f));
    nivel1.agregarObjetivo(1, new ObjetivoFijo(300.0f, 150.0f, 30.0f));

    Jugador jugador;
    jugador.setAngulo(45.0f);
    jugador.setFuerza(12.0f);

    Flecha* flecha = jugador.disparar();

    for (int i = 0; i < 10; i++)
    {
        flecha->actualizar(0.5f);
        flecha->aplicarGravedad();

        nivel1.actualizar(0.5f, flecha->getX(), flecha->getY());

        if (nivel1.estaCompletado())
        {
            cout << "Nivel 1 completado!" << endl;
            break;
        }
    }

    delete flecha;
    Medidor::liberarMemoria(sizeof(Flecha));

    cout << endl;

    // --- Nivel 2: objetivos moviles y portal ---
    cout << "Nivel 2: objetivos moviles + portal" << endl;

    Nivel nivel2(2, 2);
    nivel2.agregarObjetivo(0, new ObjetivoMovil(400.0f, 200.0f, 30.0f, 60.0f, 200.0f, 700.0f));
    nivel2.agregarObjetivo(1, new ObjetivoMovil(550.0f, 250.0f, 30.0f, 80.0f, 200.0f, 700.0f));
    nivel2.agregarPortal(new Portal(200.0f, 300.0f, 500.0f, 100.0f, 40.0f));

    Flecha* flecha2 = jugador.disparar();

    for (int i = 0; i < 15; i++)
    {
        flecha2->actualizar(0.5f);
        flecha2->aplicarGravedad();

        nivel2.actualizar(0.5f, flecha2->getX(), flecha2->getY());
    }

    delete flecha2;
    Medidor::liberarMemoria(sizeof(Flecha));

    cout << endl;
    Medidor::reportar();

    return 0;
}
