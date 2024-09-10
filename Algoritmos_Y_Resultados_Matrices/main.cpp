#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <sstream>
using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

// Algoritmo cúbico tradicional para la multiplicación de matrices
void multiplicacionCubicaTradicional(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    // Iterar sobre las filas de A
    for (int i = 0; i < n; i++) {
        // Iterar sobre las columnas de B
        for (int j = 0; j < n; j++) {
            C[i][j] = 0; // Inicializar el elemento C[i][j] a 0
            // Calcular el producto punto de la fila i de A y la columna j de B
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Función para transponer una matriz
void transponerMatriz(const vector<vector<int>>& B, vector<vector<int>>& BT, int n) {
    // Iterar sobre las filas de B
    for (int i = 0; i < n; i++) {
        // Iterar sobre las columnas de B
        for (int j = 0; j < n; j++) {
            BT[j][i] = B[i][j]; // Asignar el elemento transpuesto
        }
    }
}

// Algoritmo cúbico optimizado utilizando la transposición de matrices
void multiplicacionCubicaOptimizada(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    vector<vector<int>> BT(n, vector<int>(n, 0)); // Matriz transpuesta de B
    transponerMatriz(B, BT, n); // Transponer la matriz B
    
    // Iterar sobre las filas de A
    for (int i = 0; i < n; i++) {
        // Iterar sobre las columnas de BT (originalmente filas de B)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0; // Inicializar el elemento C[i][j] a 0
            // Calcular el producto punto de la fila i de A y la fila j de BT
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
}

// Función para sumar dos matrices
void sumaMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    // Iterar sobre las filas de las matrices
    for (int i = 0; i < n; i++) {
        // Iterar sobre las columnas de las matrices
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j]; // Sumar los elementos correspondientes
        }
    }
}

// Función para restar dos matrices
void restaMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    // Iterar sobre las filas de las matrices
    for (int i = 0; i < n; i++) {
        // Iterar sobre las columnas de las matrices
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j]; // Restar los elementos correspondientes
        }
    }
}

