#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include "ackley.hpp"
#include "Individual.hpp"


std::vector<Individual> initPopulation(int size, unsigned dimension){
    std::vector<Individual> newPop;
    for (int i = 0; i < size; ++i) {
        double const lower_bound = -32.768; //value taken from website
        double const upper_bound = 32.768;
        unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count(); //generate a seed
        std::uniform_real_distribution<double> distri(lower_bound, upper_bound);
        std::default_random_engine engine;
        std::vector<double> chromosomes;

        for (unsigned j = 0; j < dimension; ++j) {
            double x = distri(engine);
            chromosomes.push_back(x);
        }
        Individual newIndi(chromosomes);
        newPop.push_back(newIndi);
    }
    return newPop;
}

//2 point crossover
void cross(Individual& first, Individual& second, const unsigned DIM) {
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_int_distribution<int> distri(0, DIM - 1);
    std::default_random_engine engine(seed);
    int crossPoint1 = distri(engine);
    int crossPoint2 = distri(engine);     // czy moge dwa razy uzyc distri(engine)?
    
    if (crossPoint1 > crossPoint2)
        std::swap(crossPoint1, crossPoint2);

    for (int i = 0; i < DIM; ++i) {
        if (!(i >= crossPoint1 && i <= crossPoint2))
            std::swap(first.getGenes()->at(i), second.getGenes()->at(i));
    }
}

void crossover(std::vector<Individual>& Population, const unsigned DIM) {
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_int_distribution<int> distri(0, DIM); // miedzy 0, DIM - 1 czy DIM ????
    std::default_random_engine engine(seed);

    for (unsigned i = 0; i < Population.size() / 2; ++i) {
        cross(Population[distri(engine)], Population[distri(engine)], DIM);
    }
}


void mutate(double& x) {
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::normal_distribution<double> distri(0, 5);
    std::default_random_engine engine(seed);

    x += distri(engine);
}

void mutation(std::vector<Individual>& Population) {
    const double probabilityOfChoice = 0.2;
    const double probabilityOfMutation = 0.2;
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> distri(0, 1);
    std::default_random_engine engine(seed);

    for (unsigned i = 0; i < Population.size(); ++i) {
        double rand = distri(engine);
        if (rand <= probabilityOfChoice) {
            std::vector<double>* chromosomes = Population[i].getGenes();
            for (unsigned j = 0; j < chromosomes->size(); ++j) {
                rand = distri(engine);
                if (rand <= probabilityOfMutation)
                    mutate(chromosomes->at(j));
            }
        }
    }
}

/* roulettle selection */

std::vector<Individual> rouletteSelection(std::vector<Individual>& Population) { // referencja zamiast kopii
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

/* tournament selection */

std::vector<Individual> initTournament(const unsigned tourSize, const std::vector<Individual>& Population) {
    std::vector<Individual> newTour;
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_int_distribution<int> distri(0, Population.size() - 1);
    std::default_random_engine engine(seed);
    
    for (unsigned i = 0; i < tourSize; ++i) {
        newTour.push_back(Population[distri(engine)]);
    }
    
    return newTour;
}

Individual chooseWinner(const unsigned tourSize, std::vector<Individual>& tournament) {
    Individual winner(tournament[0]);

    for (unsigned i = 1; i < tourSize; ++i)
        if (tournament[i].getFitness() > winner.getFitness())
            winner = tournament[i];

    return winner;
}

std::vector<Individual> tournamentSel(const unsigned tournamentSize, std::vector<Individual>& Population) {
    int numOfTournaments = Population.size();
    std::vector<Individual> newPop;
    std::vector<Individual> tournament;

    for (int i = 0; i < numOfTournaments; ++i) {
        tournament = initTournament(tournamentSize, Population);
        newPop.push_back(chooseWinner(tournamentSize, tournament));
    }

    return newPop;
}

/** best fraction selection 
  * returns population filled with the best 100/breaks percent individuals
  */

std::vector<Individual> bestFractionSel(std::vector<Individual>& Population, int breaks) {
    std::vector<Individual> newPop;
    int range = Population.size()/breaks;
    std::sort(Population.begin(), Population.end());

    int i = 0;
    for (; i < breaks; ++i) {
        for( int j = 0; j < range; ++j)
            newPop.push_back(Population[j]);
    }
    i = 0;
    while (newPop.size() != Population.size()) {
        newPop.push_back(Population[i]);
        ++i;
    }
    
    return newPop;
}


typedef std::vector<Individual>(*selecionFun)(std::vector<Individual>& Population);  // maybe pass a function as a parameter?

std::vector<Individual> geneticAlgorithm(const unsigned DIM, const unsigned POP, const unsigned GEN){
    const unsigned TOUR_SIZE = 2;

    std::vector<Individual> Population, newPop;
    Population = initPopulation(POP, DIM);                    //inicjacja
    for (unsigned i = 0; i < Population.size(); ++i) {      //ocena
        Population[i].evaluate();
    }

    for (unsigned i = 0; i < GEN; ++i) {
        //newPop = rouletteSelection(Population);   
        newPop = tournamentSel(TOUR_SIZE, Population);
        //newPop = rouletteSelection(Population);    //reprodukcja, jak wywolac przekazana funkcje jako argument?
        crossover(newPop, DIM);                                //krzyzowanie
        mutation(newPop);                                   //mutacja
        for (unsigned i = 0; i < newPop.size(); ++i) {      //ocena
            newPop[i].evaluate();
        }
        Population = newPop;                                //sukcesja
    }
    return Population;
}