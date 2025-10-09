#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define FILENAME "data.txt"

void get_max(int* tab, int n, int* max){

    for(int i=0; i<n ; i++){

        int compt = 0;
        int aTest=tab[i];

        while(aTest != 0){
            aTest = aTest/10; 
            compt++;
        }

        if(compt > *max){
            *max = compt;
        }
    }
}

void triBase(int *tab, int n, int max_chiffres){

    int tabBase[n];

    int base=1;
    for(int f=0; f< max_chiffres ; f++){
        int count=0;
        if(f%2 ==0){
            for(int i=0 ; i< 10; i++ ){
                for (int j=0 ; j<n; j++){
                    if ((tab[j]/base)%10==i){
                        tabBase[count] = tab[j];
                        count++;
                    }
                }
            }
        }
        else{
           for(int i=0 ; i< 10; i++ ){
                for (int j=0 ; j<n; j++){
                    if ((tabBase[j]/base)%10==i){
                        tab[count] = tabBase[j];
                        count++;
                    }
                }
            } 
        } 
        base= base*10;
    }
    
    if(max_chiffres%2 != 0){
        for(int i = 0; i<n ; i++){
            tab[i]=tabBase[i];
        }
    }

}

typedef struct {
    int *t1;
    int *t2;
    int n;
    int nb_chiffres;
} tabs;

int get_sum_diff(tabs *t){
    int sum = 0;
    for(int i = 0; i < t->n; i++){
        int diff = t->t2[i] - t->t1[i];
        if(diff < 0){
            diff = -diff;
        }
        sum+=diff;
    }
    return sum;
}

int get_similarity_score(tabs *t){
    
    int sim = 0;
    int i = 0; // indice du premier tableau
    int j = 0; // indice du deuxième tableau

    while (i < t->n && j < t->n) {

        //on cherche à tomber sur une valeur commune
        if (t->t1[i] < t->t2[j]) {
            i++;
        } 
        else if (t->t2[j] < t->t1[i]) {
            j++;
        } 
        else { //valeurs égales

            int val = t->t1[i]; // la valeur commune
            int count1 = 0;
            while (i < t->n && t->t1[i] == val) { // on cherche le nb d'occurence dans t1
                count1++;
                i++;
            }

            int count2 = 0;
            while (j < t->n && t->t2[j] == val) { // "" dans t2
                count2++;
                j++;
            }

            sim += val * count1 * count2;
        }
    }
    return sim;
}

int digits(int x) {
    int c = 0;
    if (x == 0) return 1;
    while (x != 0) { 
        x /= 10; c++; 
    }
    return c;
}

int get_data(tabs *t) {

    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    int val1, val2;

    t->t1 = NULL;
    t->t2 = NULL;
    t->n = 0;
    t->nb_chiffres = 0;

    while (fscanf(file, "%d %d", &val1, &val2) == 2) {

        int *tmp1 = realloc(t->t1, (t->n + 1) * sizeof(int));
        int *tmp2 = realloc(t->t2, (t->n + 1) * sizeof(int));

        if (tmp1 == NULL || tmp2 == NULL) {
            perror("Erreur d'allocation mémoire");
            free(t->t1);
            free(t->t2);
            fclose(file);
            return 0;
        }

        t->t1 = tmp1;
        t->t2 = tmp2;

        t->t1[t->n] = val1;
        t->t2[t->n] = val2;

        //on recupère le nombre maximum de chiffre dans un nombre
        int nb_chiffre_temp = digits(val1);

        if (digits(val2) > nb_chiffre_temp)
            nb_chiffre_temp = digits(val2);

        if (nb_chiffre_temp > t->nb_chiffres)
            t->nb_chiffres = nb_chiffre_temp;

        t->n++;
    }

    fclose(file);
    return 1;
}

int main(int argc, char** argv){
    
    tabs t;

    if (get_data(&t) != 1) {
        fprintf(stderr, "Erreur lors du chargement des données.\n");
        return 1;
    }

    printf("\nLe fichier lu contient deux tableaux de %d valeurs\n", t.n);

    triBase(t.t1, t.n, t.nb_chiffres);
    triBase(t.t2, t.n, t.nb_chiffres);
    int res1 = get_sum_diff(&t);
    int res2 = get_similarity_score(&t);

    printf("\nVoici le resultat de day1 \n  Partie 1 : %d\n(aka la sommes des différences entre les deux tableaux ordonnancés)\n", res1);
    printf("\n  Partie 2 : %d\n(aka le similarity score)\n", res2);

    free(t.t1);
    free(t.t2);
    return 0;

}
    