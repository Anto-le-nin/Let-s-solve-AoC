/* Advent of Code - Day 5 | Antonin Censier */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>

bool contains(std::vector<std::vector<long>> &fresh_table, long &number){
    for(auto &v : fresh_table){
        if(v[0] <= number && v[1] >= number){
            return true;
        }
    }
    return false;
}

int part_one(){

    std::ifstream file;
    file.open("data.txt");

    std::string line;
    std::vector<std::vector<long>> fresh;
    std::vector<long> numbers;

    int count = 0;
    bool fill_numbers_alone = false;
    while(std::getline(file, line)) {
        if(line.empty()){
            fill_numbers_alone = true;
            continue;
        }

        std::istringstream line_stream(line); 
        if(!fill_numbers_alone){
            long min, max;
            char tiret;
            line_stream>>min>>tiret>>max;
            fresh.push_back({min, max});
            //std::cout<<min<<tiret<<max<<std::endl;
        }
        else{

            long number;

            line_stream>>number;
            numbers.push_back(number);
            //std::cout<<number<<std::endl;

            if(contains(fresh, number)){
                count++;
            }
        }   
    }

    return count;
}

long extend(std::vector<std::vector<long>> &fresh_table, long min, long max){

}


int part_two(){

    std::ifstream file;
    file.open("data.txt");

    std::string line;
    std::vector<std::vector<long>> fresh;

    int count = 0;

    long summ = 0;
    while(std::getline(file, line)) {

        std::istringstream line_stream(line); 

        long min, max;
        char tiret;
        line_stream>>min>>tiret>>max;

        for(auto v : fresh){
            if(v[0] <= min && v[1] >= max){ // englobé
                break;
            }
            else if(v[0] <= min && v[1] >= min){
                max = v[1];
                //supp v
            }
            else if(v[1] <= max && v[0] <= min){
                min = v[0];
                //supp v 
            }
            // je fais un test gti
            fresh.push_back({min, max});
        }

    }

    return count;
}


int main(){
    int res1 = part_one();
    std::cout<<"resultat 1 : "<< res1 <<std::endl;
    return 1;
}