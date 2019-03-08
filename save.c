#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "save.h"										


/*------------------------------------------------------------------------------------------------------------
--  save.c : fichier source contenant les définitions des fonctions permettant le chargement et la     		--
--				sauvegarde de dessins sous forme vectorielle/matricielle (+ des fonctions intermédiaires) 	--
--  																										--
--																											--
--																											--
--  25-12-16 : création du fichier save.c																    --
--	25-12-16 : implémentation des fonctions de chargement et de sauvegarde sous forme vectorielle          	--
--  30-12-16 : implémentation de la fonction de sauvegarde sous forme matricielle  		    				--
--  30-12-16 : v.1.0 terminée et fonctionnelle															    --
------------------------------------------------------------------------------------------------------------*/


/*********************************************************************
	Définitions des fonctions de gestion des sauvegardes / chargements
**********************************************************************/


/* Vérifie si l'ouverture d'un fichier a bien eu lieu sans problème
@paramètre(s) : l'adresse du fichier dont on veut vérifier l'ouverture
*/
void openCheck(FILE *fichier){

  if(fichier == NULL){
    printf("Il y a un problème dans l'ouverture du fichier ! Vérifiez que le nom est correct\n");
    exit(EXIT_FAILURE);
  }
}


/* Charge un dessin sauvegardé dont le nom est choisi par l'utilisateur sous forme 
	vectorielle (syntaxe décrite dans le fichier batch.h (1)) en stockant les figures dans une liste 
	et les paramètres généraux dans une structure appropriée dessin_t
@paramètre(s) : l'adresse de la liste dans laquelle on veut stocker les figures de l'image vectorielle
	+ l'adresse de la structure dans laquelle on veut stocker les paramètres généraux de l'image
*/
void charger_vect(liste_t *l, dessin_t *dessin){

	/* Initialisation des variables */
	int rep = 0;
	char c = ' ';
	char nom[51] = "";
	FILE *f = NULL;
	figure_t fig = {RECTANGLE,0,0,0,0,0,0};

	/* On prévient l'utiisateur que le chargement d'un dessin supprimme l'éventuel dessin en cours */
	puts("\n\nATTENTION ! Si vous chargez un dessin, le dessin actuel sera écrasé. Continuer ? (tapez 0 = oui ou 1 = non)");
	scanf("%d", &rep);
	while(!(rep == 0 || rep == 1)){
		puts("Entrez 0 si vous voulez continuer ou 1 sinon");
		scanf("%d", &rep);
	}
	/* Si il ne veut pas continuer, on revient au menu */
	if(rep){
		return ;
	}
	/* Sinon, on supprimme le dessin en cours (on vide la liste) */
	*l = creer_liste();


	/* On récupère le nom  du fichier que l'utilisateur veut charger */
	puts("Veuillez entrer le nom du fichier à charger (limité à 50 caractères) :");
	scanf("%s", nom);
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


/* Sauvegarde un dessin en écrivant dans un fichier texte dont le nom est choisi par l'utilisateur 
	les paramètres généraux du dessin et la liste des figures (syntaxe décrite dans le fichier batch.h (1))
@paramètre(s) : la liste de figures du dessin + la structure contenant les paramètres généraux de l'image
*/
void sauver_vect(liste_t l, dessin_t dessin){

	/* Initialisation des variables */
	char nom[51] = "";
	FILE *f = NULL;

	/* On récupère le nom que l'utilisateur veut donner à son fichier de sauvegarde */
	puts("Veuillez entrer le nom du fichier de sauvegarde (limité à 50 caractères) :");
	scanf("%s", nom);
	f = fopen(nom,"w");
	openCheck(f);


	/* On écrit d'abord les paramètres généraux du dessin */
	fprintf(f, "%d %d %d %d\n", dessin.largeur, dessin.hauteur, dessin.couleur_max, dessin.couleur_fond);


	/* Si il n'y a pas de dessin, on quitte en ne sauvegardant rien */
	if(l.premier == NULL){
		fclose(f);
		return ;
	}
	/* Sinon, en fonction de la forme des figures, on écrit leur caractéristiques en respectant la synthaxe (une figure par ligne) */
	else{
		while(l.premier != NULL){
			if( l.premier->elem.forme == RECTANGLE){
				fprintf(f, "r %d %d %d %d %d\n", l.premier->elem.abs, l.premier->elem.ord, l.premier->elem.longueur, l.premier->elem.hauteur, l.premier->elem.couleur);
				l.premier = l.premier->suiv;
			}
			else{
				fprintf(f, "d %d %d %d %d\n", l.premier->elem.abs, l.premier->elem.ord, l.premier->elem.rayon, l.premier->elem.couleur);
				l.premier = l.premier->suiv;
			}
		}
	}
	fclose(f);
}


/* Sauvegarde un dessin au format PNM (P2) en écrivant dans un fichier dont le nom est choisi par l'utilisateur. 
	D'abord écrit l'en-tête du fichier qui contient les paramètres généraux du dessi (sauf couleur fond). 
	Ensuite écrit une matrice représentant la couleur (ici niveau de gris) de chaque point du dessin (syntaxe décrite dans le fichier batch.h (2))
@paramètre(s) : la liste de figures du dessin + la structure contenant les paramètres généraux de l'image
*/
void sauver_mat(liste_t l, dessin_t dessin){

	/* Initialisation des variables*/
	char nom[51] = "";
	FILE *f = NULL;
	int i = 0, j = 0; /* i <=> numéro ligne matrice / j <=> numéro colonne matrice */


	/* On récupère le nom que l'utilisateur veut donner à son fichier de sauvegarde */
	puts("Veuillez entrer le nom du fichier de sauvegarde (limité à 50 caractères) :");
	scanf("%s", nom);
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


