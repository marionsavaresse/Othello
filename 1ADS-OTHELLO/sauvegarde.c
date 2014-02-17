#include <stdio.h>
#include <stdlib.h>

#include "pose.h"
#include "sauvegarde.h"

int sauvegardeFichier(s_partie partie, int *sauvegarde)
{
    // SI LE JOUEUR A VOULU SAUVEGARDER
    if (sauvegarde)
    {
        FILE *fichier = NULL;

        fichier=fopen("sauvegardeOthello.txt","w+");

        // SI LE JOUEUR QUI A SAUVEGARDE ETAIT NOIR
        if (partie.joueurSuivant == 2)
        {
            fputc('2', fichier);
        }
        // SI LE JOUEUR QUI A SAUVEGARDE ETAIT BLANC
        else
        {
            fputc('1', fichier);
        }

        // RETOUR A LA LIGNE AVANT D'INSCRIRE LE PLATEAU
        fputc('\n', fichier);

        // LE COMPTEUR N'EST DECLARE QUE POUR LA LECTURE DU TABLEAU
        // ON LIT NOTRE TABLEAU DU PLATEAU ET POUR CHAQUE CASE ON ECRIT LE CONTENU DANS LE FICHIER TXT
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if (partie.tabPlateau[i][j] == 2)
                {
                fputc('2', fichier);
                }
                else if (partie.tabPlateau[i][j] == 1)
                {
                    fputc('1', fichier);
                }
                else
                {
                    fputc('0', fichier);
                }
            }
            // RETOUR A LA LIGNE APRES CHAQUE FIN DE LIGNE DU TABLEAU
            fputc('\n', fichier);
        }

        // ON FERME LE FICHIER
        fclose(fichier);

        return 1;
    }
    // SI AUCUNE SAUVEGARDE N'A ETE DEMANDE
    return 0;
}


void initialiseFichier(s_partie *partie)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)
    char caractereLu = 0;
    int joueurOK = 0;
    int ligne = 0;
    int colonne = 0;

    FILE *fichier = NULL;

    fichier=fopen("sauvegardeOthello.txt","r");

    if (fichier != NULL)
    {
        // UN TANT QU'ON ARRIVE PAS A LA FIN DU FICHIER (EOF)
        do
        {
            caractereLu = fgetc(fichier);

            // LECTURE DU JOUEUR DANS LE FICHIER
            if (!joueurOK)
            {
                if (caractereLu != '\n')
                {
                    if (caractereLu == '1')
                    {
                        partie->joueurSuivant = 1;
                    }
                    else
                    {
                        partie->joueurSuivant = 2;
                    }
                }
                else
                {
                    joueurOK = 1;
                }
            }
            // LECTURE DU TABLEAU DANS LE FICHIER
            else
            {
                if (caractereLu != '\n')
                {
                    if (caractereLu == '0')
                    {
                        partie->tabPlateau[ligne][colonne] = 0;
                    }
                    else if (caractereLu == '1')
                    {
                        partie->tabPlateau[ligne][colonne] = 1;
                    }
                    else
                    {
                        partie->tabPlateau[ligne][colonne] = 2;
                    }
                    // A CHAQUE TOUR DE DO WHILE ON CHANGERA DE COLONNE
                    colonne++;
                }
                // QUAND IL Y A UN RETOUR A LA LIGNE DANS LE FICHIER ON CHANGE DE LIGNE
                // ET ON REINITIALISE LES COLONNES
                else
                {
                    colonne = 0;
                    ligne++;
                }
            }
        } while (caractereLu != EOF);

        // ON FERME LE FICHIER
        fclose(fichier);

        // ON MET LE SCORE A JOUR
        majScore(partie);
    }
    // S'IL N'Y A PAS DE FICHIER A OUVRIR LE JEU OUVRIRA UNE NOUVELLE PARTIE
    else
    {
        printf("-> Il n'y a pas de fichier de sauvegarder à ouvrir.\n\n");
    }
}
