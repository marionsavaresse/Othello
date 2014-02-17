#include <stdio.h>

#include "plateau.h"
#include "possibilites.h"



int coupPossibleDirection(s_partie partie, int ligne, int colonne, int abscisse, int ordonnee)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)
    int pionAdverse = 0, pionJoueur = 0, pionsRetournesDirection = 0;
    
    // IDENTIFICATION DU JOUEUR
    identificationJoueur(partie, &pionJoueur, &pionAdverse);
    
    // VERIFICATION SUR DEPLACEMENT (MARCHE QUELQUE SOIT LE COUPLE DE DIRECTION)
    // CONDITION POUR NE PAS SORTIR DU TABLEAU
    if ((ligne+abscisse > -1 && ligne+abscisse < 8) && (colonne+ordonnee > -1 && colonne+ordonnee < 8))
    {
        // CONDITION CASE VIDE + CASE ADJACENTE ADVERSE
        if ((partie.tabPlateau[ligne+abscisse][colonne+ordonnee] != 0) && (partie.tabPlateau[ligne+abscisse][colonne+ordonnee] == pionAdverse))
        {
            do
            {
                ligne += abscisse;
                colonne += ordonnee;
                pionsRetournesDirection++;
            }
            while ((partie.tabPlateau[ligne+abscisse][colonne+ordonnee] == pionAdverse) && ((ligne+abscisse > -1 && ligne+abscisse < 8) && (colonne+ordonnee > -1 && colonne+ordonnee < 8)));
            
            // CONDITION POUR NE PAS SORTIR DU TABLEAU
            if ((ligne+abscisse > -1 && ligne+abscisse < 8) && (colonne+ordonnee > -1 && colonne+ordonnee < 8))
            {
                // CONDITION CASE ADVERSE + CASE ADJACENTE JOUEUR
                if (partie.tabPlateau[ligne+abscisse][colonne+ordonnee] == pionJoueur && partie.tabPlateau[ligne][colonne] == pionAdverse)
                {
                    return pionsRetournesDirection;
                }
            }
        }
    }
    return 0;
}



int coupPossible(s_partie partie, int ligne, int colonne)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)
    int pionsRetournesCase = 0;
    
    // ON TEST LES DIRECTIONS POSSIBLES, SI AU MOINS UNE MARCHE, LE TEST S'ARRETE
    if (coupPossibleDirection(partie, ligne, colonne, -1, 0) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, -1, 0);
    }
    if (coupPossibleDirection(partie, ligne, colonne, -1, 1) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, -1, 1);
    }
    if (coupPossibleDirection(partie, ligne, colonne, 0, 1) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, 0, 1);
    }
    if (coupPossibleDirection(partie, ligne, colonne, 1, 1) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, 1, 1);
    }
    if (coupPossibleDirection(partie, ligne, colonne, 1, 0) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, 1, 0);
    }
    if (coupPossibleDirection(partie, ligne, colonne, 1, -1) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, 1, -1);
    }
    if (coupPossibleDirection(partie, ligne, colonne, 0, -1) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, 0, -1);
    }
    if (coupPossibleDirection(partie, ligne, colonne, -1, -1) != 0)
    {
        pionsRetournesCase += coupPossibleDirection(partie, ligne, colonne, -1, -1);
    }
    if (pionsRetournesCase != 0)
    {
        return pionsRetournesCase;
    }
    return 0;
}



int possible(s_partie partie, int *coordonneesCaseLigne, int *coordonneesCaseColonne)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)  
    int pionsRetournes = 0;
    int pionsRetournes2 = 0;
    *coordonneesCaseLigne = 0;
    *coordonneesCaseColonne = 0;
    
    // LES COMPTEURS NE SERONT DECLARES QUE POUR LA LECTURE DU TABLEAU
    // ON PARCOURT LES CASES VIDES POUR SAVOIR SI UN COUP EST POSSIBLE QUELQUE PART
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if (!partie.tabPlateau[i][j])
            {
                if (coupPossible(partie, i, j) != 0)
                {
                    pionsRetournes2 = coupPossible(partie, i, j);
                    
                    if (pionsRetournes2 > pionsRetournes)
                    {
                        pionsRetournes = pionsRetournes2;
                        *coordonneesCaseLigne = i;
                        *coordonneesCaseColonne = j;
                    }
                    
                }
            }
        }
    }
    if (pionsRetournes != 0)
    {
        return 1;
    }
    return 0;
}



int partieTerminee(s_partie partie, int *sauvegarde, int caseLigne, int caseColonne)
{
    // CAS OU LE JOUEUR A SOUHAITE SAUVEGARDER ET DONC ARRETER LA PARTIE
    if (*sauvegarde)
    {
        return 1;
    }
    // ON VERIFIE QU'AUCUN DES DEUX JOUEURS N'A DE COUP POSSIBLE
    else
    {
        partie.joueurSuivant = 2;
        if (possible(partie, &caseLigne, &caseColonne) == 0)
        {
            partie.joueurSuivant =1;
            if (possible(partie, &caseLigne, &caseColonne) == 0)
            {
                return 1;
            }
        }
        return 0;
    }
}