/* Advent of Code - Day 2 | Antonin Censier */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/* Structure adaptée au problème */
typedef struct {
    int **tab;     // tableau 2D
    int rows;      // nombre de lignes
    int *nb_cols;  // nombre de valeurs par ligne
} Tab;


bool test_ligne(int *ligne, int nb_value);
int get_data(Tab *t);
int get_nb_right_line(Tab *t);
int get_nb_right_line_flex(Tab *t);


int main() {
    Tab t;
    if(get_data(&t) != 1){
        fprintf(stderr, "Erreur lors du chargement des données.\n");
        return 0;
    }

    // -- Partie 1
    int nb_right = get_nb_right_line(&t);
    printf("\nLe nombre de bonne ligne est de %d\n", nb_right);

    // -- Partie 2
    int nb_right_flex = get_nb_right_line_flex(&t);
    printf("\nAvec 1 de souplesse le nombre de bonne ligne est de %d\n", nb_right_flex);
    
    for (int i = 0; i < t.rows; i++) {
        free(t.tab[i]);
    }
    free(t.tab);
    free(t.nb_cols);
    return 0;
}


/* 
* Teste si la ligne est croissante/décroissante avec différence de 1 à 3.
* Prend en argument la ligne et le nombre de valeur dans la ligne.
*/
bool test_ligne(int *ligne, int nb_value) {
    if(nb_value == 1) {
        return true;
    }

    bool croissant;
    int first_diff = ligne[1] - ligne[0];

    if (abs(first_diff) < 1 || abs(first_diff) > 3) return false;
    croissant = first_diff > 0;

    for (int j = 1; j < nb_value; j++) {
        int diff = ligne[j] - ligne[j - 1];
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
        if ((croissant && diff < 0) || (!croissant && diff > 0)) {
            return false;
            break;
        }
    }
    return true;
}

/* 
* Parcourt le tableau et renvoie le nombre de lignes valides.
* Prend en argument le tableau.
*/
int get_nb_right_line(Tab *t) {
    int nb_right_rows = 0;

    for(int i = 0; i < t->rows; i++) {

        if (test_ligne(t->tab[i], t->nb_cols[i])) {
            nb_right_rows++;
        }

    }
    return nb_right_rows;
}

/* 
* Renvoie le nombre de lignes valides avec un nombre de tolérance.
* Prend en argument le tableau.
*/
int get_nb_right_line_flex(Tab *t) {
    int nb_right_rows = 0;

    for(int i = 0; i < t->rows; i++) {

        if (test_ligne(t->tab[i], t->nb_cols[i])) {
            nb_right_rows++;
        }
        else{
            for(int j = 0; j < t->nb_cols[i]; j++) {
                // Crée une nouvelle ligne sans [j]
                int new_len = t->nb_cols[i] - 1;
                int *new_line = malloc(new_len * sizeof(int));
                if (!new_line) {
                    perror("Erreur malloc new_line");
                    exit(1);
                }

                // Copie tout sauf [j]
                for (int k = 0, idx = 0; k < t->nb_cols[i]; k++) {
                    if (k == j) continue;
                    new_line[idx++] = t->tab[i][k];
                }

                // Test de la ligne
                if(test_ligne(new_line, t->nb_cols[i] - 1)) {
                    free(new_line);
                    nb_right_rows++;
                    break;
                }
            }
        }

    }
    return nb_right_rows;
}

/* 
* Initialise le tableau avec les données de FILENAME.
* Prend en argument le tableau et renvoie 1 si pas d'erreurs.
*/
int get_data(Tab *t) {
    FILE *f = fopen("data.txt", "r");
    if (!f) {
        perror("Erreur ouverture fichier");
        return 0;
    }

    t->tab = NULL;
    t->nb_cols = NULL;
    t->rows = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), f)) {
        int *ligne = NULL;
        int n = 0;
        int val;
        char *ptr = buffer;
    
        // Extraire données ligne
        while (sscanf(ptr, "%d", &val) == 1) {
            ligne = realloc(ligne, (n + 1) * sizeof(int));
            ligne[n++] = val;
    
            // Avance le pointeur
            while (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' && *ptr != '\0')
                ptr++;
            while (*ptr == ' ' || *ptr == '\t')
                ptr++;
        }
    
        // Ajoute cette ligne au tableau 2D
        t->tab = realloc(t->tab, (t->rows + 1) * sizeof(int *));
        t->nb_cols = realloc(t->nb_cols, (t->rows + 1) * sizeof(int));
        t->tab[t->rows] = ligne;
        t->nb_cols[t->rows] = n;
        t->rows++;
    }
    
    fclose(f);
    return 1;
}
