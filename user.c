#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "user.h"
#include "save.h"


/*-----------------------------------------------------------------------------------------------------------
--  user.c : fichier source contenant les définition des fonctions permettant l'implémentation du mode	   --
--						interactif																		   --
--  																									   --
--																										   --
--																										   --
--  28-12-16 : création du fichier user.c																   --
--	28-12-16 : implémentation de toutes les fonctions sauf modifier_figure et changer_ordre_figure         --
--  04-01-17 : implémentation des fonctions modifier_figure et changer_ordre_figure						   --
--  04-01-17 : v.1.0 terminée et fonctionnelle															   --
-----------------------------------------------------------------------------------------------------------*/



/***************************************************************
	Définitions des fonctions pour le mode intéraction utilisateur
****************************************************************/


/* 
Affiche la présentation générale du programme (nom, auteurs, description...)
*/
void afficher_presentation(){

	puts("\t\t\t*********************************");
	puts("\t\t\t*            DRAWER             *");
	puts("\t\t\t*********************************\n");

	puts("Auteur : Mohammed EL KHAIRA\nv.1.0\n");
	puts("Bienvenue dans DRAWER, le logiciel qui vous permet de créer des dessins composés\nde rectangles et de disques de couleur grise.\nDans cette première version, vous avez la possibilité de créer un nouveau\ndessin, placer les rectangles et disques de votre choix et les modifier.\nVous pouvez aussi sauvegarder et charger vos créations.\nNotez que vous pouvez faire qu'un dessin à la fois.\n\n");
}


/* Affiche le menu principal
@renvoi : le numéro (entier) de la section choisie par l'utilisateur
*/
int afficher_menu_principal(){

	int choix = 0;

	puts("\n\nQue souhaitez-vous faire ?");
	puts("(1) créer un dessin (ou modifier un dessin chargé)");
	puts("(2) sauvegarder un dessin");
	puts("(3) charger un dessin");
	puts("(4) quitter\n");

	puts("Veuillez choisir un numéro");
	scanf("%d", &choix);

	return choix;
}


/* Affiche le premier menu, celui de la création d'un dessin 
@renvoi : le numéro (entier) de la sous-section choisie par l'utilisateur
*/
int afficher_menu_1(){

	int choix = 0;

	puts("\n\nCréation d'un dessin (ou modification d'un dessin chargé) :");
	puts("(5) ajouter une figure (rectangle ou disque)");
	puts("(6) supprimer une figure");
	puts("(7) afficher la liste des figures actuelles");
	puts("(8) modifier une figure (dimensions ou point d’ancrage)");
	puts("(9) changer l’ordre des figures");
	puts("(10) retour\n");

	puts("Veuillez choisir un numéro");
	scanf("%d", &choix);
	
	return choix;
}


/* Demande à l'utilisateur de saisir les paramètres généraux du dessin et les stocke dans une structure appropriée dessin_t
@paramètre(s) : l'adresse de la structure dans laquelle on veut stocker les paramètres généraux du dessin crée
*/
void initialiser_parametres(dessin_t *dessin){

	puts("\nVeuillez entrer les paramètres de votre dessin :");

	puts("Largeur");
	scanf("%d", &(dessin->largeur));
	puts("Hauteur");
	scanf("%d", &(dessin->hauteur));
	puts("Intensité maximale des couleurs");
	scanf("%d", &(dessin->couleur_max));

	puts("Couleur du fond");
	scanf("%d", &(dessin->couleur_fond));
	while(dessin->couleur_fond < 0 || dessin->couleur_fond > dessin->couleur_max){
		printf("La couleur du fond de l'image ne doit pas être supérieur à %d\n", dessin->couleur_max);
		puts("Couleur du fond");
		scanf("%d", &(dessin->couleur_fond));
	}
}


