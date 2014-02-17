#ifndef _ADS_OTHELLO_possibilites_h
#define _ADS_OTHELLO_possibilites_h

// PARTIE.H CONTIENT SEULEMENT UNE DECLARATION DE STRUCTURE UTILISEE ICI DONC BESOIN DE L'INCLURE
#include "partie.h"

// DECLARATION DES FONCTIONS DU .C CORRESPONDANT
void jouerCaseDirection(s_partie *partie, int ligne, int colonne, int abscisse, int ordonnee);
void jouerCase(s_partie *partie, int ligne, int colonne);
void jouer(s_partie *partie, int *sauvegarde);

#endif
