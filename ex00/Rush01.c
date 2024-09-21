#include <unistd.h>
#include <stdlib.h>

//affichage de la chaine de caractere en parcourant la chaine avec while 
//sert a afficher les messages erreurs etc

void    ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
}

//affichage de la grille 4x4 ou int **grid est pointeur vers grille quand solution
//converti chq entier (1 a 4) en ASCII avec '0' a lentier et affiche

void    print_grid(int **grid)
{
    int i, j;
    char c;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            c = grid[i][j] + '0';
            write(1, &c, 1);
            if (j < 3)
                write(1, " ", 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

//calcul nombre caisses visibles dans une ligne ou colonne dpuis pnt vue evite
//fonction recursive chaque iterations caisse haute "max.." compte visible
// int *line: pointeur ligne col grille, size: taille rest analy

int count_visible(int *line, int size, int max_height, int visible_count)
{
    if (size == 0)
        return (visible_count);
    if (*line > max_height)
        return (count_visible(line + 1, size - 1, *line, visible_count + 1));
    return (count_visible(line + 1, size - 1, max_height, visible_count));   
}

//validation en verif les contrainte pour visibilite sur ligne
//fct count_visible verif ligne respecte contrainte visibi dps gauche et droite. non respct 0 sinon 1.

int valide_line(int *line, int constraint_left, int constraint_right)
{
    if (count_visible(line, 4, 0, 0) != constraint_left)
        return (0);
    if (count_visible(line + 3, 4, 0, 0) != constraint_right)
        return (0);
    return(1);     
}

//validation visible sur colonne avec contraintes ok
//extr colonn grille, stok val dns tab column, vrf contraint dps haut et dps bas.
//int **grid sgnf grille entiere

int validation_vot(int **grid, int col, int constraint_top, int constraint_bottom)
{
    int column[4];
    int i;

    i = 0;
    while (i < 4)
    {
        column[i] = grid[i][col];
        i++;
    }
    if (count_visible(column, 4, 0, 0) != constraint_top)
        return (0);
    if (count_visible(column + 3, 4, 0, 0) != constraint_bottom)
        return (0);
    return (1);      
}

//validation complete de la grille fct principal
//validate.. verifie ligne colonne resp contrainte visibi. pas 0 sinn 1

int is_valid(int **grid, int *constraints_row, int *constraints_col)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (!validate_line(grid[i], constraints_row[i * 2], constraints_row[i * 2 + 1]))
            return (0);
        if (!validate_col(grid, i, constraints_col[i * 2]), constraints_col[i * 2 + 1])
            return(0);
        i++;    
    }
    return (1);
}

//verifie si valeur peut etre placée, evite doublon valeur
//ligne et colonne vrf pas deja mm val. si mm v 0 sinon 1
//row ligne place valeur, col c colonne plc val, int vl placer ( 1 et 4)

int can_place(int **grid, int row, int col, int value)
{
    int i;

    i = 0;
    while (i < col)
    {
        if (grid[row][i] == value)
            return(0);
        i++;
    }
    i = 0;
    while (i < row)
    {
        if (grid[i][col] == value)
            return (0);
        i++;    
    }
    return (1);
}