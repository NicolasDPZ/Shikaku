#include "solucionador.h"
#include <algorithm> // para sort

// ===========================================================================
//  SOLUCIONADOR DE SHIKAKU
//
//  Reglas del juego:
//    - El tablero se debe dividir en rectangulos.
//    - Cada rectangulo contiene EXACTAMENTE un numero.
//    - El area (filas x columnas) del rectangulo es igual a ese numero.
//    - Los rectangulos no se pueden solapar y deben cubrir todo el tablero.
//
//  Idea de la solucion (backtracking / "prueba y error con retroceso"):
//    1. Para cada numero (pista) calculamos TODOS los rectangulos posibles.
//    2. Vamos colocando un rectangulo por pista.
//    3. Si en algun momento no cabe ninguno, retrocedemos y probamos otro.
//    4. Cuando todas las pistas tienen su rectangulo, el tablero queda
//       completamente cubierto y ya tenemos la solucion.
// ===========================================================================

// ---------------------------------------------------------------------------
// Estructuras auxiliares (solo se usan dentro de este archivo)
// ---------------------------------------------------------------------------

// Una "pista" es una celda del tablero que tiene un numero.
struct Pista
{
    int fila;
    int columna;
    int valor;
};

// Un rectangulo candidato: esquina superior izquierda + tamano.
struct Rectangulo
{
    int fila;    // fila de la esquina superior
    int columna; // columna de la esquina izquierda
    int alto;    // numero de filas que ocupa
    int ancho;   // numero de columnas que ocupa
};

// ---------------------------------------------------------------------------
// 1. Comprobar si un rectangulo es "legal" para una pista
// ---------------------------------------------------------------------------
// Un rectangulo sirve si:
//   - cabe completamente dentro del tablero, y
//   - contiene exactamente UN numero (el de su propia pista).
static bool rectanguloValido(const Tablero &tablero, const Rectangulo &r)
{
    // Se sale del tablero?
    if (r.fila < 0 || r.columna < 0)
        return false;
    if (r.fila + r.alto > tablero.filas)
        return false;
    if (r.columna + r.ancho > tablero.columnas)
        return false;

    // Contar cuantas celdas con numero hay dentro del rectangulo.
    int numeros = 0;
    for (int i = r.fila; i < r.fila + r.alto; i++)
        for (int j = r.columna; j < r.columna + r.ancho; j++)
            if (tablero.celdas[i][j] != 0)
                numeros++;

    // Debe haber exactamente uno (el de la pista).
    return numeros == 1;
}

// ---------------------------------------------------------------------------
// 2. Generar todos los rectangulos posibles para una pista
// ---------------------------------------------------------------------------
static vector<Rectangulo> generarCandidatos(const Tablero &tablero, const Pista &p)
{
    vector<Rectangulo> candidatos;

    // Probamos todas las formas alto x ancho cuya area sea igual al numero.
    // Ejemplo: si el numero es 6 -> (1x6), (2x3), (3x2), (6x1).
    for (int alto = 1; alto <= p.valor; alto++)
    {
        if (p.valor % alto != 0) // "alto" debe dividir al valor
            continue;
        int ancho = p.valor / alto;

        // El rectangulo TIENE que cubrir la celda de la pista.
        // Por eso movemos la esquina superior izquierda dentro del rectangulo:
        // df y dc indican en que posicion del rectangulo queda la pista.
        for (int df = 0; df < alto; df++)
            for (int dc = 0; dc < ancho; dc++)
            {
                Rectangulo r;
                r.fila = p.fila - df;
                r.columna = p.columna - dc;
                r.alto = alto;
                r.ancho = ancho;

                if (rectanguloValido(tablero, r))
                    candidatos.push_back(r);
            }
    }
    return candidatos;
}

// ---------------------------------------------------------------------------
// 3. Ocupar / liberar celdas usando tablero.regiones
// ---------------------------------------------------------------------------
// regiones[i][j] == -1  -> celda libre
// regiones[i][j] == id  -> celda ocupada por el rectangulo numero "id"

// Esta libre todo el espacio que necesita el rectangulo?
static bool estaLibre(const Tablero &tablero, const Rectangulo &r)
{
    for (int i = r.fila; i < r.fila + r.alto; i++)
        for (int j = r.columna; j < r.columna + r.ancho; j++)
            if (tablero.regiones[i][j] != -1)
                return false;
    return true;
}

// Pinta (marca) las celdas del rectangulo con un identificador.
// Si id == -1, lo que hace es borrar/liberar el rectangulo.
static void pintar(Tablero &tablero, const Rectangulo &r, int id)
{
    for (int i = r.fila; i < r.fila + r.alto; i++)
        for (int j = r.columna; j < r.columna + r.ancho; j++)
            tablero.regiones[i][j] = id;
}

