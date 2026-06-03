#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct Tablero
{
    int filas;
    int columnas;
    std::vector<std::vector<int>> celdas;
    std::vector<std::vector<int>> regiones;
};

bool cargarTablero(const std::string &archivo, Tablero &tablero);
bool mostrarTablero(const Tablero &tablero);
bool validarTablero(const Tablero &tablero);

#endif
