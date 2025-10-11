#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int **tab;
    int rows; 
    int *nb_cols;
} tableau_2D;
// int get_data(){

// }

// 
bool test_ligne(int *ligne, int nb_value){
    if(nb_value == 1){
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

int get_nb_right_line(tableau_2D *t){

    int nb_right_rows = 0;

    for(int i = 0; i < t->rows; i++){

        if (test_ligne(t->tab[i], t->nb_cols[i])){
            nb_right_rows++;
        }

    }
    return nb_right_rows;
}

int get_nb_right_line_flex(tableau_2D *t){

    int nb_right_rows = 0;

    for(int i = 0; i < t->rows; i++){

        if (test_ligne(t->tab[i], t->nb_cols[i])){
            nb_right_rows++;
        }
        else{
            for(int j = 0; j < t->nb_cols[i]; j++){
                // Créer une nouvelle ligne sans l'élément j
                int new_len = t->nb_cols[i] - 1;
                int *new_line = malloc(new_len * sizeof(int));
                if (!new_line) {
                    perror("Erreur malloc new_line");
                    exit(1);
                }

                // Copier tout sauf l'élément j
                for (int k = 0, idx = 0; k < t->nb_cols[i]; k++) {
                    if (k == j) continue;  // saute l'élément à retirer
                    new_line[idx++] = t->tab[i][k];
                }

                //test de la ligne
                if(test_ligne(new_line, t->nb_cols[i] - 1)){
                    free(new_line);
                    nb_right_rows++;
                    break;
                }
            }
        }

    }
    return nb_right_rows;
}

int main() {
    FILE *f = fopen("data.txt", "r");
    if (!f) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    tableau_2D t;
    t.tab = NULL;  // tableau 2D
    t.nb_cols = NULL;  // nombre de valeurs par ligne
    t.rows = 0;      // nombre de lignes

    char buffer[1024];  // pour lire une ligne complète

    while (fgets(buffer, sizeof(buffer), f)) {
        int *ligne = NULL;
        int n = 0;
        int val;
        char *ptr = buffer;

        // Lire tous les entiers de la ligne
        while (sscanf(ptr, "%d", &val) == 1) {
            int *tmp = realloc(ligne, (n + 1) * sizeof(int));
            if (!tmp) {
                perror("Erreur realloc ligne");
                free(ligne);
                fclose(f);
                return 1;
            }
            ligne = tmp;
            ligne[n++] = val;

            // avancer le pointeur dans la ligne
            while (*ptr != ' ' && *ptr != '\t' && *ptr != '\n' && *ptr != '\0')
                ptr++;
            while (*ptr == ' ' || *ptr == '\t')
                ptr++;
        }

        // Ajouter cette ligne au tableau 2D
        int **tmp_tab = realloc(t.tab, (t.rows + 1) * sizeof(int *));
        int *tmp_cols = realloc(t.nb_cols, (t.rows + 1) * sizeof(int));
        if (!tmp_tab || !tmp_cols) {
            perror("Erreur realloc tableau principal");
            free(ligne);
            fclose(f);
            return 1;
        }
        t.tab = tmp_tab;
        t.nb_cols = tmp_cols;
        t.tab[t.rows] = ligne;
        t.nb_cols[t.rows] = n;
        t.rows++;
    }

    fclose(f);

    int nb_right = get_nb_right_line(&t);

    printf("\nLe nombre de bonne ligne est de %d\n", nb_right);

    int nb_right_flex = get_nb_right_line_flex(&t);

    printf("\nAvec 1 de souplesse le nombre de bonne ligne est de %d\n", nb_right_flex);
    
    for (int i = 0; i < t.rows; i++) {
        free(t.tab[i]);
    }
    free(t.tab);
    free(t.nb_cols);

    return 0;

}
