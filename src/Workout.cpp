#include "Workout.h"
#include <iostream>

using namespace std;

Workout::Workout(string name) : workoutName(name) {
    exercises.clear();
}

void Workout::addExercise(Exercise* ex) {
    exercises.push_back(ex);
}

int Workout::getTotalPoints() {
    int total = 0;
    for (Exercise* e : exercises) {
        if (e) total += e->getPoints();
    }
    return total;
}

void Workout::performWorkout() {
    cout << "=== Workout: " << workoutName << " ===\n";
    for (Exercise* e : exercises) {
        if (e) e->perform();   // polymorphic call
    }
    cout << "Total points for workout: " << getTotalPoints() << "\n";
    cout << "============================\n";
}