// Algoritmo de Strassen para la multiplicación de matrices
void strassenMultiplicacion(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    // Caso base: matrices de 1x1
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int nuevoTam = n / 2; // Tamaño de las submatrices
    vector<int> temp(nuevoTam); // Vector temporal para inicializar submatrices

    // Crear submatrices
    vector<vector<int>> A11(nuevoTam, temp), A12(nuevoTam, temp), A21(nuevoTam, temp), A22(nuevoTam, temp);
    vector<vector<int>> B11(nuevoTam, temp), B12(nuevoTam, temp), B21(nuevoTam, temp), B22(nuevoTam, temp);
    vector<vector<int>> C11(nuevoTam, temp), C12(nuevoTam, temp), C21(nuevoTam, temp), C22(nuevoTam, temp);
    vector<vector<int>> M1(nuevoTam, temp), M2(nuevoTam, temp), M3(nuevoTam, temp), M4(nuevoTam, temp);
    vector<vector<int>> M5(nuevoTam, temp), M6(nuevoTam, temp), M7(nuevoTam, temp);
    vector<vector<int>> AResult(nuevoTam, temp), BResult(nuevoTam, temp);

    // Dividir matrices en submatrices
    for (int i = 0; i < nuevoTam; i++) {
        for (int j = 0; j < nuevoTam; j++) {
            A11[i][j] = A[i][j]; // Submatriz A11
            A12[i][j] = A[i][j + nuevoTam]; // Submatriz A12
            A21[i][j] = A[i + nuevoTam][j]; // Submatriz A21
            A22[i][j] = A[i + nuevoTam][j + nuevoTam]; // Submatriz A22

            B11[i][j] = B[i][j]; // Submatriz B11
            B12[i][j] = B[i][j + nuevoTam]; // Submatriz B12
            B21[i][j] = B[i + nuevoTam][j]; // Submatriz B21
            B22[i][j] = B[i + nuevoTam][j + nuevoTam]; // Submatriz B22
        }
    }

    // Calcular M1 a M7 usando las submatrices
    sumaMatrices(A11, A22, AResult, nuevoTam); // A11 + A22
    sumaMatrices(B11, B22, BResult, nuevoTam); // B11 + B22
    strassenMultiplicacion(AResult, BResult, M1, nuevoTam); // M1 = (A11 + A22) * (B11 + B22)

    sumaMatrices(A21, A22, AResult, nuevoTam); // A21 + A22
    strassenMultiplicacion(AResult, B11, M2, nuevoTam); // M2 = (A21 + A22) * B11

    restaMatrices(B12, B22, BResult, nuevoTam); // B12 - B22
    strassenMultiplicacion(A11, BResult, M3, nuevoTam); // M3 = A11 * (B12 - B22)

    restaMatrices(B21, B11, BResult, nuevoTam); // B21 - B11
    strassenMultiplicacion(A22, BResult, M4, nuevoTam); // M4 = A22 * (B21 - B11)

    sumaMatrices(A11, A12, AResult, nuevoTam); // A11 + A12
    strassenMultiplicacion(AResult, B22, M5, nuevoTam); // M5 = (A11 + A12) * B22

    restaMatrices(A21, A11, AResult, nuevoTam); // A21 - A11
    sumaMatrices(B11, B12, BResult, nuevoTam); // B11 + B12
    strassenMultiplicacion(AResult, BResult, M6, nuevoTam); // M6 = (A21 - A11) * (B11 + B12)

    restaMatrices(A12, A22, AResult, nuevoTam); // A12 - A22
    sumaMatrices(B21, B22, BResult, nuevoTam); // B21 + B22
    strassenMultiplicacion(AResult, BResult, M7, nuevoTam); // M7 = (A12 - A22) * (B21 + B22)

    // Calcular C11, C12, C21, C22
    sumaMatrices(M1, M4, AResult, nuevoTam); // M1 + M4
    restaMatrices(AResult, M5, BResult, nuevoTam); // (M1 + M4) - M5
    sumaMatrices(BResult, M7, C11, nuevoTam); // C11 = (M1 + M4 - M5 + M7)

    sumaMatrices(M3, M5, C12, nuevoTam); // C12 = M3 + M5

    sumaMatrices(M2, M4, C21, nuevoTam); // C21 = M2 + M4

    restaMatrices(M1, M2, AResult, nuevoTam); // M1 - M2
    sumaMatrices(AResult, M3, BResult, nuevoTam); // (M1 - M2) + M3
    sumaMatrices(BResult, M6, C22, nuevoTam); // C22 = (M1 - M2 + M3 + M6)

    // Combinar submatrices en la matriz resultante
    for (int i = 0; i < nuevoTam; i++) {
        for (int j = 0; j < nuevoTam; j++) {
            C[i][j] = C11[i][j]; // Asignar C11
            C[i][j + nuevoTam] = C12[i][j]; // Asignar C12
            C[i + nuevoTam][j] = C21[i][j]; // Asignar C21
            C[i + nuevoTam][j + nuevoTam] = C22[i][j]; // Asignar C22
        }
    }
}

// Función para leer las matrices desde el archivo datasetMatriz.txt
vector<pair<vector<vector<int>>, vector<vector<int>>>> leerMatrices(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    vector<pair<vector<vector<int>>, vector<vector<int>>>> dataset;
    string linea;

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        if (linea.find("Matriz A") != string::npos) {
            int m, n;
            sscanf(linea.c_str(), "Matriz A (%dx%d):", &m, &n);
            vector<vector<int>> A(m, vector<int>(n));

            // Leer la matriz A
            for (int i = 0; i < m; ++i) {
                getline(archivo, linea);
                stringstream ss(linea);
                for (int j = 0; j < n; ++j) {
                    ss >> A[i][j];
                }
            }

            getline(archivo, linea); // Leer línea en blanco

            getline(archivo, linea); // Leer la línea de la Matriz B
            int p;
            sscanf(linea.c_str(), "Matriz B (%dx%d):", &n, &p);
            vector<vector<int>> B(n, vector<int>(p));

            // Leer la matriz B
            for (int i = 0; i < n; ++i) {
                getline(archivo, linea);
                stringstream ss(linea);
                for (int j = 0; j < p; ++j) {
                    ss >> B[i][j];
                }
            }

            dataset.emplace_back(A, B); // Agregar las matrices leídas al dataset
        }
    }

    archivo.close();
    return dataset;
}

