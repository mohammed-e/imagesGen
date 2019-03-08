#include "list.h"
#include "save.h"

#ifndef DEF_USER
#define DEF_USER

/*-----------------------------------------------------------------------------------------------------------
--  user.h : bibliothèque contenant les prototypes des fonctions permettant l'implémentation du mode	   --
--						intéraction utilisateur															   --
--  																									   --
--																										   --
--																										   --
--  28-12-16 : création du fichier user.h																   --
--	28-12-16 : déclaration de toutes les fonctions sauf modifier_figure et changer_ordre_figure      	   --
--  04-01-17 : déclaraions des fonctions modifier_figure et changer_ordre_figure						   --
--  04-01-17 : v.1.0 terminée et fonctionnelle															   --
-----------------------------------------------------------------------------------------------------------*/



/**************************************************************
	Prototypes des fonctions pour le mode intéraction utilisateur
***************************************************************/


void afficher_presentation();

int afficher_menu_principal();

int afficher_menu_1();

void initialiser_parametres(dessin_t *);

int afficher_menu_2();

int afficher_menu_3();

void ajouter_figure(figure_t *, liste_t *, dessin_t *);

void supprimer_figure(liste_t *);

void afficher_liste_figure(liste_t);

void modifier_figure(figure_t *);

void changer_ordre_figure(liste_t *);

void interaction(int *, liste_t *, dessin_t *, figure_t *);


#endif