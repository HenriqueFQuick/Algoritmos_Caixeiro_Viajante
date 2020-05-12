#include <iostream>
#include <math.h>
#include<chrono>

using namespace std;

int* vetor;
double distanciaMinima = 999999999.0;

void forcaBruta(int n, int w[], int x[], int y[], bool used[], int k, double soma, int anterior){
    int i;
    if(k == n){
        soma += sqrt(pow(x[anterior]-x[0],2)+pow(y[anterior]-y[0],2));
        if(soma < distanciaMinima){
            distanciaMinima = soma;
            for(i = 0; i< n; i++){
                vetor[i] = w[i] + 1;
            }
        }
    } else{
        for(i = 0; i < n; i++){
            if(!used[i]){
                used[i] = true;
                w[k] = i;
                soma += sqrt(pow(x[i]-x[anterior],2)+pow(y[i]-y[anterior],2));
                forcaBruta(n, w, x, y, used, k+1, soma, i);
                used[i] = false;
            }
        }
    }
}

void metodo(int n, double** cost, double** best, int* x, int* y){
    double t;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            cost[i][j] = 99999;
        }
    }
    for(int i = 0; i < n; i++) cost[i][i] = 0;

    for(int j = 0; j < n; j++){
        for(int i = 0; i < n-j; i++){
            for(int k = i+1; k <= i+j; k++){
                //cout << "j: " << j << " i: " << i << " k: " << k <<endl;
                //cout << cost[i][k-1] << "  " << cost[k][i+j] << " "<< sqrt(pow(x[i]-x[k],2)+pow(y[i]-y[k],2)) << endl;
                t = cost[i][k-1] + cost[k][i+j] + sqrt(pow(x[i]-x[k],2)+pow(y[i]-y[k],2));
                if(t < cost[i][i+j]){
                    cost[i][i+j] = t;
                    best[i][i+j] = k;
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << best[i][j] << " ";
        }
        cout << endl;
    }
}

double** criaMatriz(int n, double** matriz){
    matriz = new double*[n];
    for(int i = 0; i < n; i++){
        matriz[i] = new double[n];
    }
    for(int i = 0; i < n; i++){           
        for(int j = 0; j < n; j++){
            matriz[i][j] = 0;
        }
    }
    return matriz;
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
    double** cost;
    double** best;
    int* x = new int[n];
    int* y = new int[n];
    completaMatriz(n,x,y);
    auto inicio = std::chrono::high_resolution_clock::now();
    cost = criaMatriz(n, cost);
    best = criaMatriz(n, best);

    metodo(n, cost, best, x, y);

    cout << (cost[0][n-1]+sqrt(pow(x[0]-x[n-1],2)+pow(y[0]-y[n-1],2))) << endl;
    auto resultado = std::chrono::high_resolution_clock::now()-inicio;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(resultado).count();
    cout << endl << microseconds << endl;
    return 0;
}