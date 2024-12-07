#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

auto main(int argc, char *argv[]) -> int {
    string inputFile = "puzzleInput.txt";

    // STEP 1: Reading two arrays[1000] from the input
    ifstream f(inputFile);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    // String variable to store the read data
    string s;
    //Split into each array
    vector<int> array1;
    vector<int> array2;
    int temp1;
    int temp2;
    while (getline(f, s)){
        istringstream iss(s);
        if(iss >> temp1 >> temp2){
            array1.push_back(temp1);
            array2.push_back(temp2);
        }
    }

   // Close the file
    f.close();

    //STEP 2: Sort the arrays in ascending order.
    sort(array1.begin(), array1.end());
    sort(array2.begin(), array2.end());

    //STEP 3: Sum the differences. This gets us part 1 response
    int part1 = 0;
    for(int i = 0; i < array1.size(); i++){
       part1 += abs(array1.at(i) - array2.at(i));
    }
    cout << part1;

    //STEP 4: Get similarity score

    int part2 = 0;

    for(int i = 0; i < array1.size(); i++){
        for(int j = 0; i < array1.size(); j++){
            if(array2.at(j) > array1.at(i)){
                break;
            }

            if(array1.at(i) == array2.at(j)){
               part2 += array1.at(i);
            }

        }
    }
    cout << "Part 2:";
    cout << part2 << endl;

    return 0;
}
