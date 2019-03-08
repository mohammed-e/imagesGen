#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "save.h"
#include "batch.h"


/*-----------------------------------------------------------------------------------------------------------------
--  batch.c : fichier source contenant les définitions des fonctions permettant l'implémentation du mode batch   --
--  																											 --
--																												 --
--																												 --
--  29-12-16 : création du fichier batch.c 															 			 --
--	05-01-17 : implémentation de la fonction de conversion d'une image vectorielle en image matricielle          --
--	05-01-17 : v.1.0 terminée et fonctionnelle 																	 --
--  06-01-17 : implémentation de la fonction de conversion d'un lot d'images vectorielles en matricielles        --
--  																											 --
-----------------------------------------------------------------------------------------------------------------*/



/*********************************************
	Définitions des fonctions pour le mode batch
**********************************************/


/* Charge un dessin sauvegardé dans un fichier, dont le nom est passé en paramètre lors de l'exécution, sous forme 
	vectorielle (syntaxe décrite dans le fichier batch.h (1)) en stockant les figures dans une liste et les 
	paramètres généraux dans une structure appropriée dessin_t
@paramètre(s) : l'adresse de la liste dans laquelle on veut stocker les figures de l'image vectorielle
	+ l'adresse de la structure dans laquelle on veut stocker les paramètres généraux de l'image
	+ le nom du fichier passé en paramètre (->argv[1])
*/
void charger_batch(liste_t *l, dessin_t *dessin, char *nom){

	/* Initialisation des variables */
	char c = ' ';
	FILE *f = NULL;
	figure_t fig = {RECTANGLE,0,0,0,0,0,0};


	/* On ouvre le fichier passé en paramètre */
	f = fopen(nom,"r");
	openCheck(f);


	/* On commence par récupérer les paramètres généraux du dessin */
	if(!fscanf(f, "%d %d %d %d\n", &(dessin->largeur), &(dessin->hauteur), &(dessin->couleur_max), &(dessin->couleur_fond))){
		puts("Le fichier chargé n'est pas écrit correctement. Veuillez respecter le format demandé");
		return ;
	}
	
	/* On récupère ensuite les figure une part une, en fonction de la synthaxe considérée */
	while(!feof(f)){
		/* D'abord la nature des figures */
		if(!fscanf(f, "%c", &c)){
			puts("Le fichier chargé n'est pas écrit correctement. Veuillez respecter le format demandé");
			return ;
		}
		/* Puis le reste */
		if(c == 'r'){
			if(!fscanf(f, "%d %d %d %d %d\n", &fig.abs, &fig.ord, &fig.longueur, &fig.hauteur, &fig.couleur)){
				puts("Le fichier chargé n'est pas écrit correctement. Veuillez respecter le format demandé");
				return ;
			}
			ajouter_fin(fig,l);
		}
		else{
			fig.forme = DISQUE;
			if(!fscanf(f, "%d %d %d %d\n", &fig.abs, &fig.ord, &fig.rayon, &fig.couleur)){
				puts("Le fichier chargé n'est pas écrit correctement. Veuillez respecter le format demandé");
				return ;
			}
			ajouter_fin(fig,l);
		}
	}
	fclose(f);
}


