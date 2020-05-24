#include <iostream>
#include <math.h>
#include<chrono>
#include <limits.h>
#include <vector>

using namespace std;
#define MAXTAM 100

int* vetor;
double distanciaMinima = 999999999.0;

double distanceBetweenTwoPoints(int x1, int x2, int y1, int y2){
	double distance = 0.0, difference1 = 0.0, difference2 = 0.0;
	
	difference1 = x2-x1;
	difference2 = y2-y1;

	distance = sqrt(pow(difference1,2) + pow(difference2,2)); 	
	return distance;
}

void completaMatriz(int tam, int* y, int* x){
    int aux = 0;
    while(aux < tam){
        cin >> x[aux];
        cin >> y[aux];
        aux++;
    }
}

double** adjacenciesMatrixCreate(int n){
	int i = 0, j = 0, k, l;
	double** matrix = new double*[MAXTAM];
	int* x = new int[n];
	int* y = new int[n];
	
	completaMatriz(n, y, x);
	
	for(i; i< MAXTAM; i++){
		matrix[i] = new double[MAXTAM];
	}
	for(k = 0; k < n; k++){
		for(l = 0; l < n; l++){
			matrix[k][l] = distanceBetweenTwoPoints(x[k], x[l], y[k], y[l]);
		}
	}
	return matrix;
}

double dynamicProgramming(int n, double** matrixCities, int k, int anterior, vector<vector<double>>& minimalDistancies, int* w, int aux){
    if(anterior == ((1 << (n)) - 1)){
        return matrixCities[k][0];
    }
         

    if(minimalDistancies[k][anterior] != INT_MAX){
        return minimalDistancies[k][anterior];
    }

    for(int i = 0; i < (n); ++i){
        if(i == k || (anterior & (1 << i))){
            continue;
        }
        
        double distance = matrixCities[k][i] + dynamicProgramming(n, matrixCities, i, anterior | (1 << i), minimalDistancies, w, aux);
        if(distance < minimalDistancies[k][anterior]){
            minimalDistancies[k][anterior] = distance;
        }
    }

    return minimalDistancies[k][anterior];

}

void printMatrix(double** matrix, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			cout << matrix[i][j] << " | ";
		}
		cout << "\n";
	}
}

int main(){
    int aux = 0;
    int n;
    cin >> n;
    vetor = new int[n];
    for(int i = 0; i < n; i++)
        vetor[i] = 0;
    int* w = new int[n];

    double** matrixCities = adjacenciesMatrixCreate(n);
    //printMatrix(matrixCities, n);
    auto inicio = std::chrono::high_resolution_clock::now();

    vector<vector<double>> minimalDistancies(n, vector<double>((1 << (n)) - 1, INT_MAX));
    
    distanciaMinima = dynamicProgramming(n,matrixCities, 0, 1, minimalDistancies, w, aux);

    cout << distanciaMinima << endl;

    auto resultado = std::chrono::high_resolution_clock::now()-inicio;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(resultado).count();
    cout << microseconds << endl;
    return 0;
}