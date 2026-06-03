#include "borrarMovimiento.h"
#include <iostream>
using namespace std;

bool borrarMovimiento(Tablero &tablero, vector<vector<int>> &historial)
{
    if (historial.empty())
    {
        cout << "No hay movimientos que deshacer.\n";
        return false;
    }

    // Restaurar el último snapshot
    const vector<int> &snapshot = historial.back();
    int k = 0;
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
            tablero.regiones[i][j] = snapshot[k++];

    historial.pop_back();

    cout << "Ultimo movimiento deshecho. ("
         << historial.size() << " movimiento(s) en historial).\n";
    return true;
}