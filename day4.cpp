// Author: Sean O'Dea
// Date: 1/1/2024
// https://adventofcode.com/2023/day/4
// Day 4: Scratchcards

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include <math.h>
#include <queue>
#include <chrono>

using namespace std;

string *readInput(string path, int *total);
int cardPoints(string card);
double score(set<int> *winning, vector<int> *actual);
int totalCards(string *cards, int numCards);
int cardPoints2(string card);
double score2(set<int> *winning, vector<int> *actual);

int main() {
    auto start = chrono::high_resolution_clock::now();

    int numLines;
    string *lines = readInput("./inputs/DONE/day4.txt", &numLines); 

    int sum = 0;
    for (int i = 0; i < numLines; i++) {
        sum += cardPoints(lines[i]);
        //cout << cardPoints(lines[i]) << " ";
    }
    //sum += totalCards(lines, numLines);
    cout << "SUM - " << sum << endl;
    
    delete[] lines;

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

int cardPoints(string card) {
    set<int> *winning = new set<int>;
    vector<int> *actual = new vector<int>;

    int i = 0;
    while (card[i] != ':') i++;
    i+=2; // move to beginning of first number
    while (card[i] != '|') {
        winning->insert(atoi(&card[i]));
        i += 3; // jump to next number
    }
    i+=2; // beginning of second section numbers
    while (i < card.size()) {
        actual->push_back(atoi(&card[i]));
        i += 3; // jump to next number
    }

    int total = score(winning, actual);
    delete winning;
    delete actual;
    return total;
}

double score(set<int> *winning, vector<int> *actual) {
    int count = 0;
    for (int x : *actual) {
        if (winning->find(x) != winning->end()) {
            count++;
        }
    }
    if (count < 1) return 0;
    return pow(2, count-1);
}

/*--------------Part 2---------------*/
int totalCards(string *lines, int numLines) {
    queue<int> toCheck;
    int seenScores[numLines]; // array-based tracking of already-seen scores for efficiency
    
    int total = 0;
    for (int i = 0; i < numLines; i++) {
        toCheck.push(i); // starting cards
        seenScores[i] = -1; // default for non-seen cards
    }

    while (!(toCheck.empty())) {
        int current = toCheck.front();
        toCheck.pop();
        total++;
        int numWon;
        if (seenScores[current] == -1) {
            int score = cardPoints2(lines[current]);
            numWon = score;
            seenScores[current] = score;
        } else {
            numWon = seenScores[current];
        }
        for (int i = 1; i <= numWon; i++) {
            //cout << current+i << " ";
            toCheck.push(current+i);
        }
    }
    return total;
}

int cardPoints2(string card) {
    set<int> *winning = new set<int>;
    vector<int> *actual = new vector<int>;

    int i = 0;
    while (card[i] != ':') i++;
    i+=2; // move to beginning of first number
    while (card[i] != '|') {
        winning->insert(atoi(&card[i]));
        i += 3; // jump to next number
    }
    i+=2; // beginning of second section numbers
    while (i < card.size()) {
        actual->push_back(atoi(&card[i]));
        i += 3; // jump to next number
    }

    int total = score2(winning, actual);
    delete winning;
    delete actual;
    return total;
}

double score2(set<int> *winning, vector<int> *actual) {
    int count = 0;
    for (int x : *actual) {
        if (winning->find(x) != winning->end()) {
            count++;
        }
    }
    return count;
}