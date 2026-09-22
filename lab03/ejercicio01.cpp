#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Estudiante{
    string nombre;
    string codigo;
    float promedio;
};

void merge(vector<Estudiante>& estudiantes, int izq, int medio, int der){
    vector<Estudiante> aux;

    int i = izq;
    int j = medio + 1;
    // Comparar ambas mitades
    while (i <= medio && j <= der){
        if(estudiantes[i].promedio <= estudiantes[j].promedio){
            aux.push_back(estudiantes[i]);
            i++;
        }
        else{
            aux.push_back(estudiantes[j]);
            j++;
        }
    }
    // Agregar los restantes de la izquierda
    while (i <= medio){
        aux.push_back(estudiantes[i]);
        i++;
    }
    // Agregar los restantes de la derecha
    while (j <= der){
        aux.push_back(estudiantes[j]);
        j++;
    }
    // Copiar al vector original
    for (int k = 0; k < aux.size(); k++){
        estudiantes[izq + k] = aux[k];
    }
}

void mergeSort(vector<Estudiante>& estudiantes, int izq, int der){
    if (izq < der){
        int medio = izq + (der - izq) / 2;

        mergeSort(estudiantes, izq, medio);
        mergeSort(estudiantes, medio + 1, der);
        merge(estudiantes, izq, medio, der);
    }
}

void mostrarEstudiantes(const vector<Estudiante>& estudiantes){
    cout << "ESTUDIANTES EN ORDEN DE PROMEDIO\n";
    cout << "CODIGO\t\tNOMBRE\t\tPROMEDIO\n";

    for (const Estudiante& estudiante : estudiantes){
        cout << estudiante.codigo << "\t\t"
             << estudiante.nombre << "\t\t"
             << estudiante.promedio << endl;
    }
}

int main(){
    int n;

    cout << "Cantidad de estudiantes: ";
    cin >> n;

    cin.ignore();

    vector<Estudiante> estudiantes(n);

    for (int i = 0; i < n; i++){

        cout << "\nESTUDIANTE " << i + 1 << endl;

        cout << "Nombre: ";
        getline(cin, estudiantes[i].nombre);

        cout << "Codigo: ";
        getline(cin, estudiantes[i].codigo);

        cout << "Promedio: ";
        cin >> estudiantes[i].promedio;

        cin.ignore();
    }

    mergeSort(estudiantes, 0, estudiantes.size() - 1);
    cout << endl;
    mostrarEstudiantes(estudiantes);

    return 0;
}