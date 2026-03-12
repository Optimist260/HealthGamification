#include "FileManager.h"
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

vector<string> listUsers() {
    vector<string> result;
    for(const auto &entry : fs::directory_iterator("data/users")) {
        auto name = entry.path().stem().string();
        result.push_back(name);
    }
    return result;
}

bool userExists(string username) {
    return fs::exists("data/users/" + username + ".txt");
}
