#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp3.h"

/*
 **********************************************************
 DEBUT DES FONCTIONS UTILITAIRE POUR GENERER DES STRUCTURES
 **********************************************************
 */


//Fonction de création d'un livre
T_Livre* creerLivre (char *titre, char *auteur, char *edition)
{
    T_Livre *new_livre = (T_Livre*)malloc(sizeof(T_Livre));
    //Revoir l'allocation dynamique comme la sugestion faite à la fonction creerRayon
    
    //Test si l'allocation s'est bien déroulée
    if(new_livre==NULL)
        exit(EXIT_FAILURE);
    
    //Initialisation de la structure
    strcpy(new_livre->titre,titre);
    strcpy(new_livre->auteur,auteur);
    strcpy(new_livre->edition,edition);
    new_livre->disponible=1;
    new_livre->suivant=NULL;
    
    return new_livre;
}



//Fonction de création d'un rayon
T_Rayon* creerRayon(char *theme)
{
    T_Rayon *new_rayon = (T_Rayon*)malloc(sizeof(T_Rayon));
    /*
     pourquoi tu ne fais pas :
     -->    T_Rayon *new_rayon = malloc(sizeof(*new_rayon));
     ????????
     */
    
    //Test si l'allocation s'est bien déroulé
    if(new_rayon==NULL)
        exit(EXIT_FAILURE);
    
    //Initialisation de la structure
    strcpy(new_rayon->theme_rayon,theme);
    new_rayon->nombre_livres=0;
    new_rayon->suivant=NULL;
    new_rayon->premier=NULL;
    
    return new_rayon;
}



//Fontion de création de la bibliothèque
T_Biblio* creerBiblio (char *nom)
{
    T_Biblio *new_biblio = (T_Biblio*)malloc(sizeof(T_Biblio));
    
    //Test si l'allocation s'est bien déroulée
    if(new_biblio==NULL)
        exit(EXIT_FAILURE);
    
    //Initialisation de la structure
    strcpy(new_biblio->nom,nom);
    new_biblio->premier=NULL;
    
    return new_biblio;
}


/*
 ********************************************
 FIN DES FONCTIONS DE CREATION DES STRUCTURES
 ********************************************
 */











/*
 ******************************
 DEBUT DES FONCTIONS DE LINKAGE
 ******************************
 */


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


/*
 On souhaite ajouter le rayon à la bibliothèque
 Pour cela on suppose que le rayon est déjà créé. Le conflit se gère directement dans le main
 Notre but est d'insérer le rayon dans la bibliothèque
 */
int ajouterRayon(T_Biblio *biblio, T_Rayon *rayon)
{
    T_Rayon *ptr_rayon = biblio->premier;
    
    if(!biblio->premier)
    {
        biblio->premier=rayon;
        rayon->suivant=NULL;
        ptr_rayon=rayon;
    }
    else
    {
        while(ptr_rayon->suivant && strcmp(rayon->theme_rayon,ptr_rayon->suivant->theme_rayon)>0)
            ptr_rayon=ptr_rayon->suivant;
        
        if(!ptr_rayon->suivant || strcmp(rayon->theme_rayon, ptr_rayon->suivant->theme_rayon)!=0)
        {                                                       //vérifier que le livre n'existe pas déjà dans le rayon !
            rayon->suivant=ptr_rayon->suivant;
            ptr_rayon->suivant=rayon;
            ptr_rayon=rayon;
        }
    }
    
    if(strcmp(ptr_rayon->theme_rayon,rayon->theme_rayon)==0)
        return 1;
    
    return 0;
}


/*
 ****************************
 FIN DES FONCTIONS DE LINKAGE
 ****************************
 */











/*
 *******************************
 DEBUT DES FONCTIONS D'AFFICHAGE
 *******************************
 */


//Fonction d'affichage des rayons de la bibliothèque
void afficherBiblio(T_Biblio *biblio)
{
    //Creation d'un pointeur afin de manipuler la liste chainee
    T_Rayon *ptr_nb_livres = biblio->premier;
    
    //On parcout la liste
    //La liste étant déjà trié, on se contente d'afficher simplement dans l'odre ou on la parcourt
    while (ptr_nb_livres)
    {
        printf("Le Rayon : %s contient %d livres\n",ptr_nb_livres->theme_rayon,ptr_nb_livres->nombre_livres);
        ptr_nb_livres=ptr_nb_livres->suivant;
    }
}


//Fonction d'affichage du contenu d'un rayon
void afficherRayon(T_Rayon *rayon)
{
    //Pointeur sur la structure des livres. Récupère la première adresse de la sous liste chainée
    T_Livre *ptr_rayon = rayon->premier;
    
    while(ptr_rayon->suivant)
    {
        //Si livre Disponible
        if (ptr_rayon->disponible==1)
        {
            printf("Titre : %s\tAuteur : %s\tEdition : %s\tDisponibilité : Oui\n",ptr_rayon->titre,ptr_rayon->auteur,ptr_rayon->edition);
        }
        //Si livre non Disponible
        else
        {
            printf("Titre : %s\tAuteur : %s\tEdition : %s\tDisponibilité : Non\n",ptr_rayon->titre,ptr_rayon->auteur,ptr_rayon->edition);
        }
        //incrémentation du pointeur
        ptr_rayon=ptr_rayon->suivant;
    }
    
}


