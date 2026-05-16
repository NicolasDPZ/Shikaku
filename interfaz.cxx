#include "interfaz.h"

void Ayudas(){
    cout << "=== Comandos disponibles: === \n";
    cout << "0. Mostrar ayudas:       h \n";
    cout << "1. Cargar un tablero:    c <nombre del archivo>  \n";
    cout << "2. como jugar:           j <fila> <columna> <inicio> <final>\n";
    cout << "3. Limpiar el tablero:   l\n";
    cout << "4. mostrar el tablero:   m\n";
    cout << "5. verificar solucion:   v\n";
    cout << "6. Salir del juego:      s\n";

}


void Juego(Tablero &tablero){

    Ayudas();
    char comando;
    cout << "Ingrese un comando: \n";
    cin >> comando;

    switch(comando){
        case 'h':
            Ayudas();
            break;

        case 'c':
            string archivo;
            if (getArchivo(archivo)) {
                cout << "Archivo cargado: " << archivo << endl;
            } else {
                cout << "Error al cargar el archivo. Asegúrate de ingresar un archivo válido en txt, el uso del comando es 'c <nombre del archivo>' \n";
            }
            break;


        case 'j':
            //hacerMovimiento();
            break;


        case 'l':
            //limpiarTablero();
            break;


        case 'm':
            mostrarTablero(tablero);
            break;


        case 'v':
            //verificarSolucion();
            break;


        case 's':
            cout << "Saliendo del juego... \n";
            break;


        default:
            cout << "Ese comando no existe. Escribe 'h' para ver las ayudas. \n";
    }

}

