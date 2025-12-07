/* Advent of Code - Day 2 | Antonin Censier */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>

long part_one(){

    std::ifstream file;
    file.open("data.txt");

    std::string line;

    long result = 0;

    while(std::getline(file, line, ',')) {  

        std::istringstream line_stream(line); 

        long min, max;
        char tiret;
        line_stream>>min>>tiret>>max;

        //std::cout<<min<<tiret<<max<<std::endl;

        for(long i = min; i < max; i++) {
            
            long nb_digits = 1;
            long temp = i;

            while(temp/10 != 0) { 
                temp = temp/10;
                nb_digits++;
            }

            long divisor = 1;
            for (int k = 0; k < nb_digits/2; k++) divisor *= 10;

            if(i%divisor == (i - i%divisor)/divisor) {
                result+=i;
                std::cout<<i%divisor<<"="<<i - i%divisor<<std::endl;
            }
        }
    }
    return result;
}

long part_two(){

    std::ifstream file;
    file.open("data.txt");

    std::string line;

    long result = 0;

    while(std::getline(file, line, ',')) {  

        std::istringstream line_stream(line); 

        long min, max;
        char tiret;
        line_stream>>min>>tiret>>max;

        //std::cout<<min<<tiret<<max<<std::endl;

        for(long i = min; i < max; i++) {
            
            long nb_digits = 1;
            long temp = i;
            
            std::vector<int> digits;
            while(temp/10 != 0) {
                digits.push_back(int(temp%10));
                temp = temp/10;
                nb_digits++;
            }
            digits.push_back(int(temp));
            
            int n = digits.size();

            for(int l = 1; l <= n/2; l++){

                if(n%l != 0) continue;

                bool isPattern = true;

                for (int blockStart = l; blockStart < n; blockStart += l) {
                    for (int j = 0; j < l; j++) {
                        if (digits[blockStart + j] != digits[j]) {
                            isPattern = false;
                            break;
                        }
                    }
                    if (!isPattern)
                        break;
                }

                if (isPattern) {
                    result += i;
                    std::cout << i << std::endl;
                    break;
                }
            }
        }
    }
    return result;
}

int main() {
    long part1 = part_one();
    long part2 = part_two();
    std::cout<<"Resultat :"<<part1<<std::endl;
    std::cout<<"Resultat :"<<part2<<std::endl;
    return 0;
}

