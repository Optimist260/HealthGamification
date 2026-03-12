#include "Badge.h"

using namespace std;

Badge::Badge(string title_, string desc, int reqPoints, string reqAct)
    : title(title_), description(desc), requiredPoints(reqPoints),
      requiredActivity(reqAct), awarded(false) {}

string Badge::getTitle() const {
    return title;
}

string Badge::getDescription() const {
    return description;
}

int Badge::getRequiredPoints() const {
    return requiredPoints;
}

string Badge::getRequiredActivity() const {
    return requiredActivity;
}

bool Badge::isAwarded() const {
    return awarded;
}

void Badge::markAwarded() {
    awarded = true;
}

bool Badge::canEarn(int userPoints, const vector<string>& activities) const {
    // Check points requirement
    if (userPoints < requiredPoints)
        return false;

    // If badge requires a specific achievement
    if (!requiredActivity.empty()) {
        for (auto& act : activities) {
            if (act.find(requiredActivity) != string::npos)
                return true;
        }
        return false;
    }

    // Only points needed
    return true;
}
