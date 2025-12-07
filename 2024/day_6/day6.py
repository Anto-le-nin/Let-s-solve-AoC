# Advent of Code - Day 6 | Antonin Censier (version Python)

def lire_grille(fichier):
    """Lit la grille depuis data.txt et renvoie (grille, x, y, direction)."""
    grille = [list(line.strip()) for line in open(fichier)]
    start_x = start_y = None

    for y, ligne in enumerate(grille):
        for x, c in enumerate(ligne):
            if c == '^':  # départ toujours vers le haut
                start_x, start_y = x, y
                grille[y][x] = '.'  # on remplace le garde par une case vide
                return grille, start_x, start_y, 0  # 0 = direction haut
    raise ValueError("Pas de garde trouvé (^)")


def in_bounds(x, y, grille):
    """Retourne True si (x, y) est dans la grille."""
    return 0 <= y < len(grille) and 0 <= x < len(grille[0])


def tourne_droite(direction):
    """Renvoie la nouvelle direction après un virage à droite."""
    return (direction + 1) % 4


def parcourir(grille, x, y, direction):
    """Fait avancer le garde jusqu'à sortir de la grille."""
    # directions : 0 = haut, 1 = droite, 2 = bas, 3 = gauche
    # Format: (dx, dy) pour cohérence avec x, y
    mouvements = [(0, -1), (1, 0), (0, 1), (-1, 0)]
    
    while True:
        # Marque la case actuelle comme visitée
        grille[y][x] = 'X'
        
        dx, dy = mouvements[direction]
        nx, ny = x + dx, y + dy
        
        # Si on sort de la grille → arrêt
        if not in_bounds(nx, ny, grille):
            break
        
        # Si mur → tourne à droite
        if grille[ny][nx] == '#':
            direction = tourne_droite(direction)
        else:
            # avance normalement
            x, y = nx, ny
    
    return grille


def compter_X(grille):
    """Compte le nombre de cases 'X' visitées."""
    return sum(ligne.count('X') for ligne in grille)


def afficher_grille(grille):
    """Affiche la grille dans la console."""
    for ligne in grille:
        print(''.join(ligne))
    print()


def main():
    fichier = "data.txt"
    grille, x, y, direction = lire_grille(fichier)
    grille = parcourir(grille, x, y, direction)
    afficher_grille(grille)
    resultat = compter_X(grille)
    print("Résultat partie 1 :", resultat)


if __name__ == "__main__":
    main()
