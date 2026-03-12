#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include <string>
#include "User.h"

using namespace std;

void loadLeaderboard();
void saveLeaderboard();
void updateLeaderboard(User &u);
void showLeaderboard();

#endif