/*
 *****************************
 FIN DES FONCTIONS D'AFFICHAGE
 *****************************
 */










/*
 **********************************************
 DEBUT DES FONCTIONS DE SUPPRESSION & D'EMPRUNT
 **********************************************
 */


//fonction emprunter livre dans un rayon
int emprunterLivre(T_Rayon *rayon, char* titre)
{
    T_Livre *ptr = rayon->premier;
    
    while ((strcmp(ptr->titre,titre)!=0) && ptr->suivant)
        ptr=ptr->suivant;
    
    if(ptr->disponible==1)
    {
        ptr->disponible=0;
        printf("Vous venez d'emprunter le livre %s\n", ptr->titre);
        return 1;
    }
    else if(!ptr)
        printf("Le livre n'exite pas dans ce rayon");
    else
        printf("Le livre %s est déjà emprunté\n", ptr->titre);
    return 0;
}



//fonction suppression livre rayon
int supprimerLivre(T_Rayon *rayon, char* titre)
{
    T_Livre *ptr = rayon->premier;
    
    if (strcmp(ptr->titre,titre)==0)
    {
        rayon->premier=ptr->suivant;
        ptr->suivant=NULL;
        free(ptr);
        printf("Vous venez de supprimer le livre %s\n", titre);
        return 1;
    }
    
    else
    {
        while (ptr->suivant && (strcmp(ptr->suivant->titre,titre)!=0))
            ptr=ptr->suivant;
        
        if(!ptr->suivant)
            printf("Le livre n'exite pas dans ce rayon\n");
        else
        {
            T_Livre *ptr2 = ptr->suivant;
            ptr->suivant=ptr->suivant->suivant;
            free(ptr2->suivant);
            printf("Vous venez de supprimer le livre %s\n", titre);
            return 1;
        }
    }
    return 0;
}


/*
 Suppression d'un rayon et de tous les livres qu'il contient
 renvoie 1 si la suppression s'est bien passée, 0 sinon; on veillera à libérer la mémoire précédemment allouée
 */
void supprimerRayon(T_Biblio *biblio, char *nom_rayon)
{
    
}


/*
 ********************************************
 FIN DES FONCTIONS DE SUPPRESSION & D'EMPRUNT
 ********************************************
 */








/*
 ***********************************
 DEBUT DES FONCTIONS COMPLÉMENTAIRES
 ***********************************
 */


//fonction de tri de tableau
void trierTableau(char ***tab, int tailleTab)
{
    int changement,i;
    
    char *tmp;
    
    do
    {
        changement=0;
        
        for (i=0; i<tailleTab-1; i++)
        {
            if (strcmp(tab[i][1],tab[i+1][1])>0)
            {
                tmp=tab[i+1][1];
                tab[i+1][1]=tab[i][1];
                tab[i][1]=tmp;
                changement=1;
            }
        }
        
    }while (changement==1);
    
    
}


//fonction de recherche de livres
void rechercherLivres(T_Biblio *biblio, char* critereTitre)
{
    T_Rayon *ptr_rayon = biblio->premier;
    int nbLivres=0, i,j;
    
    char ***tableau;// création tableau des livres trouvés
    tableau=malloc(sizeof(char**)*tailleTabLivres);
    
    for (i=0; i<50; i++)
    {
        tableau[i]=malloc(sizeof(char*)*5);
    }
    
    while (ptr_rayon)
    {
        T_Livre *ptr_livre = ptr_rayon->premier;
        while (ptr_livre)
        {
            i=0;
            if(strncmp(ptr_livre->titre, critereTitre, strlen(critereTitre))==0)
            {
                tableau[i][0]=ptr_livre->titre;
                tableau[i][1]=ptr_livre->auteur;
                tableau[i][2]=ptr_livre->edition;
                
                if(ptr_livre->disponible==1)
                    tableau[i][3]="Oui";
                else
                    tableau[i][3]="Non";
                
                tableau[i][4]=ptr_rayon->theme_rayon;
                nbLivres++;
            }
            ptr_livre=ptr_livre->suivant;
        }
        ptr_rayon=ptr_rayon->suivant;
    }
    
    trierTableau(tableau, nbLivres);//tri tableau
    
    printf("%15s %15s %15s %15s %14s\n","Titre", "Auteur", "Edition", "Disponibilité", "Rayon"); //Affichage tableau
    
    for(i=0;i<nbLivres;i++)
    {
        for (j=0; j<5; j++)
        {
            printf("%15s", tableau[i][j]);
        }
        printf("\n");
    }
    
}

/*
 *********************************
 FIN DES FONCTIONS COMPLÉMENTAIRES
 *********************************
 */
