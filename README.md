# Proyecto de Analisis de algoritmos

Shikaku es un puzzle japonés de lógica. El tablero es una cuadrícula con números dispersos, y el objetivo es dividirlo completamente en rectángulos siguiendo estas tres reglas:

Cada rectángulo contiene exactamente un número.
El área del rectángulo (filas × columnas) debe ser igual a ese número.
Los rectángulos no se pueden solapar y deben cubrir todas las celdas del tablero.

## Compilación y ejecución
Requiere g++ con soporte para C++17.
bashmake  
make run   
make clean

## Formato de los tableros
Los tableros son archivos .txt con el siguiente formato:
"<filas> <columnas>"
"<valores separados por espacios, 0 = celda vacía>"
Por ejemplo, un tablero 5×5:
5 5
3 0 0 4 0
4 0 3 0 0
0 0 0 2 0
4 0 0 4 0
0 0 1 0 0
La suma de todos los números debe ser igual al total de celdas del tablero (filas × columnas), de lo contrario el tablero no tiene solución válida.