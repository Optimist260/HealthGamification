#ifndef CARDIOEXERCISE_H
#define CARDIOEXERCISE_H

#include "Exercise.h"

using namespace std;

class CardioExercise : public Exercise {
private:
    int duration;        
    int caloriesBurned;  

public:
    CardioExercise(string name, int difficulty, int points, int duration);

    void perform() override;

    int getDuration();
    int getCaloriesBurned();
};

#endif
    