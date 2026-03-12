#ifndef FLEXIBILITYEXERCISE_H
#define FLEXIBILITYEXERCISE_H

#include "Exercise.h"

using namespace std;

class FlexibilityExercise : public Exercise {
private:
    int duration;      
    string bodyPart;    
    
public:
    FlexibilityExercise(string name, int difficulty, int points, int duration, string bodyPart);

    void perform() override;
};

#endif
