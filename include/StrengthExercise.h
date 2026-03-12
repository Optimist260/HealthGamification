#ifndef STRENGTHEXERCISE_H
#define STRENGTHEXERCISE_H

#include "Exercise.h"

using namespace std;

class StrengthExercise : public Exercise {
private:
    int sets;        
    int repsPerSet;  
    int weight;      

public:
    StrengthExercise(string name, int difficulty, int points, int sets, int reps, int weight);

    void perform() override;

    int getTotalReps();
};

#endif
