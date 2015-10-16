#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp3.h"

//Fonctions de crÔøΩation Livre, Rayon, Biblio

T_Livre *creerLivre (char *titre, char *auteur, char *edition)
{
    T_Livre *new_livre = (T_Livre*)malloc(sizeof(T_Livre));
    
    if(new_livre==NULL)
        exit(EXIT_FAILURE);
    
    strcpy(new_livre->titre,titre);
    strcpy(new_livre->auteur,auteur);
    strcpy(new_livre->edition,edition);
    new_livre->disponible=1;
    new_livre->suivant=NULL;
    
    return new_livre;
}

T_Rayon *creerRayon(char *theme)
{
    T_Rayon *new_rayon = (T_Rayon*)malloc(sizeof(T_Rayon));
    
    if(new_rayon==NULL)
        exit(EXIT_FAILURE);
    
    strcpy(new_rayon->theme_rayon,theme);
    new_rayon->nombre_livres=0;
    new_rayon->premier=NULL;
    
    return new_rayon;
}

T_Biblio *creerBiblio (char *nom)
{
    T_Biblio *new_biblio = (T_Biblio*)malloc(sizeof(T_Biblio));
    
    if(new_biblio==NULL)
        exit(EXIT_FAILURE);
    
    strcpy(new_biblio->nom,nom);
    new_biblio->premier=NULL;
    
    return new_biblio;
}

//fonction d'ajout d'un livre dans un rayon

int ajouterLivre(T_Rayon *rayon, T_Livre *livre)
{
    T_Livre *ptr_livre = rayon->premier;
    
    if(rayon->nombre_livres==0)
    {
        livre->suivant=NULL;
        rayon->premier=livre;
        rayon->nombre_livres++;
        ptr_livre=rayon->premier;
    }
    else
    {
        while(ptr_livre->suivant && strcmp(livre->titre,ptr_livre->suivant->titre)>0)
            ptr_livre=ptr_livre->suivant;
        
        if(!ptr_livre->suivant || strcmp(livre->titre, ptr_livre->suivant->titre)!=0)
        {                                                       //vérifier que le livre n'existe pas déjà dans le rayon !
            livre->suivant=ptr_livre->suivant;
            ptr_livre->suivant=livre;
            ptr_livre=livre;
        }
    }
    
    if(strcmp(ptr_livre->titre,livre->titre)==0)
        return 1;
    
    return 0;
}

//fonction emprunter livre dans un rayon

int emprunterLivre(T_Rayon *rayon, char* titre)
{
    T_Livre *ptr = rayon->premier;
    
    while (<#condition#>) {
        <#statements#>
    }
}

int main()
{
    
    T_Biblio *UTC = creerBiblio("UTC");
    T_Rayon *Maths = creerRayon("Maths");
    T_Livre *Manuel_MT90 = creerLivre("Manuel MT90", "Prof", "Edition 2009");
    T_Livre *Manuel_MT91 = creerLivre("Manuel MT91", "Prof", "Edition 2010");
    
    
    if (ajouterLivre(Maths, Manuel_MT90)!=0)
        printf("Le premier livre du rayon %s de la bibliotheque %s est %s\n", Maths->theme_rayon, UTC->nom, Maths->premier->titre);
    else
        printf("Erreur lors de l'ajout du livre %s\n", Manuel_MT90->titre);
    
    if (ajouterLivre(Maths, Manuel_MT91)!=0)
        printf("Le second livre du rayon %s de la bibliotheque %s est %s\n", Maths->theme_rayon, UTC->nom, Maths->premier->suivant->titre);
    else
        printf("Erreur lors de l'ajout du livre %s\n", Manuel_MT91->titre);
    
    
    T_Livre *ptr = Maths->premier; // Affichage livres rayon "Maths"
    
    while(ptr)
    {
        printf("%s\n", ptr->titre);
        ptr = ptr->suivant;
    }
    
    return 0;
}


