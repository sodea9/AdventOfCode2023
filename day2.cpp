// Author: Sean O'Dea
// Date: 12/28/2023
// https://adventofcode.com/2023/day/2
// Day 2: Cube Conundrum

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <chrono>

using namespace std;

string *readInput(string path, int *total);
int checkGame(string game);
int gameProduct(string game);

int main() {
    auto start = chrono::high_resolution_clock::now();

    int numLines;
    string *lines = readInput("./inputs/day2.txt", &numLines); 

    int sum = 0;
    for (int i = 0; i < numLines; i++) {
        // sum += checkGame(lines[i]);
        sum += gameProduct(lines[i]);
    }
    cout << "SUM - " << sum << endl;

    delete[] lines;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    cout << "Solved in " << duration << " ms" << endl;
    return 0;
}

string *readInput(string path, int *total) {
    fstream input;
    input.open(path, ios::in);
    string *lines = new string[1024];
    string curLine;
    *total = 0;
    if (input.is_open()) {
        while (getline(input, curLine)) {
            lines[*total] = curLine;
            (*total)++;
        }
    } else {
        cout << "Input not found" << endl;
        exit(1);
    }

    return lines;
}

// Part 1
int checkGame(string game) {
    char *gameArr = &game[4];
    int id = 0;
    id = atoi(gameArr);

    const char delim[] = ":;,";
    char *savePtr = NULL;
    char *token = strtok_r(gameArr, delim, &savePtr);
    
    token = strtok_r(NULL, delim, &savePtr);
    while (token != NULL) {        
        int val = atoi(token);

        if ((val > 12 && strstr(token, "red") != NULL) ||
            (val > 13 && strstr(token, "green") != NULL) ||
            (val > 14 && strstr(token, "blue") != NULL)) {
            return 0;
        }
        token = strtok_r(NULL, delim, &savePtr);
    }
    return id;
}

// Part 2
int gameProduct(string game) {
    int redMax = -1;
    int blueMax = -1;
    int greenMax = -1;

    char *gameArr = &game[8];
    const char delim[] = ",;";
    char *savePtr = NULL;
    char *token = strtok_r(gameArr, delim, &savePtr);
    while (token != NULL) {
        int id = atoi(token);
        if (strstr(token, "red") && id > redMax) {
            redMax = id;
        } else if (strstr(token, "blue") && id > blueMax) {
            blueMax = id;
        } else if (strstr(token, "green") && id > greenMax) {
            greenMax = id;
        }
        token = strtok_r(NULL, delim, &savePtr);
    }

    return redMax * blueMax * greenMax;
}