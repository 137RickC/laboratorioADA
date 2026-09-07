#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool buscarEnTexto(const string &texto, const string &palabra){
    int n = texto.size();
    int m = palabra. size();
    
    for(int i= 0; i<=(n-m) ; i++){
        int j = 0;
        while (j<m && texto[i+j] == palabra[j]){ j++; 
        
        }if(j==m) return true;
    }
    return false;
}
bool busquedaBinaria(const vector<string> &lista, const string &palabra){
    int izq = 0, der =lista.size()-1;
    
    while (izq<= der){
        int medio = izq + (der - izq)/2;
        if(lista[medio] == palabra) return true;
        if(lista[medio] < palabra) izq = medio -1;
        else der = medio - 1;
    }
    
    return false;
}
int main(){
    string texto = "El granizo comenzó a caer con furia sobre los tejados de la pequeña aldea, mientras los vecinos corrían apresurados para proteger sus cosechas y los animales buscaban refugio debajo de los viejos árboles";
    string palabra = "vecinos";

    if( buscarEnTexto(texto, palabra)){

    }
    return 0;
}