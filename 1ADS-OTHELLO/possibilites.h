#ifndef _ADS_OTHELLO_possibilites_h
#define _ADS_OTHELLO_possibilites_h

// PARTIE.H CONTIENT SEULEMENT UNE DECLARATION DE STRUCTURE UTILISEE ICI DONC BESOIN DE L'INCLURE
#include "partie.h"

// DECLARATION DES FONCTIONS DU .C CORRESPONDANT
int coupPossibleDirection(s_partie partie, int ligne, int colonne, int abscisse, int ordonnee);
int coupPossible(s_partie partie, int ligne, int colonne);
int possible(s_partie partie, int *coordonneesCaseLigne, int *coordonneesCaseColonne);
int partieTerminee(s_partie partie, int *sauvegarde, int caseLigne, int caseColonne);

#endif