// ---------------------------------------------------------------------------
// 4. Backtracking: colocar una pista tras otra
// ---------------------------------------------------------------------------
static bool backtrack(Tablero &tablero,
                      const vector<vector<Rectangulo>> &candidatos,
                      int indice)
{
    // Caso base: ya colocamos todas las pistas -> solucion encontrada.
    if (indice == (int)candidatos.size())
        return true;

    // Probamos cada rectangulo candidato de la pista actual.
    for (const Rectangulo &r : candidatos[indice])
    {
        if (estaLibre(tablero, r))
        {
            pintar(tablero, r, indice); // colocar
            if (backtrack(tablero, candidatos, indice + 1))
                return true;            // funciono, ya no hay que probar mas
            pintar(tablero, r, -1);     // no funciono -> deshacer (retroceder)
        }
    }
    return false; // ningun candidato sirvio -> hay que retroceder
}

// ---------------------------------------------------------------------------
// 5. Funcion principal del solucionador
// ---------------------------------------------------------------------------
bool resolverTablero(Tablero &tablero)
{
    if (tablero.celdas.empty())
    {
        cout << "No hay tablero cargado.\n";
        return false;
    }

    // Dejamos el mapa de regiones limpio (todo libre = -1).
    tablero.regiones.assign(tablero.filas, vector<int>(tablero.columnas, -1));

    // 5.1 Buscar todas las pistas (celdas con numero).
    vector<Pista> pistas;
    int suma = 0;
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
            if (tablero.celdas[i][j] != 0)
            {
                Pista p;
                p.fila = i;
                p.columna = j;
                p.valor = tablero.celdas[i][j];
                pistas.push_back(p);
                suma += p.valor;
            }

    if (pistas.empty())
    {
        cout << "El tablero no tiene numeros, no hay nada que resolver.\n";
        return false;
    }

    // Comprobacion sencilla: en un Shikaku valido la suma de los numeros
    // SIEMPRE es igual al total de celdas (porque los rectangulos cubren
    // todo el tablero sin solaparse). Si no coinciden, no hay solucion.
    if (suma != tablero.filas * tablero.columnas)
    {
        cout << "La suma de los numeros (" << suma
             << ") no coincide con el total de celdas ("
             << tablero.filas * tablero.columnas << ").\n";
        cout << "Este tablero no puede tener solucion.\n";
        return false;
    }

    // 5.2 Generar la lista de candidatos de cada pista.
    vector<vector<Rectangulo>> candidatos;
    for (const Pista &p : pistas)
        candidatos.push_back(generarCandidatos(tablero, p));

    // 5.3 Truco sencillo para acelerar: resolver primero las pistas con
    //     MENOS candidatos. Asi, si una pista no tiene salida, lo
    //     descubrimos pronto y evitamos muchas pruebas inutiles.
    sort(candidatos.begin(), candidatos.end(),
         [](const vector<Rectangulo> &a, const vector<Rectangulo> &b)
         {
             return a.size() < b.size();
         });

    // 5.4 Arrancar el backtracking desde la primera pista.
    bool resuelto = backtrack(tablero, candidatos, 0);

    if (!resuelto)
        cout << "No se encontro solucion para este tablero.\n";

    return resuelto;
}

// ---------------------------------------------------------------------------
// 6. Mostrar la solucion en pantalla
// ---------------------------------------------------------------------------
// Cada numero que aparece es el "id" de un rectangulo: todas las celdas con
// el mismo numero forman un mismo rectangulo de la solucion.
void mostrarRegiones(const Tablero &tablero)
{
    if (tablero.regiones.empty())
    {
        cout << "No hay solucion para mostrar.\n";
        return;
    }

    cout << "\nSolucion (cada numero identifica un rectangulo):\n\n";

    int anchoFila = to_string(tablero.filas).length();
    string prefijo = string(anchoFila + 6, ' ');

    // Encabezado de columnas
    cout << prefijo;
    for (int j = 0; j < tablero.columnas; j++)
        cout << " C" << left << setw(3) << j + 1;
    cout << "\n";

    cout << prefijo;
    for (int j = 0; j < tablero.columnas; j++)
        cout << "+----";
    cout << "+\n";

    for (int i = 0; i < tablero.filas; i++)
    {
        cout << "F" << left << setw(anchoFila) << i + 1 << " -> ";

        for (int j = 0; j < tablero.columnas; j++)
        {
            int id = tablero.regiones[i][j];
            if (id == -1)
                cout << "|    ";
            else
                cout << "| " << left << setw(2) << id << " ";
        }
        cout << "|\n";

        cout << prefijo;
        for (int j = 0; j < tablero.columnas; j++)
            cout << "+----";
        cout << "+\n";
    }
}
