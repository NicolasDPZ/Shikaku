#include "interfaz.h"

void Ayudas()
{
    cout << "=== Comandos disponibles: === \n";
    cout << "  Mostrar ayudas:       h \n";
    cout << "  Cargar un tablero:    c <nombre del archivo>  \n";
    cout << "  Jugar:                j <fila> <columna> <inicio> <final>\n";
    cout << "  Limpiar el tablero:   l\n";
    cout << "  Mostrar el tablero:   m\n";
    cout << "  Verificar solución:   v\n";
    cout << "  Salir del juego:      s\n";
}

void Juego(Tablero &tablero)
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
            Ayudas();
            break;

        case 'c':
        {
            string archivo;
            ss >> archivo;
            if (archivo.empty())
            {
                cout << "Uso: c <nombre del archivo>\n";
            }
            else if (cargarTablero(archivo, tablero))
            {
                cout << "Tablero cargado desde: " << archivo << "\n";
            }
            else
            {
                cout << "Error al cargar '" << archivo << "'. Verifica que el archivo exista.\n";
            }
            break;
        }

        case 'j':
        {
            int fila, columna, inicio, final_;
            if (ss >> fila >> columna >> inicio >> final_)
            {
                // hacerMovimiento(tablero, fila, columna, inicio, final_);
                cout << "(movimiento pendiente de implementar)\n";
            }
            else
            {
                cout << "Uso: j <fila> <columna> <inicio> <final>\n";
            }
            break;
        }

        case 'l':
        {
            tablero = Tablero();
            cout << "Tablero limpiado.\n";
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
                cout << "¡Solución válida!\n";
            else
                cout << "La solución tiene errores.\n";
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
