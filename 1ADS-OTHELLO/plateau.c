#include <stdio.h>

#include "plateau.h"



// ON INITIALISE LA PARTIE 
void initialise(s_partie *partie)
{
    // INITIALISATION DU PLATEAU AVEC LES 4 CASES DE DEPART
    // LES COMPTEURS NE SERONT DECLARES QUE POUR LA LECTURE DU TABLEAU
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if (i == 3 && j == 3)
            {
                partie->tabPlateau[i][j] = 1;
            }
            else if (i == 3 && j == 4)
            {
                partie->tabPlateau[i][j] = 2;
            }
            else if (i == 4 && j == 3)
            {
                partie->tabPlateau[i][j] = 2;
            }
            else if (i == 4 && j == 4)
            {
                partie->tabPlateau[i][j] = 1;
            }
            else
            {
                partie->tabPlateau[i][j] = 0;
            }
        }
    }

    // INITIALISATION DU SCORE
    // LE COMPTEUR N'EST DECLARE QUE POUR LA LECTURE DU TABLEAU
    for(int i=0;i<2;i++)
    {
        partie->tabScore[i] = 2;
    }
    
    // LES NOIRS COMMENCENT
    partie->joueurSuivant = 2;
}



// AFFICHAGE DU PLATEAU DE JEU
void affichePlateau(s_partie partieEnCours)
{
    // AFFICHAGE DES LETTRES
    printf("\ta\t\tb\t\tc\t\td\t\te\t\tf\t\tg\t\th\v\v");
    
    // LES COMPTEURS NE SERONT DECLARES QUE POUR LA LECTURE DU TABLEAU
    for(int i=0;i<33;i++)
    {
        for(int j=0;j<66;j++)
        {
            if (j == 65)
            {
                // AFFICHAGE DES CHIFFRES DE DROITE
                if (i % 4 == 2)
                {
                    printf("    %d",(i/4)+1);
                }
                // AFFICHAGE DES ESPACES VIDES DU TABLEAU
                else
                {
                    printf(" ");
                }
            }
            else if (i % 4 == 2 && j % 8 == 4)
            {
                // AFFICHAGE DES PIONS BLANCS
                if(partieEnCours.tabPlateau[i/4][j/8] == 1)
                {
                    printf("B");
                }
                // AFFICHAGE DES PIONS NOIRS
                else if (partieEnCours.tabPlateau[i/4][j/8] == 2)
                {
                    printf("N");
                }
                // AFFICHAGE DES CASES LIBRES EN JEU
                else
                {
                    printf(" "); 
                }
            }
            // AFFICHAGE DES ETOILES EN BORDURE
            else if (i % 4 == 0 && j % 8 == 0)
            {
                printf("*");
            }
            else if (i % 4 == 0 && j % 2 == 0)
            {
                printf("*");
            }
            else if (j % 8 == 0)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
        
    }
    printf("\n\n");
}



// AFFICHAGE DES POINTS
void afficheNombrePions(s_partie partieEnCours)
{
    // AFFICHAGE DU SCORE ACTUEL
    printf("Nombre de pions noirs : %d\n", partieEnCours.tabScore[0]);
    printf("Nombre de pions blancs : %d\n\n", partieEnCours.tabScore[1]);
}



// AFFICHAGE DU PLATEAU ET DES POINTS
void affiche(s_partie partieEnCours)
{
    affichePlateau(partieEnCours);
    afficheNombrePions(partieEnCours);
}



// ON IDENTIFIE LE JOUEUR AFIN DE SAVOIR QUELS SONT SES PIONS
void identificationJoueur(s_partie partie, int *pionJoueur, int *pionAdverse)
{
    // IDENTIFICATION DES PIONS DU JOUEUR ET DE L'ADVERSAIRE
    if (partie.joueurSuivant == 2)
    {
        *pionJoueur = 2;
        *pionAdverse = 1;
    }
    else
    {
        *pionJoueur = 1;
        *pionAdverse = 2;
    }
}