#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
using namespace std;

class Exercise {
protected:
    string name;        
    int difficultyLevel;
    int points;         

public:
    Exercise(string name, int difficulty, int points);

    virtual void perform() = 0; 

    string getName();
    int getPoints();
};

#endif


























// #ifndef EXERCISE_H
// #define EXERCISE_H

// #include <string>

// class Exercise {
// private:
//     std::string name;
//     int caloriesBurned;
// public:
//     Exercise(const std::string& n, int c);
//     std::string getName() const;
//     int getCaloriesBurned() const;
// };

// #endif
