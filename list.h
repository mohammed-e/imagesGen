#ifndef DEF_LIST
#define DEF_LIST									


/*------------------------------------------------------------------------------------------------------
--  list.h : bibliothèque contenant la définition des structures de données utilisées dans le projet  --
--  				+ les prototypes des fonctions permettant l'exploitation de la structure liste_t  --
--  																								  --
--																									  --
--																									  --
--  18-12-16 : création du fichier list.h															  --
--	18-12-16 : définition des structures nature_t, figure_t, maillon_t, liste_t 		 			  --
--							+ déclarations de toutes les fonctions de gestion de liste 				  --
--  25-12-16 : définition de la structures dessin_t  												  --
--  25-12-16 : v.1.0 terminée et fonctionnelle														  --
------------------------------------------------------------------------------------------------------*/



/*************************************************************
	Definition de la structure des parametres généraux du dessin
**************************************************************/

typedef struct dessin_s{								
	int largeur;
	int hauteur;
	int couleur_max;		/* définit l'intensité maximale du niveau de gris (0 = noir / 255 = blanc) */
	int couleur_fond;
}dessin_t;


/**************************************
	Definition du type nature des figures
***************************************/

typedef enum nature_e{
	RECTANGLE,
	DISQUE
}nature_t;


/****************************************
	Definition de la structure d'une figure
*****************************************/

typedef struct figure_s{
	nature_t forme;
	int abs;							/* abscisse du point d'ancrage de la figure dans le dessin */
	int ord;							/* ordonnée du point d'ancrage de la figure dans le dessin */
	int rayon;							/* si la figure est un disque */
	int longueur;						/* si la figure est un rectangle */
	int hauteur;						/* si la figure est un rectangle */
	int couleur;
}figure_t;


/*********************************************************************************************
	Définition de la structure d'une liste simplement chaînée dont les éléments sont des figures
**********************************************************************************************/

typedef struct maillon_s{		/* un maillon contient une figure et un pointeur sur la suivante */
	figure_t elem;
	struct maillon_s *suiv;
}maillon_t;

typedef struct liste_s{			/* une liste de figure représente un dessin/image ; on a directement accès à la première/dernière figure et à la taille de la liste */
	unsigned int longueur;		/* <=> nombre de figures */
	maillon_t *premier;
	maillon_t *dernier;
}liste_t;



/**********************************************
	Prototypes des fonctions de gestion de liste
***********************************************/


liste_t creer_liste();

void afficher_liste(liste_t);

void ajouter_fin(figure_t, liste_t *);

void supprimer_debut(liste_t *);

void detruire_liste(liste_t *);

void deplacer(liste_t *, liste_t *);


#endif