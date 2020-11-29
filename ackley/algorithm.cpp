#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include "ackley.hpp"
#include "Individual.hpp"

typedef double (* selecionFun)(int args);  // maybe pass a function as a parameter?

std::vector<Individual> initPopulation(int size, unsigned dimension){
    std::vector<Individual> newPop;
    for (int i = 0; i < size; ++i) {
        double const lower_bound = -32.768; //value taken from website
        double const upper_bound = 32.768;
        unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count(); //generate a seed
        std::uniform_real_distribution<double> distri(lower_bound, upper_bound);
        std::default_random_engine engine;
        std::vector<double> chromosomes;

        for (int j = 0; j < dimension; ++j) {
            double x = distri(engine);
            chromosomes.push_back(x);
        }
        Individual newIndi(chromosomes);
        newPop.push_back(newIndi);
    }
    return newPop;
}

void crossover(){}

void mutation(std::vector<Individual>& Population) {
    const double probabilityOfChoice = 0.2;
    const double probabilityOfMutation = 0.2;
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> distri(0, 1);
    std::default_random_engine engine(seed);

    for (unsigned i = 0; i < Population.size(); ++i) {
        double rand = distri(engine);
        if (rand <= probabilityOfChoice) {
            std::vector<double>* chromosomes = Population[i].getChromosomes();
            for (unsigned j = 0; j < chromosomes->size(); ++j) {
                rand = distri(engine);
                if (rand <= probabilityOfMutation)
                    mutate(chromosomes->at(j));
            }
        }
    }
}

void mutate(double& x) {
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::normal_distribution<double> distri(0, 5);
    std::default_random_engine engine(seed);

    x += distri(engine);
}

/* three selection method's */

std::vector<Individual> rouletteSelection(std::vector<Individual> Population) {
    //TODO trzeba dodac skalowanie
    double sum = 0;
    std::vector<Individual> newPop;

    for (Individual indi : Population)
        sum += indi.getFitness();
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> distri(0, sum);
    std::default_random_engine engine(seed);
    for (unsigned i = 0; i < Population.size(); ++i) {
        double rand = distri(engine);
        double tempSum = 0;
        bool lookForRand = true;
        for (unsigned j = 0; lookForRand && j < Population.size(); ++j) {
            tempSum += Population[j].getFitness();
            if (tempSum > rand) {
                newPop.push_back(Population[j]);
                lookForRand = false;
            }
        }
    }
    return newPop;
}

void selectionFun2(){}

void mySelection(){}



std::vector<Individual> geneticAlgorithm(const unsigned DIM, const unsigned POP, const unsigned GEN){
    std::vector<Individual> Population, newPop;
    Population = initPopulation(POP, DIM);                    //inicjacja
    for (unsigned i = 0; i < Population.size(); ++i) {      //ocena
        Population[i].evaluate();
    }

    for (int i = 0; i < GEN; ++i) {
        newPop = rouletteSelection(Population);             //reprodukcja
        //crossover(newPop);                                //krzyzowanie
        mutation(newPop);                                   //mutacja
        for (unsigned i = 0; i < newPop.size(); ++i) {      //ocena
            newPop[i].evaluate();
        }
        Population = newPop;                                //sukcesja
    }
    return Population;
}