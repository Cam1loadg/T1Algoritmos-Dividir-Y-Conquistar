#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath> // Para pow

using namespace std;

// Parámetros globales predeterminados para facilitar ajustes
const int MIN_N = 1; // Valor mínimo para n
const int MAX_N = 10;  // Valor máximo para n
const int MIN_VAL = -400; //  Valor mínimo para los valores de las matrices
const int MAX_VAL = 400;  //  Valor máximo para los valores de las matrices
const int CANTIDAD_PARES = 4; //  Cantidad de pares de matrices a generar

// Función para generar una matriz cuadrada con valores aleatorios
vector<vector<int>> generarMatrizAleatoria(int tamano, int minVal = MIN_VAL, int maxVal = MAX_VAL) {
    vector<vector<int>> matriz(tamano, vector<int>(tamano)); // Crear matriz de 'tamano x tamano'
    
    // Rellenar la matriz con valores aleatorios entre minVal y maxVal
    for (int i = 0; i < tamano; ++i) {
        for (int j = 0; j < tamano; ++j) {
            matriz[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
    return matriz;
}

// Función para guardar los pares de matrices en un archivo
void guardarParesDeMatricesEnArchivo(const string& nombreArchivo) {
    // Abrir archivo para escritura
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    // Iterar sobre el número de pares de matrices a generar
    for (int i = 0; i < CANTIDAD_PARES; ++i) {
        // Seleccionar un valor aleatorio para n entre MIN_N y MAX_N
        int n = MIN_N + rand() % (MAX_N - MIN_N + 1);
        int tamano = pow(2, n); // Calcular tamaño 2^n

        // Generar las matrices A y B
        vector<vector<int>> matrizA = generarMatrizAleatoria(tamano);
        vector<vector<int>> matrizB = generarMatrizAleatoria(tamano);

        // Guardar matriz A en el archivo
        archivo << "Matriz A (" << tamano << "x" << tamano << "):" << endl;
        for (const auto& fila : matrizA) {
            for (int val : fila) {
                archivo << val << " ";
            }
            archivo << endl;
        }
        archivo << endl;

        // Guardar matriz B en el archivo
        archivo << "Matriz B (" << tamano << "x" << tamano << "):" << endl;
        for (const auto& fila : matrizB) {
            for (int val : fila) {
                archivo << val << " ";
            }
            archivo << endl;
        }
        archivo << endl;
    }

    // Cerrar el archivo
    archivo.close();
}

int main() {
    // Inicializar la semilla aleatoria
    srand(static_cast<unsigned int>(time(0)));

    // Nombre del archivo a generar
    string nombreArchivo = "datasetMatriz.txt";
    
    // Llamar a la función para generar y guardar los pares de matrices
    guardarParesDeMatricesEnArchivo(nombreArchivo);

    return 0;
}
