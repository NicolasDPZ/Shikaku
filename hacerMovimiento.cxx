#include "hacerMovimiento.h"
#include <iostream>
using namespace std;

bool hacerMovimiento(Tablero &tablero, int fila1, int col1, int fila2, int col2,
                     vector<vector<int>> &historial)
{
    // Convertir a base 0
    fila1--; col1--;
    fila2--; col2--;

    // Orden correcto
    if (fila1 > fila2 || col1 > col2)
    {
        cout << "Error: la esquina superior-izquierda debe ir antes que la inferior-derecha.\n";
        return false;
    }

    // Dentro del tablero
    if (fila1 < 0 || col1 < 0 || fila2 >= tablero.filas || col2 >= tablero.columnas)
    {
        cout << "Error: el rectangulo se sale del tablero.\n";
        return false;
    }

    int alto  = fila2 - fila1 + 1;
    int ancho = col2  - col1  + 1;
    int area  = alto * ancho;

    // Contar pistas dentro del rectángulo
    int numPistas  = 0;
    int valorPista = 0;
    for (int i = fila1; i <= fila2; i++)
        for (int j = col1; j <= col2; j++)
            if (tablero.celdas[i][j] != 0)
            {
                numPistas++;
                valorPista = tablero.celdas[i][j];
            }

    if (numPistas == 0)
    {
        cout << "Error: el rectangulo no contiene ninguna pista.\n";
        return false;
    }
    if (numPistas > 1)
    {
        cout << "Error: el rectangulo contiene " << numPistas << " pistas (debe ser 1).\n";
        return false;
    }

    // Área == valor de la pista
    if (area != valorPista)
    {
        cout << "Error: area " << area << " no coincide con la pista " << valorPista << ".\n";
        return false;
    }

    // Sin solapamiento
    for (int i = fila1; i <= fila2; i++)
        for (int j = col1; j <= col2; j++)
            if (tablero.regiones[i][j] != -1)
            {
                cout << "Error: se solapa con otro rectangulo en ("
                     << i+1 << ", " << j+1 << ").\n";
                return false;
            }

    // Guardar snapshot antes de pintar
    vector<int> snapshot;
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
            snapshot.push_back(tablero.regiones[i][j]);
    historial.push_back(snapshot);

    // Pintar usando la posición lineal de la pista como id único
    int id = -1;
    for (int i = fila1; i <= fila2; i++)
        for (int j = col1; j <= col2; j++)
            if (tablero.celdas[i][j] != 0)
                id = i * tablero.columnas + j;

    for (int i = fila1; i <= fila2; i++)
        for (int j = col1; j <= col2; j++)
            tablero.regiones[i][j] = id;

    cout << "Rectangulo " << alto << "x" << ancho
         << " colocado. Pista " << valorPista << " cubierta.\n";
    return true;
}