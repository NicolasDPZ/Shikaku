#ifndef SOLUCIONADOR_H
#define SOLUCIONADOR_H

#include "tablero.h"

// Resuelve el Shikaku usando backtracking (prueba y error con retroceso).
// Si encuentra una solucion, devuelve true y la deja guardada en
// tablero.regiones. Si no, devuelve false.
bool resolverTablero(Tablero &tablero);

// Muestra en pantalla la solucion encontrada (los rectangulos / regiones).
void mostrarRegiones(const Tablero &tablero);

#endif
