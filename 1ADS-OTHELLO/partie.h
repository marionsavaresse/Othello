#ifndef _ADS_OTHELLO_partie_h
#define _ADS_OTHELLO_partie_h

// DECLARATION DE LA STRUCTURE PARTIE
typedef struct s_partie s_partie;

struct s_partie{
    int tabPlateau[8][8];
    int tabScore[2];    
    int joueurSuivant;
};

#endif
