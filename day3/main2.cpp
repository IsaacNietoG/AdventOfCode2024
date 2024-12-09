#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

auto main(int argc, char *argv[]) -> int {
    //STEP 1: Read input
    string inputFile = "puzzleInput.txt";

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
    regex self_regex("mul\\((-?\\d+),(-?\\d+)\\)|do\\(\\)|don't\\(\\)");
    // Vector for storing matches
    vector<string> matches;
    //Get report from line
    while (getline(f, s)){
        auto coincidences_begin =
            sregex_iterator(s.begin(), s.end(), self_regex);
        auto coincidences_end = sregex_iterator();

        for(sregex_iterator i = coincidences_begin; i != coincidences_end; i++){
            smatch match = *i;
            string match_str = match.str();
            matches.push_back(match_str);
        }
    }

    //Step 3: Print coincidences and, while we're at it, we fabricate the final result
    int result = 0;
    cout << "Found coincidences:" << endl;
    regex int_regex("\\d+");
    int enableMultiplication = 1;
    for(string i : matches){
        cout << i;
        if(i.compare("don't()") == 0){
            enableMultiplication = 0;
            cout << " disabled" << endl;
            continue;
        }
        if(i.compare("do()") == 0){
            enableMultiplication = 1;
            cout << " enabled" << endl;
            continue;
        }

        auto coincidences_begin =
            sregex_iterator(i.begin(), i.end(), int_regex);
        auto coincidences_end = sregex_iterator();

        int subresult = 1;

        for(sregex_iterator n = coincidences_begin; n != coincidences_end; n++){
            smatch match = *n;
            string match_str = match.str();
            cout << match_str << endl;
            subresult *= stoi(match_str);
        }
        subresult *= enableMultiplication;
        cout << subresult << endl;
        result += subresult;

    }

    cout << "Final result 2: " << result << endl;

    f.close();


    return 0;
}
