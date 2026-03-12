#ifndef BADGE_H
#define BADGE_H

#include <string>
#include <vector>
using namespace std;

class Badge
{
private:
    string title;
    string description;
    int requiredPoints;
    string requiredActivity;
    bool awarded;

public:
    Badge(string title_, string desc, int reqPoints, string reqAct = "");

    string getTitle() const;
    string getDescription() const;
    int getRequiredPoints() const;
    string getRequiredActivity() const;
    bool isAwarded() const;
    void markAwarded();

    bool canEarn(int userPoints, const vector<string> &activities) const;
};

#endif
