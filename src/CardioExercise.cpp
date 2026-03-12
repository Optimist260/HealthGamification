#include "CardioExercise.h"
#include <iostream>

using namespace std;

CardioExercise::CardioExercise(string name, int difficulty, int points, int duration)
    : Exercise(name, difficulty, points), duration(duration) {
    // simple calories estimate: duration * difficulty * 5 (placeholder)
    caloriesBurned = duration * difficulty * 5;
}

void CardioExercise::perform() {
    cout << "Cardio: " << name << " - duration: " << duration
         << " min, calories: " << caloriesBurned << ". Earned points: " << getPoints() << "\n";
}

int CardioExercise::getDuration() {
    return duration;
}

int CardioExercise::getCaloriesBurned() {
    return caloriesBurned;
}
