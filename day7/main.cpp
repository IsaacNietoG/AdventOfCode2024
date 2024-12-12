#include <iostream>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>

struct Equation{
    int result;
    std::vector<int> operands;
};

bool isEquationViable(Equation &equation);
Equation getEquation(std::string &string);

auto main(int argc, char *argv[]) -> int {
    std::string inputFile = "puzzleInput.txt";
    int answer1 = 0;

    //Reading file
    std::ifstream f(inputFile);

    if(!f.is_open()){
        std::cerr << "Error opening the file";
    }

    std::string s;
    while(getline(f,s)){
        Equation equation = getEquation(s);
        if(isEquationViable(equation)){
            answer1 += equation.result;
        }
    }

    f.close();
    std::cout << answer1 << std::endl;
}

Equation getEquation(std::string &string){
    Equation returnable;
    std::regex integer("\\d+");

    auto digits_begin =
        std::sregex_iterator(string.begin(), string.end(), integer);
    auto digits_end = std::sregex_iterator();

    //Get result (first integer)
    returnable.result = stoi((*digits_begin++).str());

    //Get operands (rest of the integers)
    for(std::sregex_iterator i = digits_begin; i!= digits_end; i++){
        std::smatch match = *i;
        int number = stoi(match.str());
        returnable.operands.push_back(number);
    }

    return returnable;
}

bool isEquationViable(Equation &equation){

}
