#include <iostream>
#include <math.h>
#include<chrono>

using namespace std;

int* vetor;
double distanciaMinima = 999999999.0;

void branchAndBound(int n, int w[], int x[], int y[], bool used[], int k, double soma, int anterior){
    int i;
    if(k == n){
        //cout << "posicao: " << "0" << " anterior: "<< anterior << endl;
        //cout << x[anterior] << " " << x[0] << endl;
        //cout << y[anterior] << " " << y[0] << endl;
        //cout << sqrt(pow(x[anterior]-x[0],2)+pow(y[anterior]-y[0],2)) << endl;
        soma += sqrt(pow(x[anterior]-x[0],2)+pow(y[anterior]-y[0],2));
        //cout << soma << " < " << distanciaMinima << " = " << (soma < distanciaMinima) << endl;
        if(soma < distanciaMinima){
            distanciaMinima = soma;
            for(i = 0; i< n; i++){
                vetor[i] = w[i] + 1;
            }
        }
    } else{
        if(soma > distanciaMinima)
            return;
        for(i = 0; i < n; i++){
            if(!used[i]){
                used[i] = true;
                w[k] = i;
                //cout << "i: " << i << " anterior: "<< anterior << endl;
                //cout << x[i] << " " << x[anterior] << endl;
                //cout << y[i] << " " << y[anterior] << endl;
                //cout << sqrt(pow(x[i]-x[anterior],2)+pow(y[i]-y[anterior],2)) << endl;
                soma += sqrt(pow(x[i]-x[anterior],2)+pow(y[i]-y[anterior],2));
                branchAndBound(n, w, x, y, used, k+1, soma, i);
                used[i] = false;
            }
        }
    }
}

void completaMatriz(int tam, int* y, int* x){
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
    completaMatriz(n,x,y);
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