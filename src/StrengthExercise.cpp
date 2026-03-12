#include "StrengthExercise.h"
#include <iostream>

using namespace std;

StrengthExercise::StrengthExercise(string name, int difficulty, int points, int sets, int reps, int weight)
    : Exercise(name, difficulty, points), sets(sets), repsPerSet(reps), weight(weight) { }

void StrengthExercise::perform() {
    cout << "Strength: " << name << " - " << sets << " sets x "
         << repsPerSet << " reps (weight: " << weight << " kg). Earned points: " << getPoints() << "\n";
}

int StrengthExercise::getTotalReps() {
    return sets * repsPerSet;
}
