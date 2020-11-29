#include <iostream>
#include <vector>
#include <cmath>
#include "ackley.hpp"
#include "Individual.hpp"

typedef double (* selecionFun)(int args);  // maybe pass a function as a parameter?

std::vector<Individual> initPopulation(int size, unsigned dimension){
    std::vector<Individual> newPop;
    Individual newIndi;
    newPop.push_back(newIndi);
    return newPop;
}

void crossover(){}

void mutation(){}

/* three selection method's */

void rouletteSelection(){
    //double selProbability = 
}

void selectionFun2(){}

void mySelection(){}



void geneticAlgorithm(){

}