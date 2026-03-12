#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>

using namespace std;

vector<string> listUsers();
bool userExists(string username);

#endif
