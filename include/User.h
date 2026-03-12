// User.h
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Badge.h"
using namespace std;

class User {
private:
    string name;
    int points;
    vector<string> activities; // last 10 only
    vector<string> badges;

public:
    User(string name);

    void addPoints(int p);
    void addActivity(string a);
    void addBadge(string b);

    string getName() const;
    int getPoints() const;
    void displayProfile(); 

    // persistence
    void saveToFile();
    bool loadFromFile(string username);
    
    void checkForNewBadges(const std::vector<Badge>& allBadges);

    std::vector<Badge> earnedBadges;

};

#endif
     


// #ifndef USER_H
// #define USER_H

// #include "Exercise.h"

// class User {
// private:
//     int points;
// public:
//     User();
//     void addPoints(int p);
//     int getPoints() const;

//     void doExercise(const Exercise& ex);  // new function
// };

// #endif