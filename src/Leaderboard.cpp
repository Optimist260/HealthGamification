#include "Leaderboard.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

struct Entry {
    string name;
    int points;
    int badges;
};

vector<Entry> board;

void loadLeaderboard() {
    board.clear();
    ifstream file("data/leaderboard.txt");
    string n;
    int p, b;
    while(file >> n >> p >> b) {
        board.push_back({n, p, b});
    }
}

void saveLeaderboard() {
    ofstream file("data/leaderboard.txt");
    for(auto &e : board)
        file << e.name << " " << e.points << " " << e.badges << "\n";
}

void updateLeaderboard(User &u) {
    bool found = false;
    for(auto &e : board){
        if(e.name == u.getName()){
            e.points = u.getPoints();
            e.badges = u.earnedBadges.size();
            found = true;
        }
    }
    if(!found)
        board.push_back({u.getName(), u.getPoints(), (int)u.earnedBadges.size()});

    sort(board.begin(), board.end(), 
        [](auto &a, auto &b){ return a.points > b.points; });

    saveLeaderboard();
}

void showLeaderboard(){
    cout << "===== LEADERBOARD =====\n";
    for(auto &e : board)
        cout << e.name << ": " << e.points << " points, " << e.badges << " badge(s)\n";
    cout << "=======================\n";
}