/* Affiche le deuxième menu, celui de la sauvegarde d'un dessin 
@renvoi : le numéro (entier) de la sous-section choisie par l'utilisateur
*/
int afficher_menu_2(){

	int choix = 0;

	puts("\n\nSauvegarde d'un dessin :");
	puts("(11) format vectorielle");
	puts("(12) format matricielle");
	puts("(13) retour\n");

	puts("Veuillez choisir un numéro");
	scanf("%d", &choix);
	
	return choix;
}


/* Affiche le troisième menu, celui du chargement d'un dessin 
@renvoi : le numéro (entier) de la sous-section choisie par l'utilisateur
*/
int afficher_menu_3(){

	int choix = 0;

	puts("\n\nChargement d'un dessin :");
	puts("(14) format vectorielle");
	puts("(15) retour\n");

	puts("Veuillez choisir un numéro");
	scanf("%d", &choix);
	
	return choix;
}


/* Demande à l'utilisateur de saisir les caractéristiques d'une figure à ajouter au dessin 
	et la stocke à la fin d'une liste (qui représente donc le dessin)
@paramètre(s) : l'adresse de la figure à ajouter + l'adresse de la liste dans laquelle on veut la stocker
*/
void ajouter_figure(figure_t *fig, liste_t *l, dessin_t *dessin){

	puts("\nVeuillez entrer les paramètres de votre figure :");

	puts("Forme de la figure (tapez 0 = rectangle ou 1 = disque)");
	scanf("%d", (int *)&(fig->forme));
	while(!(fig->forme == 0 || fig->forme == 1)){
		puts("Entrez 0 si vous voulez un rectangle ou 1 si vous voulez un disque");
		scanf("%d", (int *)&(fig->forme));
	}
	puts("Abscisse du point d'ancrage (en fonction de la taille de votre dessin)");
	scanf("%d", &(fig->abs));
	while(fig->abs < 0 || fig->abs > dessin->largeur){
		printf("L'abscisse du point d'ancrage doit être compris entre 0 et %d\n", dessin->largeur);
		puts("Abscisse du point d'ancrage");
		scanf("%d", &(fig->abs));
	}
	puts("Ordonnée du point d'ancrage (en fonction de la taille de votre dessin)");
	scanf("%d", &(fig->ord));
	while(fig->ord < 0 || fig->ord > dessin->hauteur){
		printf("L'ordonnée du point d'ancrage doit être compris entre 0 et %d\n", dessin->hauteur);
		puts("Ordonnée du point d'ancrage");
		scanf("%d", &(fig->ord));
	}
	if(fig->forme == 1){
		puts("Rayon");
		scanf("%d", &(fig->rayon));
		while(fig->rayon < 0 || fig->rayon > dessin->hauteur){
			printf("Le rayon doit être compris entre 0 et %d\n", dessin->hauteur);
			puts("Rayon");
			scanf("%d", &(fig->rayon));
		}
	}
	else{
		puts("Longueur");
		scanf("%d", &(fig->longueur));
		while(fig->longueur < 0 || fig->longueur > dessin->largeur){
			printf("La longueur doit être comprise entre 0 et %d\n", dessin->largeur);
			puts("Longueur");
			scanf("%d", &(fig->longueur));
		}
		puts("Hauteur");
		scanf("%d", &(fig->hauteur));
		while(fig->hauteur < 0 || fig->hauteur > dessin->hauteur){
			printf("La hauteur doit être comprise entre 0 et %d\n", dessin->hauteur);
			puts("Longueur");
			scanf("%d", &(fig->hauteur));
		}
	}
	puts("Couleur (entier entre 0 et l'intensité maximale choisie précédemment)");
	scanf("%d", &(fig->couleur));
	while(fig->couleur < 0 || fig->couleur > dessin->couleur_max){
		printf("La couleur doit être comprise entre 0 et %d\n", dessin->couleur_max);
		puts("Couleur");
		scanf("%d", &(fig->couleur));
	}
	
	ajouter_fin(*fig, l);
}


