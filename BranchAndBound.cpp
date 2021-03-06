#include <iostream>
#include <math.h>
#include<chrono>

using namespace std;

int* vetor;
double distanciaMinima = 999999999.0;

void branchAndBound(int n, int w[], int x[], int y[], bool used[], int k, double soma, int anterior){
    int i;
    if(k == n){
        soma += sqrt(pow(x[anterior]-x[0],2)+pow(y[anterior]-y[0],2));
        if(soma < distanciaMinima){
            distanciaMinima = soma;
            for(i = 0; i< n; i++){
                vetor[i] = w[i] + 1;
            }
        }
        used[anterior] = false;
    } else{
        if(soma > distanciaMinima)
            return;
        for(i = 0; i < n; i++){
            if(!used[i]){
                used[i] = true;
                w[k] = i;
                soma += sqrt(pow(x[i]-x[anterior],2)+pow(y[i]-y[anterior],2));
                branchAndBound(n, w, x, y, used, k+1, soma, i);
                soma -= sqrt(pow(x[i]-x[anterior],2)+pow(y[i]-y[anterior],2));
                used[i] = false;
            }
        }
    }
}

void completaVetores(int tam, int* y, int* x){
    int aux = 0;
    while(aux < tam){
        cin >> x[aux];
        cin >> y[aux];
        aux++;
    }
}

int main(){

    int n;
    cin >> n;
    vetor = new int[n];
    bool* used = new bool[n];
    int* w = new int[n];
    int* x = new int[n];
    int* y = new int[n];
    completaVetores(n,x,y);
    auto inicio = std::chrono::high_resolution_clock::now();

    double soma = 0;
    for(int i = 0; i < n; i++)
        used[i] = false;
    branchAndBound(n, w, x, y, used, 0, 0, 0);

    cout << distanciaMinima << endl;
    for(int i = 0; i < n; i++)
        cout << vetor[i] << " ";
    auto resultado = std::chrono::high_resolution_clock::now()-inicio;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(resultado).count();
    cout << endl << microseconds << endl;
    return 0;
}