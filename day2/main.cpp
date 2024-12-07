#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

bool comp(int a, int b){
    return a > b;
}

int isReportSafe(vector<int> report){
    //STEP 3: Determine decreasing or increasing order
    if(!is_sorted(report.begin(), report.end()) &&
    !is_sorted(report.begin(), report.end(), comp)){
        return 0;
    }
    //STEP 4: Look for difference of at least one and at most three
    for(int i = 1; i<report.size(); i++){
        if(abs(report.at(i)-report.at(i-1)) > 3 || report.at(i) == report.at(i-1)){
            return 0;
        }
    }
    return 1;
}

int isReportAlmostSafe(vector<int> report){
    if(isReportSafe(report) != 0)
        return 1;

    for(int i = 0; i < report.size(); i++){
        int temp = report.at(i);
        report.erase(report.begin() + i);
        if(isReportSafe(report))
            return 1;
        report.insert(report.begin()+ i, temp);
    }

    return 0;

}

auto main(int argc, char *argv[]) -> int {
    string inputFile = "puzzleInput.txt";
    int successReports = 0; //Part 1 answer
    int almostSuccessReports = 0; //Part 2 answer

    // STEP 1: Getting one line (report) from the file
    ifstream f(inputFile);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    // String variable to store the read data
    string s;
    //Get report from line
    vector<int> report;
    while (getline(f, s)){
        istringstream iss(s);
        int n;
        while(iss >> n){
            report.push_back(n);
        }
        //STEP 2: Reading the report
        successReports += isReportSafe(report);
        almostSuccessReports += isReportAlmostSafe(report);
        report.clear();
    }

    //STEP 5: Print results
    cout << successReports << endl;
    cout << almostSuccessReports << endl;

   // Close the file
    f.close();


}
