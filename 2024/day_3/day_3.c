/* Advent of Code - Day 3 | Antonin Censier */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FILENAME "data.txt"

bool detect_mot(char buffer[7], char *mot, int indice);
int get_somme(FILE *f);
int get_somme_enable(FILE *f);


int main() {
    FILE *f = fopen(FILENAME, "r");
    if (!f) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    // -- Partie 1
    int somme = get_somme(f);
    printf("Somme totale : %d\n", somme);
    
    rewind(f);
    f = fopen(FILENAME, "r");
    if (!f) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    // -- Partie 2
    somme = get_somme_enable(f);    
    printf("Somme totale : %d\n", somme);

    fclose(f);
    return 0;
}


/*
* Détecte la présence d’un mot dans un buffer circulaire de 7 caractères.
* Prend en argument le buffer, le mot à rechercher et l’indice du dernier caractère lu.
*/
bool detect_mot(char buffer[7], char *mot, int indice) {
    // Indice où commence le mot
    int i0 = (indice - (int)strlen(mot) + 7) % 7;

    for(int i = 0; mot[i] != '\0' ; i++) {
        if(buffer[(i0 + i) % 7] != mot[i]) {
            return false;
        }
    }

    return true;
}

/*
* Retourne la somme des mul(a,b) présents.
* Prend en argument le fichier que le programme va parcourir.
*/
int get_somme(FILE *f) {
    int somme = 0;
    char caracter;
    char buffer[7] = {0}; // Pour détecter "don't()"
    int indice = 0;

    while ((caracter = fgetc(f)) != EOF) {

        buffer[indice % 7] = caracter;
        indice++;

        if (indice >= 4 && detect_mot(buffer, "mul(", indice)) {

            int a = 0, b = 0;
            int ok = 1;

            // Premier nombre
            if (fscanf(f, "%3d", &a) != 1) {
                ok = 0; 
                continue;
            }

            // Virgule
            caracter = fgetc(f);
            if (caracter != ',') { 
                ok = 0; 
                continue;
            }

            // Deuxième nombre
            if (fscanf(f, "%3d", &b) != 1) { 
                ok = 0; 
                continue; 
            }

            // Parenthèse
            caracter = fgetc(f);
            if (caracter != ')') { 
                ok = 0; 
                continue; 
            }

            if (ok) somme += a * b;
        }
    }
    return somme;
}

/*
* Retourne la somme des mul(a,b) avec enable condition (do() / don't()).
* Prend en argument le fichier que le programme va parcourir.
*/
int get_somme_enable(FILE *f){
    int somme = 0;
    char caracter;
    char buffer[7] = {0}; // Pour détecter jusqu'à "don't()"
    int indice = 0;
    bool enable = true;

    while ((caracter = fgetc(f)) != EOF) {
        buffer[indice % 7] = caracter;
        indice++;

        if (indice >= 7 && detect_mot(buffer, "don't()", indice)) {
            enable = false;
        }
        else if (indice >= 4 && detect_mot(buffer, "do()", indice)) {
            enable = true;
        }
        if (enable && indice >= 4 && detect_mot(buffer, "mul(", indice)) {
            int a = 0, b = 0;
            int ok = 1;

            // Premier nombre
            if (fscanf(f, "%3d", &a) != 1) {
                ok = 0;
                continue;
            }

            // Virugle
            caracter = fgetc(f);
            if (caracter != ',') { 
                ok = 0;
                continue;
            }

            // Deuxième nombre
            if (fscanf(f, "%3d", &b) != 1) { 
                ok = 0;
                continue; 
            }

            // Parenthèse
            caracter = fgetc(f);
            if (caracter != ')') { 
                ok = 0;
                continue; 
            }

            if (ok) somme += a * b;
        }
    }

    return somme;
}

