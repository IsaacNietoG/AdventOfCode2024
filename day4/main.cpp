#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<char>> (&matrix)){
    for(int i = 0; i < matrix.size() ; ++i){
        for(int j = 0; j < matrix[i].size(); ++j){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int searchWord(int row, int column , vector<vector<char>> (&matrix)){
    int founds = 0;

    //Search Horizontal+
    if(column + 3 < matrix[row].size()){
        if(matrix[row][column+1] == 'M' && matrix[row][column+2] == 'A' && matrix[row][column+3] == 'S')
            founds++;
    }

    //Search Horizontal-
    if(column - 3 >= 0){
        if(matrix[row][column-1] == 'M' && matrix[row][column-2] == 'A' && matrix[row][column-3] == 'S')
            founds++;
    }

    //Search Vertical+
    if(row + 3 < matrix.size()){
        if(matrix[row+1][column] == 'M' && matrix[row+2][column] == 'A' && matrix[row+3][column] == 'S')
            founds++;
    }

    //Search Vertical-
    if(row - 3 >= 0){
        if(matrix[row-1][column] == 'M' && matrix[row-2][column] == 'A' && matrix[row-3][column] == 'S')
            founds++;
    }

    //Search diagonal++
    if(row + 3 < matrix.size() && column + 3 < matrix[row].size()){
        if(matrix[row+1][column+1] == 'M' && matrix[row+2][column+2] == 'A' && matrix[row+3][column+3] == 'S')
            founds++;
    }

    //Search diagonal +-
    if(row + 3 < matrix.size() && column - 3 >= 0){
        if(matrix[row+1][column-1] == 'M' && matrix[row+2][column-2] == 'A' && matrix[row+3][column-3] == 'S')
            founds++;
    }

    //Search diagonal -+
    if(row - 3 >= 0 && column + 3 < matrix[row].size()){
        if(matrix[row-1][column+1] == 'M' && matrix[row-2][column+2] == 'A' && matrix[row-3][column+3] == 'S')
            founds++;
    }

    //Search diagonal--
    if(row - 3 >= 0 && column - 3 >= 0){
        if(matrix[row-1][column-1] == 'M' && matrix[row-2][column-2] == 'A' && matrix[row-3][column-3] == 'S')
            founds++;
    }


    return founds;
}

int searchCoincidences(vector<vector<char>> (&matrix)){
    int coincidences = 0;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j] == 'X'){
                coincidences += searchWord(i, j, matrix);
            }
        }
    }

    return coincidences;
}

int searchWord2Mas(int row, int column , vector<vector<char>> (&matrix)){
    int founds = 0;
    bool enoughSpace = row + 1 < matrix.size() && column + 1 < matrix[row].size() && row - 1 >= 0 && column -1 >= 0;
    // All 2Mas cases use the same space, taking the A as a center and displacing all Ms to 4 different positions:
    // M S   M M   S M   S S
    //  A     A     A     A
    // M S   S S   S M   M M
    // Horizontal+
    // Vertical-
    // Horizontal-
    // Vertical+
    // In left-right order

    if(!enoughSpace){
        return 0;
    }

    //Search Horizontal+
    if(matrix[row+1][column+1] == 'S' && matrix[row+1][column-1] == 'S' && matrix[row-1][column+1] == 'M' && matrix[row-1][column-1] == 'M')
        founds++;

    //Search Vertical-
    if(matrix[row+1][column+1] == 'M' && matrix[row+1][column-1] == 'S' && matrix[row-1][column+1] == 'M' && matrix[row-1][column-1] == 'S')
        founds++;

    //Search Horizontal-
    if(matrix[row+1][column+1] == 'M' && matrix[row+1][column-1] == 'M' && matrix[row-1][column+1] == 'S' && matrix[row-1][column-1] == 'S')
        founds++;

    if(matrix[row+1][column+1] == 'S' && matrix[row+1][column-1] == 'M' && matrix[row-1][column+1] == 'S' && matrix[row-1][column-1] == 'M')
        founds++;

    return founds;
}

int search2Mas(vector<vector<char>> (&matrix)){
    int coincidences = 0;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j] == 'A'){
                coincidences += searchWord2Mas(i, j, matrix);
            }
        }
    }

    return coincidences;
}

auto main(int argc, char *argv[]) -> int {
    //STEP 1: Read input
    string inputFile = "puzzleInput2.txt";
    vector<vector<char>> playground(140, vector<char>(140, 0));

    ifstream f(inputFile);
    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    //STEP 2: Dump to 2D array
    string s;
    int i = 0;
    int j = 0;
    while(getline(f,s)){
        j = 0;
        for(char s : s){
            playground[i][j++] = s;
        }
        i++;
    }
    f.close();

    printMatrix(playground);
    int result = searchCoincidences(playground);
    int result2 = search2Mas(playground);

    cout << result << endl;
    cout << result2 << endl;

    return 0;
}
