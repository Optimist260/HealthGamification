#include <iostream>
#include <algorithm>
#include <filesystem>
#include "User.h"  
#include "CardioExercise.h"
#include "StrengthExercise.h"
#include "FlexibilityExercise.h"
#include "Workout.h"
#include "Badge.h"
#include "FileManager.h"
#include "Leaderboard.h"

using namespace std;

vector<Badge> allBadges = {
    Badge("Getting Started", "Earn 10 points!", 10),
    Badge("Active Member", "Log 5 activities!", 50, "Workout"),
    Badge("Pro Gamer", "Reach 100 points!", 100)
};

int main() {
    // ensure directories exist
    filesystem::create_directories("data/users");

    // load leaderboard
    loadLeaderboard();

    bool appRunning = true;
    while (appRunning) {
        string username;
        int choice;

        cout << "============================" << endl;
        cout << "   HEALTH GAMIFICATION APP   " << endl;
        cout << "============================" << endl;
        cout << "1. Login (Existing User)" << endl;
        cout << "2. Create New User" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        User user("temp");

        if (choice == 3) {
            appRunning = false;
            break;
        }

        if (choice == 1) {
            auto users = listUsers();

            if (users.empty()) {
                cout << "No users found. Create new." << endl;
                cout << "Enter username: ";
                cin >> username;
                transform(username.begin(), username.end(), username.begin(), ::tolower);
                user = User(username);
                user.saveToFile();
            } else {
                cout << "Available Users:" << endl;
                for (int i = 0; i < users.size(); i++)
                    cout << i + 1 << ". " << users[i] << endl;

                cout << "Enter number: ";
                cin >> choice;
                username = users[choice - 1];

                user.loadFromFile(username);
                user.checkForNewBadges(allBadges);

            }
        } else if (choice == 2) {
            cout << "Enter new username: ";
            cin >> username;
            transform(username.begin(), username.end(), username.begin(), ::tolower);
            user = User(username);
            user.saveToFile();
        } else {
            continue;
        }

        bool userMenuActive = true;
        while (userMenuActive) {
            cout << "\n======= MENU =======" << endl;
            cout << "1. Perform Cardio Exercise" << endl;
            cout << "2. Perform Strength Exercise" << endl;
            cout << "3. Perform Flexibility Exercise" << endl;
            cout << "4. Perform Pre-Defined Workout" << endl;
            cout << "5. Show Profile" << endl;
            cout << "6. Show Leaderboard" << endl;
            cout << "7. Save Progress" << endl;
            cout << "8. Logout" << endl;
            cout << "9. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;

            if (choice == 8) {
                user.saveToFile();
                updateLeaderboard(user);
                userMenuActive = false;
                continue;
            }

            if (choice == 9) {
                user.saveToFile();
                updateLeaderboard(user);
                appRunning = false;
                userMenuActive = false;
                continue;
            }

            switch (choice) {
            case 1: {
                CardioExercise run("Morning Run", 2, 20, 30);
                run.perform();
                user.addPoints(run.getPoints());
                user.addActivity("Cardio: Morning Run");
                user.checkForNewBadges(allBadges);
                break;
            }
            case 2: {
                StrengthExercise push("Push-ups", 3, 15, 3, 12, 0);
                push.perform();
                user.addPoints(push.getPoints());
                user.addActivity("Strength: Push-ups");
                user.checkForNewBadges(allBadges);
                break;
            }
            case 3: {
                FlexibilityExercise yoga("Morning Yoga", 1, 5, 600, "Full Body");
                yoga.perform();
                user.addPoints(yoga.getPoints());
                user.addActivity("Flexibility: Morning Yoga");
                user.checkForNewBadges(allBadges);
                break;
            }
            case 4: {
                Workout w("Quick Combo");
                CardioExercise run("Morning Run", 2, 20, 30);
                StrengthExercise push("Push-ups", 3, 15, 3, 12, 0);
                FlexibilityExercise yoga("Morning Yoga", 1, 5, 600, "Full Body");

                w.addExercise(&run);
                w.addExercise(&push);
                w.addExercise(&yoga);

                w.performWorkout();
                user.addPoints(w.getTotalPoints());
                user.addActivity("Completed Workout: Quick Combo");
                user.checkForNewBadges(allBadges);
                break;
            }
            case 5:
                user.displayProfile();
                break;

            case 6:
                showLeaderboard();
                break;

            case 7:
                user.saveToFile();
                updateLeaderboard(user);
                cout << "Progress saved." << endl;
                break;
            }
        }
    }

    cout << "Exiting..." << endl;
    return 0;
}
