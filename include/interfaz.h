#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "tablero.h"
#include "hacerMovimiento.h"
#include "borrarMovimiento.h"


using namespace std;

void Ayudas();
void Juego(Tablero &tablero, vector<vector<int>> &historial);

#endif