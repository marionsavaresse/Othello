#ifndef _ADS_OTHELLO_plateau_h
#define _ADS_OTHELLO_plateau_h

// PARTIE.H CONTIENT SEULEMENT UNE DECLARATION DE STRUCTURE UTILISEE ICI DONC BESOIN DE L'INCLURE
#include "partie.h"

// DECLARATION DES FONCTIONS DU .C CORRESPONDANT
void initialise(s_partie *partie);
void affichePlateau(s_partie partieEnCours);
void afficheNombrePions(s_partie partieEnCours);
void affiche(s_partie partieEnCours);
void identificationJoueur(s_partie partie, int *pionJoueur, int *pionAdverse);

#endif
