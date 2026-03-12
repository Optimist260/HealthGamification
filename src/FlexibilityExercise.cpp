#include "FlexibilityExercise.h"
#include <iostream>

using namespace std;

FlexibilityExercise::FlexibilityExercise(string name, int difficulty, int points, int duration, string bodyPart)
    : Exercise(name, difficulty, points), duration(duration), bodyPart(bodyPart) { }

void FlexibilityExercise::perform() {
    cout << "Flexibility: " << name << " - duration: " << duration
         << " sec, target: " << bodyPart << ". Earned points: " << getPoints() << "\n";
}
