#ifndef _ADS_OTHELLO_sauvegarde_h
#define _ADS_OTHELLO_sauvegarde_h

// PARTIE.H CONTIENT SEULEMENT UNE DECLARATION DE STRUCTURE UTILISEE ICI DONC BESOIN DE L'INCLURE
#include "partie.h"

// DECLARATION DES FONCTIONS DU .C CORRESPONDANT
int sauvegardeFichier(s_partie partie, int *sauvegarde);
void initialiseFichier(s_partie *partie);

#endif
