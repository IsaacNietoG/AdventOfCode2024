#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

auto main(int argc, char *argv[]) -> int {
    //STEP 1: Read input
    string inputFile = "puzzleInput.txt";
    int finalResult = 0;

    // STEP 1: Getting one line from the file
    ifstream f(inputFile);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    //STEP 2: Getting all the coincidences from the file
    // String variable to store the read data
    string s;
    regex self_regex("mul\\((-?\\d+),(-?\\d+)\\)");
    // Vector for storing matches
    vector<string> matches;
    //Get report from line
    while (getline(f, s)){

    }

    f.close();


    return 0;
}
