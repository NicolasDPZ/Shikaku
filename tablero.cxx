#include "tablero.h"

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

    // Filas
    for (int i = 0; i < tablero.filas; i++)
    {
        cout << "F" << left << setw(anchoFila) << i + 1 << " -> ";

        for (int j = 0; j < tablero.columnas; j++)
        {
            int val = tablero.celdas[i][j];
            if (val == 0)
                cout << "|    ";
            else
                cout << "| " << left << setw(2) << val << " ";
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
    return true;
}