#include "Exercise.h"

using namespace std;

Exercise::Exercise(string name_, int difficulty, int points_)
    : name(name_), difficultyLevel(difficulty), points(points_) { }

string Exercise::getName() {
    return name;
}

int Exercise::getPoints() {
    return points;
}
