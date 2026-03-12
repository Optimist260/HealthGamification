#include "User.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
User::User(string n) : name(n), points(0) {}

void User::addPoints(int p) {
    points += p;
}

void User::addActivity(string a) {
    if (activities.size() >= 10) {
        activities.erase(activities.begin()); // remove oldest
    }
    activities.push_back(a);
}

void User::addBadge(string b) {
    if (find(badges.begin(), badges.end(), b) == badges.end())
        badges.push_back(b);
}

void User::displayProfile() {
    cout << "============================\n";
    cout << "PROFILE\n";
    cout << "----------------------------\n";
    cout << "Name: " << name << "\n";
    cout << "Points: " << points << "\n";
    cout << "Badges:\n";
    for (auto &b : earnedBadges)
    cout << " - " << b.getTitle() << " (" << b.getDescription() << ")\n";
    cout << "Activities (last 10):\n";
    for (auto &a : activities)
        cout << " - " << a << "\n";
    cout << "============================\n";
}

void User::checkForNewBadges(const vector<Badge>& allBadges) {
    for (auto badge : allBadges) {
        bool alreadyHas = false;

        for (auto& b : earnedBadges) {
            if (b.getTitle() == badge.getTitle()) {
                alreadyHas = true;
                break;
            }
        }

        if (!alreadyHas && badge.canEarn(points, activities)) {
            earnedBadges.push_back(badge);
            cout << "\n*** Achievement Unlocked: " << badge.getTitle() << "! ***\n";
        }
    }
}

bool User::loadFromFile(string username) {
    ifstream file("data/users/" + username + ".txt");
    if(!file.is_open()) return false;

    activities.clear();
    badges.clear();

    string line;

    while(getline(file, line)) {
        if(line.rfind("NAME:", 0) == 0)
            name = line.substr(5);

        else if(line.rfind("POINTS:", 0) == 0)
            points = stoi(line.substr(7));

        else if(line.rfind("BADGES:", 0) == 0) {
            string list = line.substr(7);
            size_t pos = 0;
            while((pos = list.find(',')) != string::npos) {
                badges.push_back(list.substr(0,pos));
                list.erase(0,pos+1);
            }
            if(!list.empty()) badges.push_back(list);
        }

        else if(line == "ACTIVITIES:") {
            while(getline(file, line)) {
                if(line.size() > 0)
                    activities.push_back(line);
            }
        }
    }
    return true;
}



void User::saveToFile() {
    ofstream file("data/users/" + name + ".txt");

    file << "NAME:" << name << "\n";
    file << "POINTS:" << points << "\n";

    file << "BADGES:";
    for (int i = 0; i < earnedBadges.size(); i++) {
    file << earnedBadges[i].getTitle();
    if (i < earnedBadges.size() - 1) file << ",";
    }
    file << "\n";

    file << "ACTIVITIES:\n";
    for(auto &a : activities)
        file << a << "\n";

    file.close();
}

string User::getName() const {
    return name;
}

int User::getPoints() const {
    return points;
}
