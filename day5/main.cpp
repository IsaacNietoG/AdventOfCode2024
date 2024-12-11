#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <regex>

void storeInput(std::string inputfile, std::map<int, std::set<int>> &rules, std::vector<std::vector<int>> &updates);
bool isRight(std::vector<int> &update, std::map<int , std::set<int>> &rules);
int getMiddlePage(std::vector<int> &update);

auto main(int argc, char *argv[]) -> int {
    std::string inputFile = "puzzleInput.txt";
    int firstAnswer = 0;
    std::map<int , std::set<int>> rules;
    std::vector<std::vector<int>> updates;

    //STEP 1: Getting rules and updates
    storeInput(inputFile, rules, updates);

    //STEP 2: For each update, check if they are in right order
    for(std::vector<int> update : updates){
        if(isRight(update, rules)){
            //STEP 3: Get middle page number and add to firstAnswer
            firstAnswer += getMiddlePage(update);
        }
    }

    //Answer display
    std::cout << firstAnswer << std::endl;

    return 0;
}

void addRule(int key, int value, std::map<int, std::set<int>> &rules){
    rules[key].insert(value);
    // I thought it'd be harder lmao
}

void storeInput(std::string inputfile, std::map<int, std::set<int>> &rules, std::vector<std::vector<int>> &updates){
    std::ifstream f(inputfile);
    // Check if the file is successfully opened
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
    }

    std::regex digitRegex("\\d+");
    std::string s;
    //First get the rules
    while(getline(f,s)){
        if(s.length() == 0)
            break;

        auto digits_begin =
            std::sregex_iterator(s.begin(), s.end(), digitRegex);
        auto digits_end = std::sregex_iterator();

        std::smatch match1 = *digits_begin++;
        std::smatch match2 = *digits_begin;
        addRule(stoi(match1.str()), stoi(match2.str()), rules);
    }

    //Then the updates
    while(getline(f,s)){
        std::vector<int> currentUpdate;
        auto digits_begin =
            std::sregex_iterator(s.begin(), s.end(), digitRegex);
        auto digits_end = std::sregex_iterator();

        for(std::sregex_iterator i = digits_begin; i!= digits_end; i++){
            std::smatch match = *i;
            int number = stoi(match.str());
            currentUpdate.push_back(number);
        }
        updates.push_back(currentUpdate);
    }
    f.close();

}

bool isRight(std::vector<int> &update, std::map<int , std::set<int>> &rules){
    for(int i = 1; i < update.size(); i++){
        int currentElement = update[i];
        for(int j = i-1; j >= 0; j--){
            int currentPrevious = update[j];
            auto notFound = rules[currentElement].end();
            auto search = rules[currentElement].find(currentPrevious);
            if(search != notFound){
                return false;
            }
        }
    }

    return true;
}

int getMiddlePage(std::vector<int> &update){
    return update[update.size()/2];
}
