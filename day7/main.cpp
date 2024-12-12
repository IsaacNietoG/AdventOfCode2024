#include <iostream>
#include <regex>
#include <fstream>
#include <string>
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
    std::smatch match = *digits_begin++;
    int number = std::stoi(match.str());
    returnable.result = number;

    //Get operands (rest of the integers)
    for(std::sregex_iterator i = digits_begin; i!= digits_end; i++){
        std::smatch match = *i;
        int number = std::stoi(match.str());
        returnable.operands.push_back(number);
    }

    return returnable;
}

bool evaluate(std::vector<int> &operands, int result, int index, int current){
    //Base case
    if(index == operands.size())
        return current == result;

    if(evaluate(operands, result, index+1, current + operands[index])){
        return true;
    }

    if(evaluate(operands, result, index+1, current * operands[index])){
        return true;
    }

    return false;
}

bool isEquationViable(Equation &equation){
    if(equation.operands.empty())
        return false;

    return evaluate(equation.operands, equation.result, 1, equation.operands[0]);
}
