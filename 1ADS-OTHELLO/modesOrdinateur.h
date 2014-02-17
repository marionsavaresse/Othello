#ifndef _ADS_OTHELLO_ordiAleatoire_h
#define _ADS_OTHELLO_ordiAleatoire_h

// PARTIE.H CONTIENT SEULEMENT UNE DECLARATION DE STRUCTURE UTILISEE ICI DONC BESOIN DE L'INCLURE
#include "partie.h"

// DECLARATION DES FONCTIONS DU .C CORRESPONDANT
void jouerOrdiAlea(s_partie *partie);
void jouerOrdiGlouton(s_partie *partie, int *coupLigne, int *coupColonne);

#endif
