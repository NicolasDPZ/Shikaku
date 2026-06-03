#include "interfaz.h"
#include "solucionador.h"
#include "hacerMovimiento.h"
#include "borrarMovimiento.h"

void Ayudas()
{
    cout << "=== Comandos disponibles: === \n";
    cout << "  Mostrar ayudas:       h \n";
    cout << "  Cargar un tablero:    c <nombre del archivo>  \n";
    cout << "  Jugar:                j <fila1> <columna1> <fila2> <columna2>\n";
    cout << "  Deshacer:             d <fila1> <columna1> <fila2> <columna2>\n";
    cout << "  Resolver (sintetico): r\n";
    cout << "  Limpiar el tablero:   l\n";
    cout << "  Mostrar el tablero:   m\n";
    cout << "  Verificar solucion:   v\n";
    cout << "  Salir del juego:      s\n";
}

void Juego(Tablero &tablero, vector<vector<int>> historial)
{

    Ayudas();
    string linea;
    char comando = ' ';
    do
    {
        cout << "\nIngrese un comando: ";
        getline(cin, linea);

        if (linea.empty())
            continue;

        comando = linea[0];
        istringstream ss(linea);
        ss >> comando;

        switch (comando)
        {
        case 'h':
        {
            Ayudas();
            break;
        }   

1        case 'c':
        {
            string archivo;
            ss >> archivo;
            if (archivo.empty())
            {
                cout << "Uso: c <nombre del archivo>\n";
                break;
            }

            string rutaTableros = "Tableros/" + archivo;
            bool cargado = cargarTablero(rutaTableros, tablero);

            if (!cargado)
                cargado = cargarTablero(archivo, tablero);

            if (cargado)
                cout << "Tablero cargado exitosamente.\n";
            else
                cout << "Error al cargar '" << archivo << "'. Verifica que el archivo exista en Tableros/ o en el directorio actual.\n";
            break;
        }
        

        case 'j':
        {
            int f1, c1, f2, c2;
            if (ss >> f1 >> c1 >> f2 >> c2)
                hacerMovimiento(tablero, f1, c1, f2, c2, historial);
            else
                cout << "Uso: j <fila1> <col1> <fila2> <col2>\n";
            break;
        }

        case 'd':
        {
            int fila, col;
            if (ss >> fila >> col)
                borrarMovimiento(tablero, fila, col);
            else
                cout << "Uso: d <fila> <columna>\n";
            break;
        }

        case 'r':
        {
            // Solucionador sintetico: intenta resolver el tablero solo.
            if (resolverTablero(tablero))
            {
                cout << "Solucion encontrada!\n";
                mostrarRegiones(tablero);
            }
            break;
        }

        case 'l':
        {
            tablero = Tablero();
            historial.clear();
            break;
        }

        case 'm':
        {
            mostrarTablero(tablero);
            break;
        }

        case 'v':
        {
            if (validarTablero(tablero))
                cout << "Solucion valida!\n";
            else
                cout << "La solucion tiene errores.\n";
            break;
        }

        case 's':
        {
            cout << "Saliendo del juego... \n";
            break;
        }

        default:
            cout << "Ese comando no existe. Escribe 'h' para ver las ayudas. \n";
        }
    } while (comando != 's');
}
