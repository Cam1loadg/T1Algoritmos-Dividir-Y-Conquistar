#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Genera un vector completamente aleatorio
void generarVectorAleatorio(vector<int>& vec, int tamano) {
    vec.clear();
    for (int i = 0; i < tamano; ++i) {
        vec.push_back(rand() % 100);  // Números entre 0 y 99
    }
}

// Genera un vector semiordenado (parte desordenada pequeña)
void generarVectorSemiordenado(vector<int>& vec, int tamano) {
    vec.clear();
    for (int i = 0; i < tamano; ++i) {
        vec.push_back(i);
    }
    // Desordena el 10% de los elementos
    for (int i = 0; i < tamano / 10; ++i) {
        swap(vec[i], vec[rand() % tamano]);
    }
}

// Genera un vector parcialmente ordenado (mitad ordenada, mitad aleatoria)
void generarVectorParcialmenteOrdenado(vector<int>& vec, int tamano) {
    vec.clear();
    for (int i = 0; i < tamano / 2; ++i) {
        vec.push_back(i);
    }
    for (int i = tamano / 2; i < tamano; ++i) {
        vec.push_back(rand() % 100);
    }
}

// Genera un vector completamente invertido
void generarVectorInvertido(vector<int>& vec, int tamano) {
    vec.clear();
    for (int i = tamano - 1; i >= 0; --i) {
        vec.push_back(i);
    }
}

// Escribe el vector en el archivo
void escribirVector(ofstream& archivo, const vector<int>& vec, const string& tipo) {
    archivo << tipo << " {";
    for (size_t i = 0; i < vec.size(); ++i) {
        archivo << vec[i];
        if (i < vec.size() - 1) {
            archivo << ", ";
        }
    }
    archivo << "}\n";
}

// Función principal para generar el dataset y almacenarlo en un archivo
void generarDataset(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo.\n";
        return;
    }

    srand(time(0));  // Semilla para generación aleatoria

    int cantidadAleatorio = 100 + rand() % 101;  // Entre 100 y 200
    int cantidadSemiordenado = 100 + rand() % 101;
    int cantidadParcialmenteOrdenado = 100 + rand() % 101;
    int cantidadInvertido = 100 + rand() % 101;

    vector<int> vec;

    // Generar vectores aleatorios
    for (int i = 0; i < cantidadAleatorio; ++i) {
        int tamano = 200 + rand() % 301;  // Tamaño aleatorio entre 200 y 500
        generarVectorAleatorio(vec, tamano);
        escribirVector(archivo, vec, "Aleatorio");
    }

    // Generar vectores semiordenados
    for (int i = 0; i < cantidadSemiordenado; ++i) {
        int tamano = 200 + rand() % 301;
        generarVectorSemiordenado(vec, tamano);
        escribirVector(archivo, vec, "Semiordenado");
    }

    // Generar vectores parcialmente ordenados
    for (int i = 0; i < cantidadParcialmenteOrdenado; ++i) {
        int tamano = 200 + rand() % 301;
        generarVectorParcialmenteOrdenado(vec, tamano);
        escribirVector(archivo, vec, "ParcialmenteOrdenado");
    }

    // Generar vectores invertidos
    for (int i = 0; i < cantidadInvertido; ++i) {
        int tamano = 200 + rand() % 301;
        generarVectorInvertido(vec, tamano);
        escribirVector(archivo, vec, "Invertido");
    }

    archivo.close();

    // Imprime por pantalla la cantidad de vectores generados por tipo
    cout << "Se generaron los siguientes vectores:\n";
    cout << "Aleatorios: " << cantidadAleatorio << endl;
    cout << "Semiordenados: " << cantidadSemiordenado << endl;
    cout << "Parcialmente ordenados: " << cantidadParcialmenteOrdenado << endl;
    cout << "Invertidos: " << cantidadInvertido << endl;
}

int main() {
    generarDataset("dataset.txt");
    return 0;
}
