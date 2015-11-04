#ifndef tp3_h
#define tp3_h

//Constantes
#define tailleNom 50 //taille des chaines de caractères
#define tailleTabLivres 50 //taille du tableau contenant les résultats de la recherche d'un livre


//Structures


struct Livre
{
    char titre[tailleNom];
    char auteur[tailleNom];
    char edition[tailleNom];
    unsigned short int disponible;
    struct Livre* suivant;
};
typedef struct Livre T_Livre;


struct Rayon
{
    char theme_rayon[50];
    unsigned short int nombre_livres;
    T_Livre *premier;
    struct Rayon* suivant;
};
typedef struct Rayon T_Rayon;

struct Biblio
{
    char nom[tailleNom];
    struct Rayon* premier;
};
typedef struct Biblio T_Biblio;

//prototypes
T_Livre *creerLivre (char *titre, char *auteur, char *edition);
T_Rayon *creerRayon(char *theme);
T_Biblio *creerBiblio (char *nom);

int ajouterLivre(T_Rayon *rayon, T_Livre *livre);
int ajouterRayon(T_Biblio *biblio, T_Rayon *rayon);
void afficherBiblio(T_Biblio *biblio);
void afficherRayon(T_Rayon *rayon);
int emprunterLivre(T_Rayon *rayon, char* titre);
int supprimerLivre(T_Rayon *rayon, char* titre);
void supprimerRayon(T_Biblio *biblio, char *nom_rayon);
void trierTableau(char ***tab, int tailleTab);
void rechercherLivres(T_Biblio *biblio, char* critereTitre);

#endif








