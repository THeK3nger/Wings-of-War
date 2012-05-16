#include <stdio.h>
#include <time.h>
#include <locale>

#include "GameLogger.h"

using namespace std;

GameLogger::GameLogger() {
    _onfile = false;
}

GameLogger::GameLogger(string filename) {
    _file.open(filename.c_str());
    _onfile = true;
}

GameLogger::GameLogger(const GameLogger& orig) {
}

GameLogger::~GameLogger() {
    if (_onfile) {
        _file.close();
    }
}

void GameLogger::toLog(string message) {
    if (_onfile) {
        _file << "[" << currentTime() << "] " << message << endl;
    } else {
        cout << "[" << currentTime() << "] " << message << endl;
    }
}

string GameLogger::currentTime() {
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return string(asctime(timeinfo));
}

