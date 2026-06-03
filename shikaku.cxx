
#include "interfaz.h"
#include <iostream>
using namespace std;
 
int main()
{
    cout << "\n === Bienvenido al shikaku === \n\n";
 
    Tablero tablero;
    vector<vector<int>> historial;
    Juego(tablero, historial);
 
    return 0;
}
 
