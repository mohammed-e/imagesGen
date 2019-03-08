#include <stdio.h>
#include "list.h"

#ifndef DEF_SAVE
#define DEF_SAVE																													


/*-----------------------------------------------------------------------------------------------------------
--  save.h : bibliothèque contenant les prototypes des fonctions permettant le chargement et la sauvegarde --
--						de dessins sous forme vectorielle/matricielle (+ des fonctions intermédiaires) 	   --
--  																									   --
--																										   --
--																										   --
--  25-12-16 : création du fichier save.h																   --
--	25-12-16 : déclaration des fonctions de chargement et de sauvegarde sous forme vectorielle + openCheck --
--  30-12-16 : déclaration de la fonction de sauvegarde sous forme matricielle                             --
--  30-12-16 : v.1.0 terminée et fonctionnelle															   --
-----------------------------------------------------------------------------------------------------------*/



/******************************************************************
	Prototypes des fonctions de gestion des sauvegardes / chargements
*******************************************************************/


void openCheck(FILE *);

void charger_vect(liste_t *, dessin_t *);

void sauver_vect(liste_t, dessin_t);

void sauver_mat(liste_t, dessin_t);


#endif