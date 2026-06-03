#ifndef HACER_MOVIMIENTO_H
#define HACER_MOVIMIENTO_H

#include "tablero.h"
#include <vector>
using namespace std;

bool hacerMovimiento(Tablero &tablero, int fila1, int col1, int fila2, int col2,
                     vector<vector<int>> &historial);

#endif