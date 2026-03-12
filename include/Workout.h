#ifndef WORKOUT_H
#define WORKOUT_H

#include <string>
#include <vector>
#include "Exercise.h"

using namespace std;

class Workout {
private:
    string workoutName;         
    vector<Exercise*> exercises;

public:
    Workout(string name);

    void addExercise(Exercise* ex);
    int getTotalPoints();
    void performWorkout();
};

#endif
