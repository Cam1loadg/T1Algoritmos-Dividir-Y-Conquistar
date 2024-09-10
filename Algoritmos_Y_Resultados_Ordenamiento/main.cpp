#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <sys/stat.h> // para crear directorios
#include <algorithm>  // para sort estándar

using namespace std;
using namespace std::chrono;

// Función para leer el dataset desde un archivo
vector<vector<int>> leerDataset(const string& nombreArchivo) {
    ifstream file(nombreArchivo);
    vector<vector<int>> dataset;
    string linea;

    // Verificar si el archivo se pudo abrir
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    // Leer cada línea del archivo
    while (getline(file, linea)) {
        vector<int> numeros;
        string numero = "";
        // Procesar cada carácter de la línea
        for (char c : linea) {
            if (c == ' ') {
                // Convertir el número leído a entero y agregarlo al vector
                if (!numero.empty()) {
                    try {
                        numeros.push_back(stoi(numero));
                    } catch (const invalid_argument& e) {
                    }
                    numero = "";
                }
            } else {
                numero += c;
            }
        }
        // Agregar el último número de la línea
        if (!numero.empty()) {
            try {
                numeros.push_back(stoi(numero));
            } catch (const invalid_argument& e) {
            }
        }
        dataset.push_back(numeros);
    }

    file.close();
    return dataset;
}

// Función para imprimir un vector
void imprimirVector(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Algoritmo Selection Sort obtenido de: https://www.geeksforgeeks.org/selection-sort-algorithm-2/?ref=gcse_ind
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        // Encontrar el índice del elemento mínimo en el subarreglo no ordenado
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        // Intercambiar el elemento mínimo con el primer elemento no ordenado
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}

// Función auxiliar para el algoritmo Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    // Copiar datos a los arreglos temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Fusionar los arreglos temporales de nuevo en arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Algoritmo Merge Sort, junto a la función auxiliar obtenida de: https://www.geeksforgeeks.org/merge-sort/?ref=gcse_ind
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    // Ordenar la primera y segunda mitad
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    // Fusionar las mitades ordenadas
    merge(arr, left, mid, right);
}

// Función auxiliar para el algoritmo Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pivote
    int i = low - 1; // Índice del elemento más pequeño

    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor que el pivote
        if (arr[j] < pivot) {
            i++; // Incrementar el índice del elemento más pequeño
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Algoritmo Quick Sort, junto a la función auxiliar obtenida de: https://www.geeksforgeeks.org/quick-sort-algorithm/?ref=gcse_ind
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi es el índice de partición, arr[pi] está en la posición correcta
        int pi = partition(arr, low, high);
        // Ordenar los elementos por separado antes y después de la partición
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Algoritmo Insertion Sort Recursivo, obtenido de https://www.geeksforgeeks.org/insertion-sort-swapping-elements/?ref=gcse_ind
void insertionSortRecursive(vector<int>& arr, int n) {
    if (n <= 1)
        return;

    // Ordenar los primeros n-1 elementos
    insertionSortRecursive(arr, n - 1);
    int last = arr[n - 1];
    int j = n - 2;

    // Mover los elementos del arreglo que son mayores que el último elemento
    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = last;
}

// Función para guardar los tiempos y resultados en un archivo
void guardarResultados(const string& nombreArchivo, const vector<pair<int, long long>>& resultados) {
    ofstream file(nombreArchivo);
    file << "Tamaño,Tiempo (microsegundos)\n";
    for (const auto& resultado : resultados) {
        file << resultado.first << "," << resultado.second << "\n";
    }
    file.close();
}

// Función para guardar la salida de los arreglos ordenados en un archivo
void guardarSalida(const string& nombreArchivo, const vector<vector<int>>& resultados) {
    ofstream file(nombreArchivo);
    for (const auto& arr : resultados) {
        for (int num : arr) {
            file << num << " ";
        }
        file << "\n";
    }
    file.close();
}

int main() {
    // Leer el dataset desde el archivo
    vector<vector<int>> dataset = leerDataset("dataset.txt");

    // Crear directorios para guardar los resultados y salidas
    mkdir("Resultados"); // Crear directorio Resultados
    mkdir("Salida");     // Crear directorio Salida

    // Variables para almacenar los tiempos y salidas de cada algoritmo
    vector<pair<int, long long>> tiemposSelectionSort;
    vector<vector<int>> salidaSelectionSort;

    // SELECTION SORT
    for (auto arr : dataset) {
        auto inicio = high_resolution_clock::now();
        selectionSort(arr);
        auto fin = high_resolution_clock::now();
        long long duracion = duration_cast<microseconds>(fin - inicio).count();
        tiemposSelectionSort.push_back({arr.size(), duracion});
        salidaSelectionSort.push_back(arr);
    }
    guardarResultados("Resultados/Selection_Sort.csv", tiemposSelectionSort);
    guardarSalida("Salida/Selection_Sort.txt", salidaSelectionSort);

    // MERGE SORT
    vector<pair<int, long long>> tiemposMergeSort;
    vector<vector<int>> salidaMergeSort;

    for (auto arr : dataset) {
        auto inicio = high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto fin = high_resolution_clock::now();
        long long duracion = duration_cast<microseconds>(fin - inicio).count();
        tiemposMergeSort.push_back({arr.size(), duracion});
        salidaMergeSort.push_back(arr);
    }
    guardarResultados("Resultados/Merge_Sort.csv", tiemposMergeSort);
    guardarSalida("Salida/Merge_Sort.txt", salidaMergeSort);

    // QUICK SORT
    vector<pair<int, long long>> tiemposQuickSort;
    vector<vector<int>> salidaQuickSort;

    for (auto arr : dataset) {
        auto inicio = high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto fin = high_resolution_clock::now();
        long long duracion = duration_cast<microseconds>(fin - inicio).count();
        tiemposQuickSort.push_back({arr.size(), duracion});
        salidaQuickSort.push_back(arr);
    }
    guardarResultados("Resultados/Quick_Sort.csv", tiemposQuickSort);
    guardarSalida("Salida/Quick_Sort.txt", salidaQuickSort);

    // STANDARD SORT
    vector<pair<int, long long>> tiemposStandardSort;
    vector<vector<int>> salidaStandardSort;

    for (auto arr : dataset) {
        auto inicio = high_resolution_clock::now();
        sort(arr.begin(), arr.end());
        auto fin = high_resolution_clock::now();
        long long duracion = duration_cast<microseconds>(fin - inicio).count();
        tiemposStandardSort.push_back({arr.size(), duracion});
        salidaStandardSort.push_back(arr);
    }
    guardarResultados("Resultados/Standard_Sort.csv", tiemposStandardSort);
    guardarSalida("Salida/Standard_Sort.txt", salidaStandardSort);

    // INSERTION SORT RECURSIVO
    vector<pair<int, long long>> tiemposInsertionSort;
    vector<vector<int>> salidaInsertionSort;

    for (auto arr : dataset) {
        auto inicio = high_resolution_clock::now();
        insertionSortRecursive(arr, arr.size());
        auto fin = high_resolution_clock::now();
        long long duracion = duration_cast<microseconds>(fin - inicio).count();
        tiemposInsertionSort.push_back({arr.size(), duracion});
        salidaInsertionSort.push_back(arr);
    }
    guardarResultados("Resultados/Insertion_Sort_Recursive.csv", tiemposInsertionSort);
    guardarSalida("Salida/Insertion_Sort_Recursive.txt", salidaInsertionSort);

    return 0;
}