/* Supprimme la figure demandée par l'utilisateur ou supprimme toutes les figures d'un coup si demandé
@paramètre(s) : l'adresse de la liste dont l'on veut supprimer une figure ou toutes
*/
void supprimer_figure(liste_t *l){

	liste_t l_tmp = creer_liste();
	int num = 0;

	if(l->premier == NULL){
		puts("Votre dessin est vide, il n'y a rien à supprimer !");
		return ;
	}

	puts("Entrez le numéro de la figure à supprimmer");
	scanf("%d", &num);
	while(num < 0 || num > l->longueur){
		printf("Ce numéro doit être compris entre 0 et %u\n", l->longueur);
		scanf("%d", &num);
	}

	if(num == 0)
		return ;
	/*else if(num == 999)
		detruire_liste(l);*/
	else{
		while(num > 1){
			deplacer(l, &l_tmp); 			/* tant que on n'a pas accès à la figure que l'utilisateur souhaite supprimmer, on déplace successivement, à partir de la première, les figures de la liste dans une liste temporaire */
			num = num - 1;
		}
		supprimer_debut(l);				  /* on supprimme la figure en question */
		while(l->premier != NULL){
			deplacer(l, &l_tmp);			/* on déplace le reste de la liste dans la liste temporaire. Cette-dernière contient alors toutes les figures sauf celle supprimée */
		}
		*l = l_tmp;									/* la liste temporaire devient la liste représentant le dessin */
	}
}


/* Affiche le contenu d'un dessin (la liste des figures qu'il contient)
@paramètre(s) : la liste de figures à afficher
*/
void afficher_liste_figure(liste_t l){
	if(l.premier == NULL)
		puts("Votre dessin est vide, il n'y a rien à afficher !");
	afficher_liste(l);
}


void modifier_figure(figure_t *fig){

}


void changer_ordre_figure(liste_t *l){

}


/* Permet l'intéraction avec l'utilisateur dans le mode intéractif
@paramètre(s) : l'adresse du numéro (entier) de la section choisie par l'utilisateur
	+ l'adresse de la liste dans laquelle on veut stocker le dessin
	+ l'adresse de la structure dans laquelle on veut stocker les paramètres généraux du dessin
	+ l'adresse du model de figure à ajouter au dessin 
*/
void interaction(int *choix, liste_t *l, dessin_t *dessin, figure_t *fig){
	
	switch(*choix){
			case 1:
				if(l->premier == NULL)
					initialiser_parametres(dessin);
				*choix = afficher_menu_1();
				break;
			case 2:
				*choix = afficher_menu_2();
				break;
			case 3:
				*choix = afficher_menu_3();
				break;
			case 4: 
				exit(EXIT_SUCCESS);
				break;
			case 5:
				ajouter_figure(fig, l, dessin);
				*choix = afficher_menu_1();
				break;
			case 6:
				supprimer_figure(l);
				*choix = afficher_menu_1();
				break;
			case 7:
				afficher_liste_figure(*l);
				*choix = afficher_menu_1();
				break;
			case 8:
				modifier_figure(fig);
				*choix = afficher_menu_1();
				break;
			case 9:
				changer_ordre_figure(l);
				*choix = afficher_menu_1();
				break;
			case 10:
				*choix = afficher_menu_principal();
				break;
			case 11:
				sauver_vect(*l, *dessin);
				*choix = afficher_menu_2();
				break;
			case 12:
				sauver_mat(*l, *dessin);
				*choix = afficher_menu_2();
				break;
			case 13:
				*choix = afficher_menu_principal();
				break;
			case 14:
				charger_vect(l, dessin);
				*choix = afficher_menu_3();
				break;
			case 15:
				*choix = afficher_menu_principal();
				break;
			case 16:
				break;
			default:
				puts("Veuillez ne choisir qu'un nombre proposé");
				*choix = afficher_menu_principal();
				break;
		}
}
