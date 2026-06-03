#include "tablero.h"
#include <map>

bool cargarTablero(const std::string &archivo, Tablero &tablero)
{
    ifstream file(archivo);
    if (!file.is_open())
        return false;
    file >> tablero.filas >> tablero.columnas;
    tablero.celdas.assign(tablero.filas, vector<int>(tablero.columnas, 0));
    tablero.regiones.assign(tablero.filas, vector<int>(tablero.columnas, -1));
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
            file >> tablero.celdas[i][j];
    return true;
}

bool mostrarTablero(const Tablero &tablero)
{
    if (tablero.celdas.empty())
    {
        cout << "No hay tablero cargado.\n";
        return false;
    }

    int anchoFila = to_string(tablero.filas).length();
    string prefijo = string(anchoFila + 6, ' ');

    // Encabezado de columnas
    cout << prefijo;
    for (int j = 0; j < tablero.columnas; j++)
        cout << " C" << left << setw(3) << j + 1;
    cout << "\n";

    // Línea separadora superior
    cout << prefijo;
    for (int j = 0; j < tablero.columnas; j++)
        cout << "+----";
    cout << "+\n";

    // Asignar número de movimiento (1..N) a cada id de región,
    // en el orden en que aparecen al recorrer el tablero de arriba a abajo.
    map<int,int> idAMovimiento;
    int contador = 1;
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
        {
            int r = tablero.regiones[i][j];
            if (r != -1 && idAMovimiento.find(r) == idAMovimiento.end())
                idAMovimiento[r] = contador++;
        }

    // Filas
    for (int i = 0; i < tablero.filas; i++)
    {
        cout << "F" << left << setw(anchoFila) << i + 1 << " -> ";

        for (int j = 0; j < tablero.columnas; j++)
        {
            int val    = tablero.celdas[i][j];
            int region = tablero.regiones[i][j];

            if (val != 0)
            {
                // Celda con pista: mostrar el número sin adornos
                cout << "|*" << left << setw(2) << val << " ";
            }
            else if (region != -1)
            {
                // Celda cubierta: mostrar número de movimiento (1, 2, 3...)
                cout << "| " << left << setw(2) << idAMovimiento[region] << " ";
            }
            else
            {
                // Celda vacía
                cout << "|    ";
            }
        }
        cout << "|\n";

        // Separador
        cout << prefijo;
        for (int j = 0; j < tablero.columnas; j++)
            cout << "+----";
        cout << "+\n";
    }

    return true;
}

bool validarTablero(const Tablero &tablero)
{
    if (tablero.celdas.empty())
    {
        cout << "No hay tablero cargado.\n";
        return false;
    }

    // 1. Verificar que el jugador haya cubierto todo el tablero
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
            if (tablero.regiones[i][j] == -1)
            {
                cout << "Solucion incompleta: la celda F" << i + 1
                     << " C" << j + 1 << " no esta cubierta.\n";
                return false;
            }

    // Recopilar informacion de cada region: celdas que la forman
    // id -> lista de (fila, col)
    map<int, vector<pair<int,int>>> regionCeldas;
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
            regionCeldas[tablero.regiones[i][j]].push_back({i, j});

    for (auto &[id, celdas] : regionCeldas)
    {
        // 2. Cada region debe contener exactamente 1 pista
        int numPistas  = 0;
        int valorPista = 0;
        for (auto [fi, fj] : celdas)
            if (tablero.celdas[fi][fj] != 0)
            {
                numPistas++;
                valorPista = tablero.celdas[fi][fj];
            }

        if (numPistas == 0)
        {
            cout << "Error: hay una region sin ninguna pista.\n";
            return false;
        }
        if (numPistas > 1)
        {
            cout << "Error: hay una region con " << numPistas << " pistas (debe ser exactamente 1).\n";
            return false;
        }

        // 3. El area de la region debe coincidir con el valor de la pista
        int area = (int)celdas.size();
        if (area != valorPista)
        {
            cout << "Error: una region tiene area " << area
                 << " pero su pista vale " << valorPista << ".\n";
            return false;
        }

        // 4. Las celdas de la region deben formar un rectangulo
        int minFila = tablero.filas, maxFila = -1;
        int minCol  = tablero.columnas, maxCol  = -1;
        for (auto [fi, fj] : celdas)
        {
            minFila = min(minFila, fi);
            maxFila = max(maxFila, fi);
            minCol  = min(minCol,  fj);
            maxCol  = max(maxCol,  fj);
        }
        int alto  = maxFila - minFila + 1;
        int ancho = maxCol  - minCol  + 1;
        if (alto * ancho != area)
        {
            cout << "Error: la region de la pista en F" << minFila + 1
                 << " C" << minCol + 1
                 << " no forma un rectangulo compacto.\n";
            return false;
        }
    }

    return true;
}