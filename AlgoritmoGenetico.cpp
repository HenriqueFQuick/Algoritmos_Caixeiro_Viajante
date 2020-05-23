#include <iostream>
#include <math.h>
#include<chrono>
#include<vector>
#include <bits/stdc++.h> 
#include <algorithm>
#include<string>

using namespace std;

class City{
    public:
        int x;
        int y;
        double distanceTo(City city);
        City();
        City(int x, int y);
};
City::City(int a, int b){
    x = a;
    y = b;
}
City::City(){
    x = INT_MAX;
    y = INT_MAX;
}
double City::distanceTo(City city){
    int xDistance = abs(x - city.x);
    int yDistance = abs(y - city.y);
    double distance = sqrt( (xDistance*xDistance) + (yDistance*yDistance) );
    
    return distance;
}





//TourManager
vector<City> destinationCities;

void TourManageraddCity(City city){
    destinationCities.push_back(city);
}
City TourManagergetCity(int index){
    return (City)destinationCities[index];
}
int TourManagernumberOfCities(){
    return destinationCities.size();
}





class Tour{
    public:
        Tour();
        Tour(vector<City> tour);
        void generateIndividual();
        City getCity(int tourPosition);
        void setCity(int tourPosition, City city);
        int getDistance();
        int tourSize();
        bool containsCity(City city);
        vector<City> tour;
        int distance = 0;
};
Tour::Tour(){
    for(int i = 0; i < TourManagernumberOfCities(); i++){
        City city(INT_MAX,INT_MAX);
        tour.push_back(city);
    }
}
Tour::Tour(vector<City> tour){
    tour = tour;
}
void Tour::setCity(int tourPosition, City city) {
    tour[tourPosition] = city;
    distance = 0;
}
void Tour::generateIndividual(){
    for (int cityIndex = 0; cityIndex < TourManagernumberOfCities(); cityIndex++) {
        setCity(cityIndex, TourManagergetCity(cityIndex));
    }
    random_shuffle(tour.begin(), tour.end());
}
City Tour::getCity(int tourPosition) {
    return (City)tour[tourPosition];
}
int Tour::tourSize() {
    return tour.size();
}
bool Tour::containsCity(City city){
    for(int i = 0; i < tour.size(); i++){
        if(tour[i].x == city.x && tour[i].y == city.y)
            return true;
    }
    return false;
}
int Tour::getDistance(){

    if (distance == 0) {
        int tourDistance = 0;
        for (int cityIndex=0; cityIndex < tourSize(); cityIndex++) {

            City fromCity = getCity(cityIndex);
            City destinationCity;

            if(cityIndex+1 < tourSize())
                destinationCity = getCity(cityIndex+1);
            else
                destinationCity = getCity(0);

            tourDistance += fromCity.distanceTo(destinationCity);
        }
        distance = tourDistance;
    }
    return distance;
}





class Population{
    public:
        vector<Tour> tours;
        Population(int populationSize, bool initialize);
        void saveTour(int index, Tour tour);
        Tour getTour(int index);
        Tour getFittest();
        int populationSize();
};
Population::Population(int populationSize, bool initialize){
    for (int i = 0; i < populationSize; i++) {
        Tour newTour;
        newTour.Tour::generateIndividual();
        Population::saveTour(i, newTour);
    }
}
void Population::saveTour(int index, Tour tour) {
    if(tours.size() < TourManagernumberOfCities()){
        tours.push_back(tour);
    }else
        tours[index] = tour;
}
Tour Population::getTour(int index) {
    return tours[index];
}
int Population::populationSize() {
    return tours.size();
}
Tour Population::getFittest() {
    Tour fittest = tours[0];
    
    for (int i = 0; i < Population::populationSize(); i++) {
        if (fittest.Tour::getDistance() > getTour(i).Tour::getDistance()) {
            fittest = getTour(i);
        }
    }
    return fittest;
}




double mutationRate = 1;
int tournamentSize = 4;
bool elitism = true;

