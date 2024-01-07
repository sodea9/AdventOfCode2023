// Author: Sean O'Dea
// Date: 12/31/2023
// https://adventofcode.com/2023/day/3
// Day 3: Gear Ratios

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>

using namespace std;

char *readInput(string path, int *rows, int *columns);
int checkAdjacent(char *array, int rowNum, int colNum, int rows, int columns);
bool isValidPosition(int row, int col, int numRows, int numCols);
bool isSymbol(char character);
int arrayCharsToInt(char *array, int rowNum, int colNum, int columns);
int gearRatio(char *array, int rowNum, int colNum, int rows, int columns);


int main() {
    auto start = chrono::high_resolution_clock::now();
 
    int rows, cols;
    char *schematic = readInput("./inputs/DONE/day3.txt", &rows, &cols);
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char item = schematic[i*cols+j];
            if (isdigit(item)) {
                sum += checkAdjacent(schematic, i, j, rows, cols);
                while (isdigit(schematic[i*cols+j])) j++;
            }
            //if (item == '*') {
            //    //cout << gearRatio(schematic, i, j, rows, cols) << " ";
            //    sum += gearRatio(schematic, i, j, rows, cols);
            //}
        }
    }

    cout << "SUM - " << sum << endl;
    delete[] schematic;
 
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    cout << "Solved in " << duration << " ms" << endl;
 
    return 0;
}

char *readInput(string path, int *rows, int *columns) {
    fstream input;
    input.open(path, ios::in);
    if (!(input.is_open())) {
        cout << "Input not found" << endl;
        exit(1);
    }

    *rows = 0;
    string total = "";
    string temp;
    while (getline(input, temp)) {
        (*rows)++;
        *columns = temp.length();
        total += temp;
    }
    char *array = new char[total.length()+1];
    strcpy(array, total.c_str());

    return array;
}

int checkAdjacent(char *array, int rowNum, int colNum, int rows, int columns) {
    int j = colNum;
    while (isdigit(array[rowNum*columns+j])) {
        //8 adjacent positions
        if ((isValidPosition(rowNum-1, j-1, rows, columns) && isSymbol(array[(rowNum-1)*columns+j-1])) ||
            (isValidPosition(rowNum-1, j, rows, columns)   && isSymbol(array[(rowNum-1)*columns+j]))   ||
            (isValidPosition(rowNum-1, j+1, rows, columns) && isSymbol(array[(rowNum-1)*columns+j+1])) ||
            (isValidPosition(rowNum, j-1, rows, columns)   && isSymbol(array[rowNum*columns+j-1]))     ||
            (isValidPosition(rowNum, j+1, rows, columns)   && isSymbol(array[rowNum*columns+j+1]))     ||
            (isValidPosition(rowNum+1, j-1, rows, columns) && isSymbol(array[(rowNum+1)*columns+j-1])) ||
            (isValidPosition(rowNum+1, j, rows, columns)   && isSymbol(array[(rowNum+1)*columns+j]))   ||
            (isValidPosition(rowNum+1, j+1, rows, columns) && isSymbol(array[(rowNum+1)*columns+j+1]))) {

            return arrayCharsToInt(array, rowNum, colNum, columns);
        }
        j++;
    }
    return 0;
}

bool isValidPosition(int row, int col, int numRows, int numCols) {
    return (0 <= col && col < numCols) && (0 <= row && row < numRows);
}

bool isSymbol(char character) {
    if (isdigit(character) || character == '.') {
        return false;
    }
    return true;
}

int arrayCharsToInt(char *array, int rowNum, int colNum, int columns) {
    int value = 0;
    char item = array[rowNum*columns+colNum];
    while (isdigit(item) && colNum < columns) {
        value = value*10 + item - '0';
        colNum++;
        item = array[rowNum*columns+colNum];
    }
    return value;
}

// Part 2
// (yea this looks disgusting I know)
int gearRatio(char *array, int gearRow, int gearCol, int rows, int columns) {
    vector<tuple<int, int>> coords;
    if (isValidPosition(gearRow, gearCol+1, rows, columns) && isdigit(array[gearRow*columns+gearCol+1])) { //right
        coords.push_back(tuple(gearRow, gearCol+1));
    }
    if (isValidPosition(gearRow, gearCol-1, rows, columns) && isdigit(array[gearRow*columns+gearCol-1])) { //left
        coords.push_back(tuple(gearRow, gearCol-1));
    }
    if (isValidPosition(gearRow-1, gearCol, rows, columns) && isdigit(array[(gearRow-1)*columns+gearCol])) { //top
        coords.push_back(tuple(gearRow-1, gearCol));
    } else {
        if (isValidPosition(gearRow-1, gearCol+1, rows, columns) && isdigit(array[(gearRow-1)*columns+gearCol+1])) { // top right
            coords.push_back(tuple(gearRow-1, gearCol+1));
        }
        if (isValidPosition(gearRow-1, gearCol-1, rows, columns) && isdigit(array[(gearRow-1)*columns+gearCol-1])) { // top left
            coords.push_back(tuple(gearRow-1, gearCol-1));
        }
    }
    if (isValidPosition(gearRow+1, gearCol, rows, columns) && isdigit(array[(gearRow+1)*columns+gearCol])) { //bottom
        coords.push_back(tuple(gearRow+1, gearCol));
    } else {
        if (isValidPosition(gearRow+1, gearCol+1, rows, columns) && isdigit(array[(gearRow+1)*columns+gearCol+1])) { // bottom right
            coords.push_back(tuple(gearRow+1, gearCol+1));
        }
        if (isValidPosition(gearRow+1, gearCol-1, rows, columns) && isdigit(array[(gearRow+1)*columns+gearCol-1])) { // bottom left
            coords.push_back(tuple(gearRow+1, gearCol-1));
        }
    }
    if (coords.size() != 2) return 0;
    int ratio = 1;
    for (auto c : coords) {
        int i, j;
        tie(i, j) = c;
        while (j > 0 && isdigit(array[i*columns+j-1])) j--; //find beginning of number
        ratio *= arrayCharsToInt(array, i, j, columns);
    }
    return ratio;
}

// if two adjacent numbers, is valid
// check cross
// then check corners
// store coordinates of two numbers