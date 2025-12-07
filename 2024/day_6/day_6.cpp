/* Advent of Code - Day 6 | Antonin Censier */
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

class Curseur {
    public : 
        int x, y;
        char direction;
        Curseur(int x, int y) : x(x), y(y){
            std::cout<<"x = "<<x<<"y = "<<y<<std::endl;
            direction = 'h';
        };

        void parcour(std::vector<std::vector<char>>& grille);
        bool outOfBound(std::vector<std::vector<char>>& grille);

};

void Curseur::parcour(std::vector<std::vector<char>>& grille) {
    while (true) {
        // calculer le prochain pas
        int nx = x, ny = y;
        if (direction == 'h') ny--;
        else if (direction == 'd') nx++;
        else if (direction == 'b') ny++;
        else if (direction == 'g') nx--;
    
        // si on sort, stop
        if (ny < 0 || nx < 0 || ny >= (int)grille.size() || nx >= (int)grille[0].size()) {
            grille[y][x] = 'X'; // marque la dernière case encore dans la grille
            break;
        }
    
        // si mur, tourne à droite
        if (grille[ny][nx] == '#') {
            if (direction == 'h') direction = 'd';
            else if (direction == 'd') direction = 'b';
            else if (direction == 'b') direction = 'g';
            else if (direction == 'g') direction = 'h';
        } else {
            grille[y][x] = 'X'; // marque la case actuelle
            x = nx;
            y = ny;
        }
    }
    
}

bool Curseur::outOfBound(std::vector<std::vector<char>>& grille){
    return (y < 0 || x < 0 || y >= grille.size() || x >= grille[0].size());
}

Curseur getGrille(std::vector<std::vector<char>>& grille) {

    std::ifstream file;
    file.open("data.txt");

    std::string line;
    int count_l = 0;

    Curseur cursed(-1, -1);
    int count_c = 0;

    while(std::getline(file, line)){     
        std::vector<char> thisline;

        if(count_c != 0){
            thisline.reserve(count_c);
        }

        for (count_c = 0; count_c < line.size(); ++count_c) {
            char c = line[count_c];
            if (c == '^') {
                cursed = Curseur(count_c, count_l);
            }
            thisline.push_back(c);
        }   

        grille.push_back(thisline);
        count_l++;
    }
    return cursed;
}

void afficheGrille(std::vector<std::vector<char>>& grille){
    for(std::vector<char> l : grille){
        for(char c : l){
            std::cout<<c;
        }
        std::cout<<std::endl;
    }
}

int getX(std::vector<std::vector<char>>& grille){
    int compte = 0;
    for(std::vector<char> l : grille){
        for(char c : l){
            if(c == 'X') compte++;
        }
    }
    return compte;
}

int main() {
    std::vector<std::vector<char>> grille;
    Curseur initPos = getGrille(grille);
    afficheGrille(grille);
    std::cout<< "check the init pos : "<<grille[initPos.y][initPos.x]<<std::endl;
    initPos.parcour(grille);
    afficheGrille(grille);
    int res = getX(grille);
    std::cout<<"Resultat partie 1"<<res<<std::endl;
}