int returnCityNumber(int x, int y){
    for(int j = 0; j < TourManagernumberOfCities(); j++){
        if(x == destinationCities[j].x && y == destinationCities[j].y)
            return j;
    }
    return -1;
}


Tour tournamentSelection(Population pop) {
    
    Population tournament(tournamentSize, false);
    
    for (int i = 0; i < tournamentSize; i++) {
        int randomId = (int) (rand() % pop.populationSize());
        tournament.saveTour(i, pop.getTour(randomId));
    }
    
    Tour fittest = tournament.Population::getFittest();
    
    return fittest;
}

void mutatePrint(Tour tour) {
    int k = 0;
    cout << "MUTACAO " << endl << "Tour inicial: " << endl;
    for(int i = 0; i < TourManagernumberOfCities(); i++){
        int cityN = returnCityNumber(tour.tour[i].x, tour.tour[i].y);
        if(cityN != -1)
            cout << cityN << "\t|\t";
        else
            cout << "X\t|\t";
    }
    for(int tourPos1=0; tourPos1 < tour.tourSize(); tourPos1++){
        if((rand()%10) < mutationRate){
            k++;
            int tourPos2 = (int) (rand()%tour.tourSize());

            City city1 = tour.getCity(tourPos1);
            City city2 = tour.getCity(tourPos2);

            tour.setCity(tourPos2, city1);
            tour.setCity(tourPos1, city2);
        }
    }
    cout << endl << "Tour depois de " << k <<" mutacoes: " << endl;
    for(int i = 0; i < TourManagernumberOfCities(); i++){
        int cityN = returnCityNumber(tour.tour[i].x, tour.tour[i].y);
        if(cityN != -1)
            cout << cityN << "\t|\t";
        else
            cout << "X\t|\t";
    }
    cout << endl << endl;
}

Tour crossoverPrint(Tour parent1, Tour parent2) {
    Tour child;

    int startPos = (int) (rand() % parent1.tourSize());
    int endPos = (int) (rand() % parent1.tourSize());
    
    for (int i = 0; i < TourManagernumberOfCities(); i++) {
        if (startPos < endPos && i > startPos && i < endPos)
            child.Tour::setCity(i, parent1.Tour::getCity(i));
        else if (startPos > endPos) {
            if (!(i < startPos && i > endPos)) {
                child.Tour::setCity(i, parent1.Tour::getCity(i));
            }
        }
    }
    cout << "CROSSOVER" << endl << "PosicaoFinal do pai1: " << startPos << ", posicaoFinal do pai1: " << endPos << endl << "Depois de colocadas as cidades do pai1: " << endl;
    for(int i = 0; i < TourManagernumberOfCities(); i++){
        int cityN = returnCityNumber(child.tour[i].x, child.tour[i].y);
        if(cityN != -1)
            cout << cityN << "\t|\t";
        else
            cout << "X\t|\t";
    }
    cout << endl << "Depois de completado com as cidades do pai2: " << endl;

    for (int i = 0; i < parent2.tourSize(); i++) {
        if (!child.Tour::containsCity(parent2.getCity(i))) {
            for (int ii = 0; ii < child.tourSize(); ii++) {
                if (child.Tour::getCity(ii).x == INT_MAX) {
                    child.Tour::setCity(ii, parent2.Tour::getCity(i));
                    break;
                }
            }
        }
    }
    for(int i = 0; i < TourManagernumberOfCities(); i++){
        int cityN = returnCityNumber(child.tour[i].x, child.tour[i].y);
        if(cityN != -1)
            cout << cityN << "\t|\t";
        else
            cout << "X\t|\t";
    }
    cout << endl << endl;
    return child;
}


