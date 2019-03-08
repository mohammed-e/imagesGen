#include "list.h"
#include "save.h"

#ifndef DEF_BATCH
#define DEF_BATCH


/*-----------------------------------------------------------------------------------------------------------------
--  batch.h : bibliothèque contenant les prototypes des fonctions permettant l'implémentation du mode batch   	 --
--  																											 --
--																												 --
--																												 --
--  29-12-16 : création du fichier batch.h																 		 --
--	29-12-16 : implémentation de la fonction de conversion d'une image vectorielle en image matricielle          --
--	29-12-16 : v.1.0 terminée et fonctionnelle 																	 --
--  06-01-17 : déclaration de la fonction de conversion d'un lot d'images vectorielles en matricielles    	     --
--  																											 --
-----------------------------------------------------------------------------------------------------------------*/


/*________________________________________________________________________________________________________
__ (1) Synthaxe des fichiers "image vectorielle" : (copié de l'énoncé du projet)						__
__ 																										__
__ L’image vectorielle sera décrite dans un fichier de texte dont la première ligne comportera			__
__ quatre entiers indiquant respectivement la largeur et la hauteur de l’image, le plus grand numéro	__
__ autorisé pour une couleur et le numéro de la couleur utilisée pour le fond de l’image. 				__
__ Chacune des lignes suivantes donnera la description d’une figure en suivant la syntaxe ci-dessous :  __
__ d x y r c 																							__
__ d indique qu’il s’agit d’un disque ; x et y sont les coordonnées entières du centre du disque ; 		__
__ r et c sont deux entiers qui indiquent respectivement le rayon et la couleur utilisée pour sont 		__
__ intérieur.																							__
__ r x y l h c 																							__
__ r indique qu’il s’agit d’un rectangle ; x et y sont les coordonnées entières du sommet supérieur		__
__ gauche ; l et h sont deux entiers qui indiquent respectivement la largeur et la hauteur  			__
__ du rectangle ; c est la couleur utilisée pour son intérieur.											__
__ 																										__
__ 																										__
__ (2) Synthaxe des fichiers "image matricielle" : (https://fr.wikipedia.org/wiki/Portable_pixmap)		__
__ 																										__
__ Les fichiers au format PNM sont composés sur la même base :											__		
__ * le nombre magique du format (deux octets) : il indique le type de format (PBM, PGM, ou PPM)        __
__ 	et la variante (binaire ou ASCII) ;																	__
__ * un caractère d'espacement (espace, tabulation, nouvelle ligne) ; 									__
__ * la largeur de l'image (nombre de pixels, écrit explicitement sous forme d'un nombre  				__
__ 	en caractères ASCII) ; 																				__
__ * un caractère d'espacement ; 																		__
__ * la hauteur de l'image (idem) ; 																	__
__ * un caractère d'espacement ; 																		__
__ * les données de l'image : succession des valeurs associées à chaque pixel, l'image est codée  		__
__ 	ligne par ligne en partant du haut, chaque ligne est codée de gauche à droite. 						__
__ Toutes les lignes commençant par croisillon # sont ignorées (lignes de commentaires).				__
__ 																										__
__ Ici on s'intéressera au format PGM, plus précisement P2 (images en nuances de gris, fichier ASCII)	__
________________________________________________________________________________________________________*/



/********************************************
	Prototypes des fonctions pour le mode batch
*********************************************/


void charger_batch(liste_t *, dessin_t *, char *);


void sauver_batch(liste_t, dessin_t, char *);


void conversion_vect_mat(liste_t *, dessin_t *, char *);

#endif