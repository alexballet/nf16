#ifndef tp3_h
#define tp3_h


#endif /* tp3_h */


//Structures

struct Livre
{
    char titre[50];
    char auteur[50];
    char edition[50];
    int disponible;
    struct Livre* suivant;
};

typedef struct Livre T_Livre;

struct Rayon
{
    char theme_rayon[50];
    int nombre_livres;
    T_Livre* premier;
    struct Rayon* suivant;
};

typedef struct Rayon T_Rayon;

struct Biblio
{
    char nom[50];
    struct Rayon* premier;
};

typedef struct Biblio T_Biblio;

//prototypes

T_Livre *creerLivre (char *titre, char *auteur, char *edition);
T_Biblio *creerBiblio (char *nom);
T_Rayon *creerRayon(char *theme);
int ajouterLivre(T_Rayon *rayon, T_Livre *livre);
int emprunterLivre(T_Rayon *rayon, char* titre);
int supprimerLivre(T_Rayon *rayon, char* titre);
void rechercherLivres(T_Biblio *biblio, char* critereTitre);


