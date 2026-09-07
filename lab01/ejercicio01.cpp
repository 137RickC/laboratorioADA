#include <iostream>
using namespace std;

int euclides (int a , int b){
    while (b!=0){
        int temp = b;
        b = a%b;
        a = temp; 
    }
    return a;
}
int bucles( int a , int b){
    int menor = min(a, b);
    for (int i = menor; i >= 1; i--){
        if(a%i== 0 && b%i== 0){ return i;}
    }
}
int main(){
    cout << euclides(6, 4) << " Con el algoritmo de Euclices" << endl;
    cout << bucles(6, 4) << " Con el algoritmo de Euclices" << endl;
    return 0;    
}