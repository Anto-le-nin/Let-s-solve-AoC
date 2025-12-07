/* Advent of Code - Day 5 | Antonin Censier */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

class Rule{
    public :

        Rule(int v, int first_rule) : value(v){
            numberAbove.clear();
            numberAbove.push_back(first_rule);
            std::cout << "rule added for " << v <<std::endl;
        };

        int value = 0;
        std::vector<int> numberAbove;

        void addRule(int rule){
            numberAbove.push_back(rule);
        }

        bool isValid(int value){
            for(int x : numberAbove){
                if(x == value){
                    return false;
                }
            }
            return true;
        }

};

Rule* findRule(std::vector<Rule>& FullRule, int value) {
    for(Rule& r : FullRule) {
        if(r.value == value) {
            return &r;
        }
    }
    return nullptr;
}

bool fixOrder(std::vector<int>& numbers, std::vector<Rule>& fullRule){
    bool changed = false;
    bool keep_checking = true;
    
    while(keep_checking) {
        keep_checking = false;
        for(size_t i = 0; i < numbers.size(); i++) {
            for(size_t j = 0; j < i; j++) {

                Rule* r = findRule(fullRule, numbers[j]);
                if(r && !r->isValid(numbers[i])) {

                    std::swap(numbers[i], numbers[j]);
                    changed = true;
                    keep_checking = true;
                    break;
                }
            }
            if(keep_checking) break;
        }
    }
    
    return changed;
}

int main() {
    std::vector<Rule> FullRule;

    std::ifstream file;
    file.open("data.txt");

    int a,b;
    char c;

    int nb_numbers = 0;
    int nb_rules = 0;
    std::string line;

    while(std::getline(file, line) && !line.empty()) {
        std::istringstream line_stream(line);
        char c;
        while(line_stream >> a >> c >> b && c == '|') {
            nb_rules ++;
            bool placed = false;

            for(Rule& r : FullRule) {
                if(b == r.value) {
                    r.addRule(a);
                    placed = true;
                    break;
                }
            }
            if(!placed){
                FullRule.emplace_back(b, a);
                nb_numbers++;
            }
        }
    }

    int line_to_decode = 0;
    int sum = 0, sum2 =0, nb_false = 0;

    while(std::getline(file, line)){

        //get the datas
        std::vector<int> numbers;
        std::istringstream line_stream(line);

        int x;
        std::string token;
        while (std::getline(line_stream, token, ',')) {
            if (!token.empty()) {
                x = std::stoi(token);
                numbers.push_back(x);
            }
        }
        
        bool valid = true;
        for(size_t i = 0; i < numbers.size(); i++) {
            for(size_t j = 0; j < i; j++) {
                Rule* r = findRule(FullRule, numbers[j]);
                if (r && !r->isValid(numbers[i])) {
                    valid = false;
                    break;
                }
            }
            if(!valid) break;
        }
        
        if(valid){
            sum += numbers[(numbers.size()/2)];
        } else {
            fixOrder(numbers, FullRule);
            sum2 += numbers[(numbers.size()/2)];
            nb_false++;
        }

        if(!numbers.empty()){
            line_to_decode ++;
        }


    }
    std::cout << "[Partie 1][Info]"<< std::endl;
    std::cout << "there are " << nb_numbers << " numbers"<< std::endl;
    std::cout << "there are " << nb_rules << " rules"<< std::endl;
    std::cout << "there are " << line_to_decode << " lines to decode"<< std::endl;
    std::cout << "[Partie 1][result] "  << " summ = "<< sum << std::endl;
    std::cout << "\n[Partie 2][Info]"<< std::endl;
    std::cout << "there are " << nb_false << " wrong lines"<< std::endl;
    std::cout << "[Partie 2][result] "  << " summ2 = "<< sum2 << std::endl;
    file.close();

}