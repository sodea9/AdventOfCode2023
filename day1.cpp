// Author: Sean O'Dea
// Date: 12/26/2023
// https://adventofcode.com/2023/day/1
// Day 1: Trebuchet?!

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <chrono>

using namespace std;

string *readInput(string path, int *total);
int firstDigitA(string str);
int lastDigitA(string str);
int firstDigitB(string str);
int lastDigitB(string str);
bool hasEnding(string const &fullString, string const &ending);

int main() {
    auto start = chrono::high_resolution_clock::now();

    int numLines;
    string *lines = readInput("./inputs/DONE/day1.txt", &numLines); 

    int sum = 0;
    int calVal;
    string curLine;
    for (int i = 0; i < numLines; i++) {
        curLine = lines[i];
        //calVal = firstDigitA(curLine) * 10;
        //calVal += lastDigitA(curLine);
        calVal = firstDigitB(curLine) * 10;
        calVal += lastDigitB(curLine);
        sum += calVal;
        //cout << calVal << endl;
        calVal = 0;
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

//Part 1
int firstDigitA(string str) {
    int val;
    for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i])) {
            return (str[i] - '0');
        }
    }
    return -1;
}

//Part 1
int lastDigitA(string str) {
    for (int i = str.size()-1; i > -1; i--) {
        if (isdigit(str[i])) {
            return (str[i] - '0');
        }
    }
    return -1;
}

//Part 2
int firstDigitB(string str) {
    string currentStr = "";
    for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i])) {
            return (str[i] - '0');
        }
        currentStr += str[i];
        if (hasEnding(currentStr, "one")) return 1;
        else if (hasEnding(currentStr, "two")) return 2;
        else if (hasEnding(currentStr, "three")) return 3;
        else if (hasEnding(currentStr, "four")) return 4;
        else if (hasEnding(currentStr, "five")) return 5;
        else if (hasEnding(currentStr, "six")) return 6;
        else if (hasEnding(currentStr, "seven")) return 7;
        else if (hasEnding(currentStr, "eight")) return 8;
        else if (hasEnding(currentStr, "nine")) return 9;
    }
    return -1;
}

//Part 2
int lastDigitB(string str) {
    string currentStr = "";
    for (int i = str.size()-1; i > -1; i--) {
        if (isdigit(str[i])) {
            return (str[i] - '0');
        }
        currentStr += str[i];
        if (hasEnding(currentStr, "eno")) return 1;
        else if (hasEnding(currentStr, "owt")) return 2;
        else if (hasEnding(currentStr, "eerht")) return 3;
        else if (hasEnding(currentStr, "ruof")) return 4;
        else if (hasEnding(currentStr, "evif")) return 5;
        else if (hasEnding(currentStr, "xis")) return 6;
        else if (hasEnding(currentStr, "neves")) return 7;
        else if (hasEnding(currentStr, "thgie")) return 8;
        else if (hasEnding(currentStr, "enin")) return 9;
    }
    return -1;
}

//Source: https://stackoverflow.com/a/874160
bool hasEnding(string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}