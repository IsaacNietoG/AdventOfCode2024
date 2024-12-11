#include <iostream>
#include <vector>
#include <fstream>

int stepsTaken = 1;

std::pair<int, int> buildLab(std::string &input, std::vector<std::vector<char>> &playground);
bool isObstacleInFront(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground);
void rotateGuardRight(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground);
void takeFrontStep(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground);
bool isInBounds(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground);
void printMatrix(std::vector<std::vector<char>> &matrix);

auto main(int argc, char *argv[]) -> int {
    std::string input = "puzzleInput.txt";

    std::vector<std::vector<char>> playground(130, std::vector<char>(130, 0));

    std::pair<int,int> guardCoords = buildLab(input, playground);

    printMatrix(playground);

    while(isInBounds(guardCoords, playground)){
        if(isObstacleInFront(guardCoords, playground)){
            rotateGuardRight(guardCoords, playground);
        }
        takeFrontStep(guardCoords, playground);
    }

    std::cout << "Finished:" << std::endl;
    printMatrix(playground);

    std::cout << stepsTaken << std::endl;

    return 0;
}

bool isInBounds(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground){
    return guardCoords.first >= 0 && guardCoords.first < playground.size() &&
        guardCoords.second >= 0 && guardCoords.second < playground[guardCoords.first].size();
}

void printMatrix(std::vector<std::vector<char>> &matrix){
    for(std::vector<char> line : matrix){
        for(char c: line){
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

std::pair<int, int> buildLab(std::string &input, std::vector<std::vector<char>> &playground){
    std::pair<int, int> guardCoords;

    std::ifstream f(input);
    // Check if the file is successfully opened
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
    }

    //Dump to 2D Array
    std::string s;
    int i = 0;
    int j = 0;
    while(getline(f,s)){
        j = 0;
        for(char s : s){
            if(s == '^' || s == 'v' || s == '>' || s == '<'){
                //Guard found
                guardCoords.first = i;
                guardCoords.second = j;
            }
            playground[i][j++] = s;
        }
        i++;
    }
    f.close();

    return guardCoords;
}

bool isObstacleInFront(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground){
    char guard = playground[guardCoords.first][guardCoords.second];

    switch(guard){
        case '>':
            if(guardCoords.second+1 < playground[guardCoords.first].size())
                return playground[guardCoords.first][guardCoords.second+1] == '#';
            break;
        case '<':
            if(guardCoords.second-1 >= 0)
                return playground[guardCoords.first][guardCoords.second-1] == '#';
            break;
        case '^':
            if(guardCoords.first-1 >= 0)
                return playground[guardCoords.first-1][guardCoords.second] == '#';
            break;
        case 'v':
            if(guardCoords.first+1 < playground.size())
                return playground[guardCoords.first+1][guardCoords.second] == '#';
            break;
        default:
            return false;
    }

    return false;
}

void rotateGuardRight(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground){
    // Yeah i know I could get fancier solutions with a pointer but I'm sleepy
    char guard = playground[guardCoords.first][guardCoords.second];

    switch(guard){
        case '>':
            playground[guardCoords.first][guardCoords.second] = 'v';
            break;
        case '<':
            playground[guardCoords.first][guardCoords.second] = '^';
            break;
        case '^':
            playground[guardCoords.first][guardCoords.second] = '>';
            break;
        case 'v':
            playground[guardCoords.first][guardCoords.second] = '<';
            break;
    }

}

void markVisitedLocation(std::pair<int, int> visitedCoords, std::vector<std::vector<char>> &playground){
    if(playground[visitedCoords.first][visitedCoords.second] == 'X')
        return;

    stepsTaken++;


}

void takeFrontStep(std::pair<int, int> &guardCoords, std::vector<std::vector<char>> &playground){
    char guard = playground[guardCoords.first][guardCoords.second];

    switch(guard){
        case '>':
            playground[guardCoords.first][guardCoords.second] = 'X';
            guardCoords.second++;
            if(guardCoords.second < playground[guardCoords.first].size()){
                markVisitedLocation(guardCoords, playground);
                playground[guardCoords.first][guardCoords.second] = '>';
            }
            break;
        case '<':
            playground[guardCoords.first][guardCoords.second] = 'X';
            guardCoords.second--;
            if(guardCoords.second >= 0){
                markVisitedLocation(guardCoords, playground);
                playground[guardCoords.first][guardCoords.second] = '<';
            }
            break;
        case '^':
            playground[guardCoords.first][guardCoords.second] = 'X';
            guardCoords.first--;
            if(guardCoords.first >= 0){
                markVisitedLocation(guardCoords, playground);
                playground[guardCoords.first][guardCoords.second] = '^';
            }
            break;
        case 'v':
            playground[guardCoords.first][guardCoords.second] = 'X';
            guardCoords.first++;
            if(guardCoords.first < playground.size()){
                markVisitedLocation(guardCoords, playground);
                playground[guardCoords.first][guardCoords.second] = 'v';
            }
            break;
    }


}