/* Sauvegarde un dessin au format PNM (P2) en écrivant dans un fichier nouvellement crée dont le nom ressemble 
	à celui passé en paramètre lors de l'exécution. D'abord écrit l'en-tête du fichier qui contient 
	les paramètres généraux du dessin (sauf couleur fond). Ensuite écrit une matrice représentant la 
	couleur (ici niveau de gris) de chaque point du dessin (syntaxe décrite dans le fichier batch.h (2))
@paramètre(s) : la liste de figures du dessin 
	+ la structure contenant les paramètres généraux de l'image
	+ le nom du fichier passé en paramètre (->argv[1])
*/
void sauver_batch(liste_t l, dessin_t dessin, char *nom){

	/* Initialisation des variables*/
	FILE *f = NULL;
	int i = 0, j = 0; /* i <=> numéro ligne matrice / j <=> numéro colonne matrice */


	/* On change le nom du fichier passé en paramètre puis on crée un nouveau fichier */
	strcat(nom, "_2");
	f = fopen(nom,"w");
	openCheck(f);


	/* On écrit d'abord l'en-tête spécifique des images au format P2 */
	fprintf(f, "P2\n%03d %03d %03d\n#Mon dessin\n", dessin.largeur, dessin.hauteur, dessin.couleur_max);

	/* On commence par remplir la matrice avec la couleur de fond du dessin*/
	for(i = 0; i < dessin.hauteur; i++){
		for(j = 0; j < dessin.largeur; j++)
			fprintf(f, "%03d ", dessin.couleur_fond);
		fputc('\n',f);
	}

	/* On repositionne le curseur au début de la matrice, juste après l'en-tête (d'où le 27)*/
	rewind(f);
	fseek(f, 27, SEEK_SET);


	/* On parcourt la matrice et on remplace la couleur de fond par celle des figures en fonction des coordonnées */
	while(l.premier != NULL){
		/* Si la figure est un rectangle*/
		if( l.premier->elem.forme == RECTANGLE){
			for(i = 0; i < dessin.hauteur; i++){ 			/* parcourt l'ensemble des lignes */
					for(j = 0; j < dessin.largeur; j++){		/* parcourt l'ensemble des colonnes */
						if(i >= l.premier->elem.ord && i < (l.premier->elem.ord) + l.premier->elem.hauteur){ 		/* si on est à la bonne ligne dans le rectangle */
							if(j >= l.premier->elem.abs && j < (l.premier->elem.abs) + l.premier->elem.longueur)	/* si on est à la bonne colonne dans le rectangle */
								fprintf(f, "%03d ", l.premier->elem.couleur); 		/* %03d : comme on sait que la couleur max est 255, on va écrire les couleurs dans un format fixe composé de 3 chiffres */
							else 
								fseek(f, 4, SEEK_CUR); 	 /* s'il n'y a pas une partie de figure en un point d'une ligne, on avance le curseur sur cette ligne jusqu'au prochain point intéressant (grâce au format fixe) */
						}
						else 
							fseek(f, 4, SEEK_CUR);; 	 /* de même */
					}
				fputc('\n',f); 									 /* à la fin d'une ligne, on passe à la suivante */
			}
			l.premier = l.premier->suiv;
		}
		/* Si la figure est un disque */
		else{
			for(i = 0; i < dessin.hauteur; i++){				/* parcourt l'ensemble des lignes */
					for(j = 0; j < dessin.largeur; j++){		/* parcourt l'ensemble des colonnes */
						if((j - l.premier->elem.abs)*(j - l.premier->elem.abs) + (i - l.premier->elem.ord)*(i - l.premier->elem.ord) <= l.premier->elem.rayon*l.premier->elem.rayon) 		/* si on est à l'intérieur du cercle */
							fprintf(f, "%03d ", l.premier->elem.couleur); 		/* %03d : comme on sait que la couleur max est 255, on va écrire les couleurs dans un format fixe composé de 3 chiffres */
						else 
							fseek(f, 4, SEEK_CUR); 	 /* s'il n'y a pas une partie de figure en un point d'une ligne, on avance le curseur sur cette ligne jusqu'au prochain point intéressant (grâce au format fixe) */
					}
				fputc('\n',f); 			/* à la fin d'une ligne, on passe à la suivante */
			}
			l.premier = l.premier->suiv;
		}
		/* On revient au début de la matrice après avoir écrit chaque figure */
		rewind(f);
		fseek(f, 27, SEEK_SET);
	}
	fclose(f);
}


/* Convertit un dessin/image vectorielle, passé en paramètre lors de l'exécution, en dessin/image matricielle.
@paramètre(s) : la liste de figures du dessin 
	+ la structure contenant les paramètres généraux de l'image
	+ le nom du fichier passé en paramètre (->argv[1])
*/
void conversion_vect_mat(liste_t *l, dessin_t *dessin, char *nom){
	charger_batch(l, dessin, nom);
	sauver_batch(*l, *dessin, nom);
}