// Función para realizar la multiplicación de matrices y registrar resultados
template<typename Func>
void medirTiempo(Func algoritmo, const pair<vector<vector<int>>, vector<vector<int>>>& matrices, const string& archivoCSV, const string& archivoSalida) {
    const vector<vector<int>>& A = matrices.first;
    const vector<vector<int>>& B = matrices.second;
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    // Medir tiempo de ejecución
    auto inicio = high_resolution_clock::now();
    algoritmo(A, B, C, n);
    auto fin = high_resolution_clock::now();
    long long tiempo = duration_cast<microseconds>(fin - inicio).count();

    // Guardar el tiempo en un archivo CSV
    ofstream fileCSV(archivoCSV, ios::app);
    fileCSV << A.size() << "x" << A[0].size() << "," << B.size() << "x" << B[0].size() << "," << tiempo << endl;
    fileCSV.close();

    // Guardar la matriz resultante en un archivo de salida
    ofstream fileSalida(archivoSalida, ios::app);
    fileSalida << "Matriz A (" << A.size() << "x" << A[0].size() << "), Matriz B (" << B.size() << "x" << B[0].size() << ")\n";
    for (const auto& fila : C) {
        for (int val : fila) {
            fileSalida << val << " ";
        }
        fileSalida << endl;
    }
    fileSalida << endl;
    fileSalida.close();
}

int main() {
    // Crear directorios para resultados y salidas
    fs::create_directory("Resultados");
    fs::create_directory("Salida");

    // Leer el archivo datasetMatriz.txt
    vector<pair<vector<vector<int>>, vector<vector<int>>>> dataset = leerMatrices("datasetMatriz.txt");

    // Algoritmo cúbico tradicional
    ofstream cubicoFile("Resultados/Cubico_Tradicional.csv");
    cubicoFile << "Tamaño Matriz A,Tamaño Matriz B,Tiempo(microsegundos)\n";
    cubicoFile.close();

    // Medir tiempo y guardar resultados para el algoritmo cúbico tradicional
    for (const auto& matrices : dataset) {
        medirTiempo(multiplicacionCubicaTradicional, matrices, "Resultados/Cubico_Tradicional.csv", "Salida/Cubico_Tradicional.txt");
    }

    // Algoritmo cúbico optimizado
    ofstream optimizadoFile("Resultados/Cubico_Optimizado.csv");
    optimizadoFile << "Tamaño Matriz A,Tamaño Matriz B,Tiempo(microsegundos)\n";
    optimizadoFile.close();

    // Medir tiempo y guardar resultados para el algoritmo cúbico optimizado
    for (const auto& matrices : dataset) {
        medirTiempo(multiplicacionCubicaOptimizada, matrices, "Resultados/Cubico_Optimizado.csv", "Salida/Cubico_Optimizado.txt");
    }

    // Algoritmo de Strassen
    ofstream strassenFile("Resultados/Strassen.csv");
    strassenFile << "Tamaño Matriz A,Tamaño Matriz B,Tiempo(microsegundos)\n";
    strassenFile.close();

    // Medir tiempo y guardar resultados para el algoritmo de Strassen
    for (const auto& matrices : dataset) {
        medirTiempo(strassenMultiplicacion, matrices, "Resultados/Strassen.csv", "Salida/Strassen.txt");
    }

    return 0;
}