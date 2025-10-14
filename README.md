# Let-s-solve-AoC

Ce repository contient les solutions aux quatre premiers jours de l’Advent of Code 2024.

Auteur : Antonin Censier
Date : Octobre 2025

## Instructions

Pour compiler et exécuter facilement les programmes, suivez les étapes ci-dessous.

Placez-vous à la racine du dépôt, puis utilisez les commandes suivantes :

Compiler tous les fichiers .c :

`
make all
`

Exécuter le programme d’un jour spécifique :

`
make dayX
`

Supprimer les exécutables :

`
make clean
`

## Methodes

### Day 1

Data : Fichier contenant deux listes d’entiers de même longueur.

Partie 1 :

L’objectif est de calculer la somme des différences absolues entre les i-èmes plus petites valeurs des deux tableaux.

La première étape consiste à trier les deux listes dans l’ordre croissant. Ayant déjà rencontré un problème similaire, j’ai choisi d’utiliser une ancienne fonction de tri par base (O(n)). Cette méthode nécessite de connaître le nombre de chiffres maximum des entiers présents dans les tableaux. Une fois les tableaux triés, la somme se calcule simplement en additionnant les différences absolues entre les éléments correspondants.

Partie 2 :

Il faut maintenant calculer la somme suivante : Somme(valeur[i] × nb_occurrences_t1 × nb_occurrences_t2).

Seules les valeurs communes aux deux tableaux sont prises en compte dans le calcul. Pour les identifier, deux indices — un pour chaque tableau — avancent successivement jusqu’à trouver une valeur commune, puis comptent le nombre d’occurrences de cette valeur dans chacun des tableaux avant d’ajouter le produit correspondant à la somme totale.

### Day 2

Data : Fichier contenant N lignes, chacune composée de 1 à M entiers.

Partie 1 :

Le but est de déterminer combien de lignes sont strictement croissantes ou décroissantes, tout en respectant un écart maximal de 3 entre deux valeurs consécutives.

Pour chaque ligne, on détermine d’abord la tendance (croissante ou décroissante) à partir des deux premières valeurs, puis on vérifie que tous les écarts respectent cette tendance et la limite de 3. Si les conditions echouent, la ligne n’est pas considérée comme valide.

Partie 2 :

Une seule valeur non conforme est désormais tolérée par ligne. 

Je suis parti du principe que si on enlève cette valeur, la ligne doit être valide. Si la ligne complète échoue au test, on retire successivement chaque entier et on vérifie à chaque fois si la ligne devient valide. Si au moins une de ces vérifications réussit, la ligne est alors considérée comme correcte.

### Day 3

Data : Fichier contenant une suite de caractères.

Partie 1 : 

L’objectif est de calculer la somme des produits identifiés sous la forme « mul(x,y) » présents dans la chaîne de caractères issue du fichier.

Pour optimiser la recherche, j’ai utilisé un buffer circulaire qui parcourt les caractères un à un tout en conservant les n derniers lus. Cette approche nécessite de connaître la position du dernier caractère inséré afin de pouvoir reconstituer les n derniers caractères dans leur ordre réel.
Cette méthode m'a permis de detecté "mul(" qui entraine ensuite une recherche de "x,y)". Si cette deuxième recherches aboutit, on calcule le produit et l'ajoute à la somme. 

Partie 2 : 

Un produit n’est désormais pris en compte que si une instruction « do() » a été rencontrée auparavant. Si la dernière instruction rencontrée est un « don’t() », les multiplications suivantes sont ignorées jusqu’à la prochaine occurrence de « do() ».

Le même  buffer circulaire est utilisé pour détecter les instructions « do() » et « don’t() », permettant ainsi d’activer ou de désactiver une condition booléenne qui autorise ou bloque la prise en compte des multiplications et leur recherche.

### Day 4

Data : Fichier contenant N lignes et M colonnes de caractères parmi ‘X’, ‘M’, ‘A’ et ‘S’

Partie 1 : 

L’objectif est de compter le nombre d’occurrences du mot « XMAS » présentes dans la grille, quelle que soit sa direction et son sens.

Pour chaque caractère, on vérifie si le mot apparaît dans chacune des directions possibles. Afin d’éviter les vérifications redondantes, le test est effectué pour « XMAS » et son inverse « SAMX », ce qui permet par exemple de ne pas avoir à tester à la fois de gauche à droite et de droite à gauche. Les vérifications menant en dehors des limites de la grille sont naturellement ignorées.

Partie 2 :

Il s’agit cette fois de compter le nombre d’occurrences du mot « MAS » formant un motif en forme de croix (X), c’est-à-dire avec la lettre ‘A’ au centre et les lettres ‘M’ et ‘S’ positionnées sur les diagonales.

Pour cela, la grille est parcourue caractère par caractère. Lorsqu’un ‘A’ est rencontré, les diagonales sont examinées afin de vérifier si elles correspondent à l’un des quatre schémas possibles de « M-A-S ».
