#include <stdlib.h>
#include <stdio.h>
#include "list.h"


/*------------------------------------------------------------------------------------------------------
--  list.c : fichier source contenant les définitions des fonctions permettant la gestion des liste   --
--  																								  --
--										 															  --
--																									  --
--  18-12-16 : création du fichier list.c															  --
--	19-12-16 :  implémentation de toutes les fonctions de gestion de liste 	 						  --
--  19-12-16 : v.1.0 terminée et fonctionnelle														  --
------------------------------------------------------------------------------------------------------*/



/**********************************************
	Définitions des fonctions de gestion de liste
***********************************************/


/* Créée une nouvelle liste
@renvoi : une liste vide
*/
liste_t creer_liste(){

	liste_t l;
	l.longueur = 0;
	l.premier = NULL;
	l.dernier = NULL;
	return l;
}


/* Affiche le contenu d'une liste (les figures qu'elle contient) en fonction de sa forme
@paramètre(s) : la liste de figures à afficher
*/
void afficher_liste(liste_t l){

	if(l.premier == NULL)
		putchar('\n');

	while(l.premier != NULL){
		if(l.premier->elem.forme == RECTANGLE){
			printf("r ");
			printf("%d, ", l.premier->elem.abs);
			printf("%d, ", l.premier->elem.ord);
			printf("%d, ", l.premier->elem.longueur);
			printf("%d, ", l.premier->elem.hauteur);
			printf("%d.\n", l.premier->elem.couleur);
		} 		      					
		else{
			printf("d ");
			printf("%d, ", l.premier->elem.abs);
			printf("%d, ", l.premier->elem.ord);
			printf("%d, ", l.premier->elem.rayon);
			printf("%d.\n", l.premier->elem.couleur);
		}
		l.premier = l.premier->suiv;
	}
}


/* Ajoute une figure à la fin d'une liste
@paramètre(s) : la figure à ajouter + l'adresse de la liste où l'ajouter
*/
void ajouter_fin(figure_t f, liste_t *l){

	maillon_t *new = (maillon_t *)malloc(sizeof(maillon_t));		/* pour ajouter une nouvelle figure, on alloue dynamiquement la taille nécessaire pour un pointeur de maillon */
	/* On remplie notre maillon (grâce à son adresse) avec les champs de la figure à ajouter */
	new->elem.forme = f.forme;
	new->elem.abs = f.abs;
	new->elem.ord = f.ord;
	new->elem.rayon = f.rayon;
	new->elem.longueur = f.longueur;
	new->elem.hauteur = f.hauteur;
	new->elem.couleur = f.couleur;
	new->suiv = NULL;
	/* Il ne reste plus qu'à placer notre maillon à la fin de notre liste ; on distingue le cas où la liste est vide des autres */
	if(l->premier == NULL){
		l->premier = new;
		l->dernier = new;
		l->longueur = l->longueur + 1;
	}
	else{
		l->dernier->suiv = new;
		l->dernier = new;
		l->longueur = l->longueur + 1;
	}
}


/* Supprimme la première figure d'une liste
@paramètre(s) : l'adresse de la liste dont l'on veut supprimer la première figure
*/
void supprimer_debut(liste_t *l){

	maillon_t *tmp = l->premier; 		/* on va utiliser un pointeur de maillon temporaire qui va permettre de ne pas perdre le premier maillon de notre liste */

	/* On va distinguer trois cas : si la liste est vide, si elle contient un seul maillon et si elle en contient plusieurs */
	if(l->premier == NULL)
		return ;
	else if(l->premier == l->dernier){
		free(l->premier);
		l->premier = NULL;
		l->dernier = NULL;
		l->longueur = l->longueur - 1;
	}
	else{
		tmp = l->premier->suiv;
		free(l->premier);
		l->premier = tmp;
		l->longueur = l->longueur - 1;
	}
}


/* Supprimme toutes les figures d'une liste
@paramètre(s) : l'adresse de la liste que l'on veut vider
*/
void detruire_liste(liste_t *l){

	if(l->premier != NULL){
		supprimer_debut(l);
		detruire_liste(l);
	}
}


/* Déplace la première figure d'une liste à la fin d'une seconde liste
@paramètre(s) : l'adresse de la liste de départ + l'adresse de la liste d'arrivée
*/
void deplacer(liste_t *l1, liste_t *l2){

	/* Cas 1 : la liste 1 est vide */
	if(l1->premier == NULL)
		return ;
	/* Cas 2 :  la liste 1 contient qu'un seul maillon et la 2 est vide */
	else if(l2->premier == NULL && l1->premier == l1->dernier){
		l2->premier = l1->premier;
		l2->dernier = l1->premier;
		l1->premier = l1->premier->suiv; /* <=> l1->premier = NULL */
		l1->dernier = l1->premier;			 /* <=> l1->dernier = NULL */
		l2->dernier->suiv = NULL;
		l1->longueur = l1->longueur - 1;
		l2->longueur = l2->longueur + 1;
	}
	/* Cas 3 : la liste 1 contient au moins deux maillons et la liste 2 est vide */
	else if(l2->premier == NULL){
		l2->premier = l1->premier;
		l2->dernier = l1->premier;
		l1->premier = l1->premier->suiv;
		l2->dernier->suiv = NULL;
		l1->longueur = l1->longueur - 1;
		l2->longueur = l2->longueur + 1;
	}
	/* Cas 4 : la liste 1 contient qu'un seul maillon et la 2 au moins 1 */
	else if(l1->premier == l1->dernier){
		l2->dernier->suiv = l1->premier;
		l2->dernier = l1->premier;
		l1->premier = l1->premier->suiv;	/* <=> l1->premier = NULL */
		l1->dernier = l1->premier;				/* <=> l1->dernier = NULL */
		l2->dernier->suiv = NULL;
		l1->longueur = l1->longueur - 1;
		l2->longueur = l2->longueur + 1;
	}
	/* Cas 5 : la liste 1 contient au moins 2 maillons et la 2 au moins 1 */
	else{
		l2->dernier->suiv = l1->premier;
		l2->dernier = l1->premier;
		l1->premier = l1->premier->suiv;
		l2->dernier->suiv = NULL;
		l1->longueur = l1->longueur - 1;
		l2->longueur = l2->longueur + 1;
	}
}