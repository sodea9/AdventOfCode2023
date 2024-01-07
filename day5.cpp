// Author: Sean O'Dea
// Date: 1/2/2024
// https://adventofcode.com/2023/day/5
// Day 5: If You Give A Seed A Fertilizer

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string.h>
#include <chrono>

using namespace std;

string *readInput(string path, int *total);
vector<int64_t> *getSeeds(string seedStr);
vector<tuple<int64_t,int64_t,int64_t>> *linesToMap(string *linesStart);
int64_t seedsToMinLocation(vector<int64_t> *seeds, vector<tuple<int64_t,int64_t,int64_t>> *_1, vector<tuple<int64_t,int64_t,int64_t>> *_2, vector<tuple<int64_t,int64_t,int64_t>> *_3, vector<tuple<int64_t,int64_t,int64_t>> *_4, vector<tuple<int64_t,int64_t,int64_t>> *_5, vector<tuple<int64_t,int64_t,int64_t>> *_6, vector<tuple<int64_t,int64_t,int64_t>> *_7);
int64_t seedToLocation(int64_t seed, vector<tuple<int64_t,int64_t,int64_t>> *_1, vector<tuple<int64_t,int64_t,int64_t>> *_2, vector<tuple<int64_t,int64_t,int64_t>> *_3, vector<tuple<int64_t,int64_t,int64_t>> *_4, vector<tuple<int64_t,int64_t,int64_t>> *_5, vector<tuple<int64_t,int64_t,int64_t>> *_6, vector<tuple<int64_t,int64_t,int64_t>> *_7);
int64_t sourceToDest(int64_t source, vector<tuple<int64_t,int64_t,int64_t>> *map);

int main() {
    auto start = chrono::high_resolution_clock::now();

    int totalLines;
    string *lines = readInput("./inputs/day5a.txt", &totalLines);
    vector<int64_t> *seeds = getSeeds(lines[0]);
    
    int i = 3;
    vector<tuple<int64_t,int64_t,int64_t>> *sts = linesToMap(&lines[i]);
    while (lines[i][0] != 's') i++;
    vector<tuple<int64_t,int64_t,int64_t>> *stf = linesToMap(&lines[++i]);
    while (lines[i][0] != 'f') i++;
    vector<tuple<int64_t,int64_t,int64_t>> *ftw = linesToMap(&lines[++i]);
    while (lines[i][0] != 'w') i++;
    vector<tuple<int64_t,int64_t,int64_t>> *wtl = linesToMap(&lines[++i]);
    while (lines[i][0] != 'l') i++;
    vector<tuple<int64_t,int64_t,int64_t>> *ltt = linesToMap(&lines[++i]);
    while (lines[i][0] != 't') i++;
    vector<tuple<int64_t,int64_t,int64_t>> *tth = linesToMap(&lines[++i]);
    while (lines[i][0] != 'h') i++;
    vector<tuple<int64_t,int64_t,int64_t>> *htl = linesToMap(&lines[++i]);

    int64_t closest = seedsToMinLocation(seeds, sts, stf, ftw, wtl, ltt, tth, htl);
    cout << "Min Location - " << closest << endl;

    delete[] lines;
    delete seeds;
    sts->clear(); delete sts;
    stf->clear(); delete stf;
    ftw->clear(); delete ftw;
    wtl->clear(); delete wtl;
    ltt->clear(); delete ltt;
    tth->clear(); delete tth;
    htl->clear(); delete htl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    if (duration >= 1000) {
        double seconds = duration;
        seconds /= 1000;
        cout << "Solved in " << seconds << " s" << endl;
    } else {
        cout << "Solved in " << duration << " ms" << endl;
    }
    return 0;
}

string *readInput(string path, int *total) {
    fstream input;
    input.open(path, ios::in);
    string *lines = new string[512];
    string curLine;
    *total = 0;
    if (!(input.is_open())) {
        cout << "Input not found" << endl;
        exit(1);
    }

    while (getline(input, curLine)) {
        lines[*total] = curLine;
        (*total)++;
    }
    return lines;
}

vector<int64_t> *getSeeds(string seedStr) {
    vector<int64_t> *seeds = new vector<int64_t>();

    char *array = &seedStr[7];
    const char delim[] = ": ";
    char *token = strtok(array, delim);
    while (token != NULL) {
        seeds->push_back(atoi(token));
        token = strtok(NULL, delim);
    }
    return seeds;
}

/// @brief converts strings containing values and ranges into a map
/// @param lines pointer to first string containing numbers of given section in the input
/// @return pointer to a map containing source and destination pairs
vector<tuple<int64_t,int64_t,int64_t>> *linesToMap(string *firstLine) {
    int64_t i = 0;
    vector<tuple<int64_t,int64_t,int64_t>> *_map = new vector<tuple<int64_t,int64_t,int64_t>>();
    while (!(firstLine[i].empty())) {
        const char delim[] = " ";
        int64_t destStart = atoll(strtok(&firstLine[i][0], delim));
        int64_t sourceStart = atoll(strtok(NULL, delim));
        int64_t range = atoll(strtok(NULL, delim));
        _map->push_back({sourceStart, destStart, range});
        i++;
    }
    return _map;
}

int64_t seedsToMinLocation(vector<int64_t> *seeds, vector<tuple<int64_t,int64_t,int64_t>> *_1, vector<tuple<int64_t,int64_t,int64_t>> *_2, vector<tuple<int64_t,int64_t,int64_t>> *_3, vector<tuple<int64_t,int64_t,int64_t>> *_4, vector<tuple<int64_t,int64_t,int64_t>> *_5, vector<tuple<int64_t,int64_t,int64_t>> *_6, vector<tuple<int64_t,int64_t,int64_t>> *_7) {
    int64_t minLocation = LONG_LONG_MAX;
    for (int64_t s : *seeds) {
        int64_t loc = seedToLocation(s, _1, _2, _3, _4, _5, _6, _7);
        if (loc < minLocation) minLocation = loc;
    }
    return minLocation;
}

int64_t seedToLocation(int64_t seed, vector<tuple<int64_t,int64_t,int64_t>> *_1, vector<tuple<int64_t,int64_t,int64_t>> *_2, vector<tuple<int64_t,int64_t,int64_t>> *_3, vector<tuple<int64_t,int64_t,int64_t>> *_4, vector<tuple<int64_t,int64_t,int64_t>> *_5, vector<tuple<int64_t,int64_t,int64_t>> *_6, vector<tuple<int64_t,int64_t,int64_t>> *_7) {
    int64_t loc = seed;         
    loc = sourceToDest(loc, _1);
    loc = sourceToDest(loc, _2);
    loc = sourceToDest(loc, _3);
    loc = sourceToDest(loc, _4);
    loc = sourceToDest(loc, _5);
    loc = sourceToDest(loc, _6);
    loc = sourceToDest(loc, _7);
    return loc;
}

int64_t sourceToDest(int64_t source, vector<tuple<int64_t,int64_t,int64_t>> *map) {
    for (auto x : *map) {
        int64_t sourceStart, destStart, range;
        tie(sourceStart, destStart, range) = x;
        if (source >= sourceStart && source < sourceStart+range) {
            int64_t dest = destStart + (source - sourceStart);
            return dest;
        }
    }
    return source;
}