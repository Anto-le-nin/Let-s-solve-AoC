/* Advent of Code - Day 1 | Antonin Censier */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define FILENAME "data.txt"

/* Structure adaptée au problème */
typedef struct {
    int *t1;          // Premier tableau
    int *t2;          // Deuxième tableau
    int n;            // Nombre de valeurs par tableau
    int nb_chiffres;  // Nombre de chiffres maximum
} Tabs;


int nb_digits(int x);
void triBase(int *tab, int n, int max_chiffres);
int get_sum_diff(Tabs *t);
int get_similarity_score(Tabs *t);
int get_data(Tabs *t);


int main() {
    Tabs t;
    if (get_data(&t) != 1) {
        fprintf(stderr, "Erreur lors du chargement des données.\n");
        return 1;
    }
    printf("\nLe puzzle contient deux tableaux de %d valeurs\n", t.n);

    //tri par ordre croissant
    triBase(t.t1, t.n, t.nb_chiffres);
    triBase(t.t2, t.n, t.nb_chiffres);

    // -- Partie 1
    int res1 = get_sum_diff(&t);
    printf("\nVoici le resultat de day1 \n  Partie 1 : %d\n", res1);

    // -- Partie 2
    int res2 = get_similarity_score(&t);
    printf("\n  Partie 2 : %d\n", res2);

    free(t.t1);
    free(t.t2);
    return 0;
}

/*
* Renvoie le nombre de chiffres du nombre passé en argument.
*/
int nb_digits(int x) {
    int nb_chiffre = 0;

    if (x == 0) return 1;

    while (x != 0) { 
        x /= 10;
        nb_chiffre++; 
    }

    return nb_chiffre;
}

/*
* Classe le tableau dans l'ordre croissant avec un tri par base.
* Prend en argument le nombre de valeurs du tableau et le nombre de chiffres maximum des valeurs.
*/
void triBase(int *tab, int n, int max_chiffres){
    int tabBase[n];
    int base = 1;

    for(int f = 0; f < max_chiffres; f++) {
        int count = 0;

        if(f%2 == 0) {
            for(int i = 0; i< 10; i++) {
                for (int j=0; j<n; j++) {

                    if ((tab[j]/base)%10 == i) {
                        tabBase[count] = tab[j];
                        count++;
                    }

                }
            }
        }
        else {
           for(int i = 0; i < 10; i++) {
                for (int j = 0; j < n; j++) {

                    if ((tabBase[j]/base)%10 == i) {
                        tab[count] = tabBase[j];
                        count++;
                    }

                }
            } 
        } 
        base = base*10;
    }
    
    if(max_chiffres%2 != 0) {
        for(int i = 0; i < n; i++) {
            tab[i] = tabBase[i];
        }
    }
}

/*
* Retourne la somme des différences entre les i-ème plus petites valeurs des tableaux.
* Prend en argument la structure Tabs contenant les tableaux TRIÉS par ordre croissant.
*/
int get_sum_diff(Tabs *t) {
    int sum = 0;

    for(int i = 0; i < t->n; i++) {
        int diff = t->t2[i] - t->t1[i];

        if(diff < 0) {
            diff = -diff;
        }

        sum+= diff;
    }

    return sum;
}

/*
* Retourne l'accuracy score (voir README)
* Prend en argument la structure Tabs contenant les tableaux TRIÉS par ordre croissant.
*/
int get_similarity_score(Tabs *t) {
    int sim = 0;
    int i = 0; // indice du premier tableau
    int j = 0; // indice du deuxième tableau

    while (i < t->n && j < t->n) {
        // mise à niveau des indices
        if (t->t1[i] < t->t2[j]) {
            i++;
        } 
        else if (t->t2[j] < t->t1[i]) {
            j++;
        } 
        else { //valeur commune
            int val = t->t1[i];

            // cherche le nb d'occurences dans t1 puis t2
            int count1 = 0;
            while (i < t->n && t->t1[i] == val) {
                count1++;
                i++;
            }

            int count2 = 0;
            while (j < t->n && t->t2[j] == val) { 
                count2++;
                j++;
            }

            //somme
            sim += val * count1 * count2;
        }
    }
    return sim;
}

/* 
* Initialise le tableau avec les données de FILENAME.
* Prend en argument le tableau et renvoie 1 si pas d'erreurs.
*/
int get_data(Tabs *t) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    //initialisation des variables
    int val1, val2;
    t->t1 = NULL;
    t->t2 = NULL;
    t->n = 0;
    t->nb_chiffres = 0;

    while (fscanf(file, "%d %d", &val1, &val2) == 2) {
        // récupère les datas
        int *tmp1 = realloc(t->t1, (t->n + 1) * sizeof(int));
        int *tmp2 = realloc(t->t2, (t->n + 1) * sizeof(int));

        t->t1 = tmp1;
        t->t2 = tmp2;

        t->t1[t->n] = val1;
        t->t2[t->n] = val2;

        // recupère le nombre maximum de chiffres dans un nombre
        int nb_chiffre_temp = nb_digits(val1);

        if (nb_digits(val2) > nb_chiffre_temp)
            nb_chiffre_temp = nb_digits(val2);

        if (nb_chiffre_temp > t->nb_chiffres)
            t->nb_chiffres = nb_chiffre_temp;

        t->n++;
    }

    fclose(file);
    return 1;
}