/* Advent of Code - Day 1 | Antonin Censier */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

void get_data(std::vector<int> &t){
    std::ifstream file;
    file.open("data.txt");

    std::string line;

    while(std::getline(file, line)){        
        std::istringstream line_stream(line);
        char c;
        int n;
        line_stream >> c >> n;

        if(c == 'L'){
            n = -n;
        }

        t.push_back(n);
    }
}

int nb_zeros(std::vector<int> &t){
    int count = 50;
    int nb_zeros = 0;
    for(int& n : t){
        count += n;
        count = (count % 100 + 100) % 100;

        if(count == 0){
            nb_zeros++;
        }
    }
    return nb_zeros;
}

int nb_zeros_2(std::vector<int> &t){
    int count = 50;
    int nb_zeros = 0;
    for(int& n : t){
        count += n;
        if(count < 0 || count > 100){
            nb_zeros ++;
        }
        count = (count % 100 + 100) % 100;

        if(count == 0){
            nb_zeros++;
        }
    }
    return nb_zeros;
}

int main(){
    std::vector<int> tab;
    get_data(tab);
    std::cout<<"nombre de zeros : "<<nb_zeros(tab)<<std::endl;
    std::cout<<"nombre de zeros (avec traversée) : "<<nb_zeros_2(tab)<<std::endl;
}