#include <iostream>

#include "Jugador.h"
#include "Flecha.h"
#include "Medidor.h"

using namespace std;

int main()
{
    Jugador jugador;

    Flecha* flecha = jugador.disparar();

    cout << "Simulacion de disparo" << endl;
    cout << "---------------------" << endl;

    for(int i = 0; i < 5; i++)
    {
        flecha->actualizar(1.0f);
        flecha->aplicarGravedad();

        cout << "Paso " << i + 1 << endl;
        cout << "Posicion X: " << flecha->getX() << endl;
        cout << "Posicion Y: " << flecha->getY() << endl;
        cout << "---------------------" << endl;
    }

    delete flecha;
    Medidor::liberarMemoria(sizeof(Flecha));

    Medidor::reportar();

    return 0;
}
