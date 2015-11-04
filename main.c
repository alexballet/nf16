#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp3.h"






int main()
{
    /*
     ***************************************************
     CREATION DES DIFFERENTES ENTITES DE LA BIBLIOTHEQUE
     ***************************************************
     */
    
    //    T_Biblio *UTC = creerBiblio("UTC");
    //
    //    T_Rayon *Maths = creerRayon("Maths");
    //    T_Rayon *Biologie = creerRayon("Biologie");
    //
    //    T_Livre *Manuel_MT90 = creerLivre("Manuel MT90", "Prof", "2009");
    //    T_Livre *Manuel_MT91 = creerLivre("Manuel MT91", "Prof", "2010");
    //    T_Livre *Manuel_BL01 = creerLivre("Manuel BL01", "Prof2", "2013");
    
    
    /*
     *************************************************************************************
     LE BUT DES FONCTIONS D AJOUT EST DE LINKER LES DIFFERENTES PARTIES DE LA BIBLIOTHEQUE
     *************************************************************************************
     */
    
    //Il est plus interessant de faire de l allocation dynamique en terme de getion ressoure
    char nom[tailleNom], nomRayon[tailleNom], titre[tailleNom], auteur[tailleNom], edition[tailleNom];
    int choix, bibliothèque=0, continuer=1;
    T_Biblio* biblio;
    T_Livre* livre;
    T_Rayon* rayon;
    
    while (continuer==1)
    {
        printf("Bienvenue dans notre programme de gestion de bibliothèque. Que voulez-vous faire ?\n1.Créer une bibliothèque\n2.Ajouter un rayon à la bibliothèque\n3.Ajouter un livre dans un rayon\n4.Afficher les rayons de la bibliothèque\n5.Afficher les livres d'un rayon\n6.Retirer un livre\n7.Supprimer un rayon\n8.Rechercher un livre par son titre\n9.Supprimer un livre\n10.Gérer une liste d'emprunts\n11.Quitter\n");
        scanf("%d", &choix);
        getchar();
        
        if(bibliothèque==1)
            rayon=biblio->premier;
        
        switch (choix)
        {
            case 1:
                if (bibliothèque==0)
                {
                    printf("Entrer le nom de la bibliothèque : ");
                    scanf("%[^\n]s", nom);
                    biblio = creerBiblio(nom);
                    bibliothèque=1;
                    printf("\nLa bibliothèque %s a été créée.\n", biblio->nom);
                    rayon = biblio->premier;
                }
                else
                    printf("\nVous aves déjà créé la bibliothèque %s!\n", biblio->nom);
                break;
                
            case 2:
                if (bibliothèque==1)
                {
                    printf("Entrer le nom du rayon : ");
                    scanf("%[^\n]s", nomRayon);
                    rayon = creerRayon(nomRayon);
                    printf("\nLe rayon %s a été créé.\n", rayon->theme_rayon);
                    
                    if(ajouterRayon(biblio, rayon)==1)
                        printf("Le rayon %s a été ajouté à la bibliothèque %s.\n", rayon->theme_rayon, biblio->nom);
                    else
                        printf("Erreur lors de l'ajout du rayon %s à la bibliothèque %s\n", rayon->theme_rayon, biblio->nom);
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
                
            case 3:
                if (bibliothèque==1)
                {
                    printf("Entrer le titre du livre : ");
                    scanf("%[^\n]s", titre);
                    getchar();
                    printf("Entrer le nom de l'auteur du livre : ");
                    scanf("%[^\n]s", auteur);
                    getchar();
                    printf("Entrer le nom de la maison d'edition : ");
                    scanf("%[^\n]s", edition);
                    getchar();
                    livre = creerLivre(titre, auteur, edition);
                    printf("\nLe livre %s a été créé.\n", livre->titre);
                    
                    
                    printf("Entrer le thème du rayon : ");
                    scanf("%[^\n]s", nomRayon);
                    getchar();
                    while (rayon && strcmp(rayon->theme_rayon,nomRayon)!=0)//recherche du rayon
                        rayon = rayon->suivant;
                    
                    if(!rayon)
                        printf("Le rayon est inexistant.\n");
                    else
                    {
                        if(ajouterLivre(rayon, livre)==1)
                            printf("Le livre %s a été ajouté au rayon %s\n", livre->titre, rayon->theme_rayon);
                        else
                            printf("Erreur lors de l'ajout du livre %s\n", livre->titre);
                    }
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
                
            case 4:
                if (bibliothèque==1)
                {
                    afficherBiblio(biblio);
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
            case 5:
                if (bibliothèque==1)
                {
                    printf("Entrer le thème du rayon : ");
                    scanf("%[^\n]s", nomRayon);
                    getchar();
                    while (rayon && strcmp(rayon->theme_rayon,nomRayon)!=0)//recherche du rayon
                        rayon = rayon->suivant;
                    
                    if(!rayon)
                        printf("Le rayon est inexistant.\n");
                    else
                    {
                        afficherRayon(rayon);
                    }
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
            case 6:
                if (bibliothèque==1)
                {
                    printf("Entrer le titre du livre : ");
                    scanf("%[^\n]s", titre);
                    getchar();
                    
                    printf("Entrer le thème du rayon : ");
                    scanf("%[^\n]s", nomRayon);
                    getchar();
                    
                    while (rayon && strcmp(rayon->theme_rayon,nomRayon)!=0)//recherche du rayon
                        rayon = rayon->suivant;
                    
                    if(!rayon)
                        printf("Le rayon est inexistant.\n");
                    else
                    {
                        emprunterLivre(rayon, titre);
                    }
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
            case 7:
                if (bibliothèque==1)
                {
                    printf("Entrer le thème du rayon : ");
                    scanf("%[^\n]s", nomRayon);
                    getchar();
                    
                    supprimerRayon(biblio, nomRayon);
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
            case 8:
                if (bibliothèque==1)
                {
                    printf("Entrer la chaine de caractères à rechercher : ");
                    scanf("%[^\n]s", nom);
                    getchar();
                    
                    rechercherLivres(biblio, nom);
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
            case 9:
                if (bibliothèque==1)
                {
                    printf("Entrer le titre du livre : ");
                    scanf("%[^\n]s", titre);
                    getchar();
                    
                    printf("Entrer le thème du rayon : ");
                    scanf("%[^\n]s", nomRayon);
                    getchar();
                    
                    while (rayon && strcmp(rayon->theme_rayon,nomRayon)!=0)//recherche du rayon
                        rayon = rayon->suivant;
                    
                    if(!rayon)
                        printf("Le rayon est inexistant.\n");
                    else
                    {
                        supprimerLivre(rayon, titre);
                    }
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
            case 10:
                if (bibliothèque==1)
                {
                    traiterListeEmprunts(biblio);
                }
                else
                    printf("Créer la bibliothèque d'abord !\n");
                break;
            case 11:
                continuer=0;
                break;
            default:
                printf("Choix inconnu\n");
                break;
        }
    }
    return 0;
}