Population evolvePopulationPrint(Population pop){
    Population newPopulation(pop.populationSize(), false);

    int elitismOffset = 0;
    if (elitism) {
        newPopulation.saveTour(0, pop.Population::getFittest());
        elitismOffset = 1;
    }

    for (int i = elitismOffset; i < newPopulation.populationSize(); i++) {

        Tour parent1 = tournamentSelection(pop);
        Tour parent2 = tournamentSelection(pop);

        Tour child = crossoverPrint(parent1, parent2);
        
        newPopulation.saveTour(i, child);
    }
    cout << endl;
    for (int i = elitismOffset; i < newPopulation.populationSize(); i++) {
        mutatePrint(newPopulation.getTour(i));
    }
    cout << endl << endl << endl;
    return newPopulation;
}












void mutate(Tour tour) {
    for(int tourPos1=0; tourPos1 < tour.tourSize(); tourPos1++){
        if((rand()%10) < mutationRate){
            int tourPos2 = (int) (rand()%tour.tourSize());

            City city1 = tour.getCity(tourPos1);
            City city2 = tour.getCity(tourPos2);

            tour.setCity(tourPos2, city1);
            tour.setCity(tourPos1, city2);
        }
    }
}

Tour crossover(Tour parent1, Tour parent2) {
    Tour child;

    int startPos = (int) (rand() % parent1.tourSize());
    int endPos = (int) (rand() % parent1.tourSize());
    
    for (int i = 0; i < TourManagernumberOfCities(); i++) {
        if (startPos < endPos && i > startPos && i < endPos)
            child.Tour::setCity(i, parent1.Tour::getCity(i));
        else if (startPos > endPos) {
            if (!(i < startPos && i > endPos)) {
                child.Tour::setCity(i, parent1.Tour::getCity(i));
            }
        }
    }

    for (int i = 0; i < parent2.tourSize(); i++) {
        if (!child.Tour::containsCity(parent2.getCity(i))) {
            for (int ii = 0; ii < child.tourSize(); ii++) {
                if (child.Tour::getCity(ii).x == INT_MAX) {
                    child.Tour::setCity(ii, parent2.Tour::getCity(i));
                    break;
                }
            }
        }
    }
    return child;
}


Population evolvePopulation(Population pop){
    Population newPopulation(pop.populationSize(), false);

    int elitismOffset = 0;
    if (elitism) {
        newPopulation.saveTour(0, pop.Population::getFittest());
        elitismOffset = 1;
    }

    for (int i = elitismOffset; i < newPopulation.populationSize(); i++) {

        Tour parent1 = tournamentSelection(pop);
        Tour parent2 = tournamentSelection(pop);

        Tour child = crossover(parent1, parent2);
        
        newPopulation.saveTour(i, child);
    }
    for (int i = elitismOffset; i < newPopulation.populationSize(); i++) {
        mutate(newPopulation.getTour(i));
    }
    return newPopulation;
}



void printCity(Tour tour){
    vector<int> vetor;
    for(int i = 0; i < tour.Tour::tourSize(); i++) {
        for(int j = 0; j < TourManagernumberOfCities(); j++){
            if(tour.getCity(i).x == destinationCities[j].x && tour.getCity(i).y == destinationCities[j].y)
                vetor.push_back(j+1);
        }
    }
    int j = 0;
    for(j = 0; j < vetor.size() && vetor[j] != 1; j++);
    for(int i = 0; i < vetor.size(); i++){
        cout << vetor[j] << " ";
        j = (j+ 1) % vetor.size();
    }
    cout << endl;
}

void createPopulation(int n){
    int a,b;
    while(n > 0){
        cin>>a;
        cin>>b;
        City city(a,b);
        TourManageraddCity(city);
        n--;
    }
}

int main(){

    int n;
    cin >> n;
    tournamentSize = n;
    auto inicio = std::chrono::high_resolution_clock::now();
    createPopulation(n);
    Population pop(n,true);

    for (int i = 0; i < 100; i++) {
        pop = evolvePopulation(pop);
        //pop = evolvePopulationPrint(pop);
    }
    Tour tour = pop.Population::getFittest();
    cout << tour.Tour::getDistance() << endl;
    printCity(tour);
    auto resultado = std::chrono::high_resolution_clock::now()-inicio;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(resultado).count();
    cout << microseconds << endl;
    return 0;
}