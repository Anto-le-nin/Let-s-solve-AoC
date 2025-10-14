/* Advent of Code - Day 4 | Antonin Censier */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define FILENAME "data.txt"

/* Structure adaptée au problème */
typedef struct{
    char **tab;    // Tableau 2D
    int nb_rows;   // Nombre de lignes
    int nb_cols;   // Nombre de colonnes
} Grille;


Grille *get_data();
bool detect_Xmas(char *mot);
bool ligne(Grille *g, int i, int j);
bool col(Grille *g, int i, int j);
bool diag1(Grille *g, int i, int j);
bool diag2(Grille *g, int i, int j);
bool x_shape(Grille *g, int i, int j);


int main() {
    Grille *g = get_data();

    // -- Partie 1
    int compt = 0;

    for(int i = 0; i < g->nb_rows; i++){
        for(int j = 0; j < g->nb_cols; j++){
            if(j <= g-> nb_cols-4) {
                if(ligne(g, i, j)) compt++;
            }
            if(i <= g->nb_rows-4) {
                if(col(g, i, j)) compt++;
            }
            if(j <= g->nb_cols-4 && i <= g->nb_rows-4) {
                if(diag1(g,i,j)) compt++;
            }
            if(j >= 3 && i <= g->nb_rows-4) {
                if(diag2(g,i,j)) compt++;
            }
        }
    }
    printf("\nNombre de XMAS : %d\n\n", compt);

    // -- Partie 2
    compt = 0;
    for(int i = 1; i < g->nb_rows-1; i++) {
        for(int j = 1; j < g->nb_cols-1; j++) {
            if(x_shape(g,i,j)) compt++;
        }
    }
    printf("\nNombre de X-shape MAS : %d\n\n", compt);

    for (int i = 0; i < g->nb_rows; i++) {
        free(g->tab[i]);
    }
    free(g->tab);
    free(g);
}

/*
* Retourne si le mot en argument est XMAS ou SAMX.
*/
bool detect_Xmas(char *mot){
    return strcmp("XMAS", mot) == 0 || strcmp("SAMX", mot) == 0;
}

/*
* Ensemble de fonctions qui detectent la recherche aboutit dans les directions respectives.
* Les directions privilégiées sont DROITE et BAS, sauf pour la diagonale BAS/GAUCHE.
* Chaque fonction prend en argument la grille et la position à tester.
*/
bool ligne(Grille *g, int i, int j){
    char ligne[5];
    for(int k = 0; k < 4; k++){
        ligne[k] = g->tab[i][j+k];
    }
    ligne[4] = '\0';
    return detect_Xmas(ligne);
}

bool col(Grille *g, int i, int j){
    char col[5];
    for(int k = 0; k < 4; k++){
        col[k] = g->tab[i+k][j];
    }
    col[4] = '\0';
    return detect_Xmas(col);
}

bool diag1(Grille *g, int i, int j){
    char diag[5];
    for (int k = 0; k < 4; k++){
        diag[k] = g->tab[i + k][j + k];
    }
    diag[4] = '\0';
    return detect_Xmas(diag);
}

bool diag2(Grille *g, int i, int j){
    char diag[5];
    for (int k = 0; k < 4; k++){
        diag[k] = g->tab[i + k][j - k];
    }
    diag[4] = '\0';
    return detect_Xmas(diag);
}

/*
* Retourne si le pattern en X avec MAS est dectecté.
* Prend en argument la grille et la position à tester.
*/
bool x_shape(Grille *g, int i, int j) {
    char a = g->tab[i-1][j-1];
    char b = g->tab[i-1][j+1];
    char c = g->tab[i+1][j-1];
    char d = g->tab[i+1][j+1];

    if (g->tab[i][j] != 'A')
        return false;

    // Les 4 motifs valides
    if ((a == 'M' && b == 'S' && c == 'M' && d == 'S') ||
        (a == 'M' && b == 'M' && c == 'S' && d == 'S') ||
        (a == 'S' && b == 'S' && c == 'M' && d == 'M') ||
        (a == 'S' && b == 'M' && c == 'S' && d == 'M'))
        return true;

    return false;
}

/* 
* Renvoie la grille avec les données de FILENAME, NULL si erreurs.
*/
Grille *get_data() {
    FILE *f = fopen(FILENAME, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    // récupère le nombre de lignes et colonnes
    int nb_rows = 0;
    int nb_cols = 0;
    int cols_temp = 0;
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            nb_rows++;
            if (cols_temp > nb_cols) nb_cols = cols_temp;
            cols_temp = 0;
        } else {
            cols_temp++;
        }
    }
    if (cols_temp > 0) nb_rows++;

    rewind(f);
    Grille *g = malloc(sizeof(Grille));
    g->nb_rows = nb_rows;
    g->nb_cols = nb_cols;
    g->tab = malloc(nb_rows * sizeof(char *));

    for (int i = 0; i < nb_rows; i++) {
        g->tab[i] = malloc((nb_cols + 1) * sizeof(char)); // +1 pour '\0'

        // Lit une ligne
        if (fgets(g->tab[i], nb_cols + 2, f) == NULL) {
            // Si ligne vide, remplit d'espaces
            for (int j = 0; j < nb_cols; j++) g->tab[i][j] = ' ';
            g->tab[i][nb_cols] = '\0';
        } else {
            // Supprime '\n' éventuel
            for (int j = 0; j < nb_cols; j++) {
                if (g->tab[i][j] == '\n' || g->tab[i][j] == '\0') {
                    g->tab[i][j] = '\0';
                    break;
                }
            }
        }
    }

    fclose(f);
    return g;
}