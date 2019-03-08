#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "save.h"
#include "user.h"
#include "batch.h"



/*------------------------------------------------------------------------------------------------
--  drawer.c : fichier principal du projet contenant le mode interactif et le mode batch		--
--  																							--
--																								--
--																								--
--  28-12-16 : création du fichier drawer.c														--
--	28-12-16 : implémentation du mode interactif sans les options de sauvegarde matricielle et 	--
--                de modification / échange de figures                                          --
--  04-01-17 : implémentation du mode interactif complet                                        --
--  06-01-17 : implémentation du mode batch														--
--  xx-xx-xx : v.1.0 terminée et fonctionnelle													--
------------------------------------------------------------------------------------------------*/



int main(int argc, char *argv[])
{

  /* Déclaration et initialisation des variables */

  liste_t l = creer_liste();
  dessin_t dessin = {0};
  figure_t fig = {RECTANGLE,0,0,0,0,0,0};    /* RECTANGLE par défault */

  /*******************/
  /* Mode Interactif */
  /*******************/

  if(argc == 1){

		int choix = 0;

		afficher_presentation();
		choix = afficher_menu_principal();

		while(choix != 4){
			interaction(&choix, &l, &dessin, &fig);
		}
    
  }


  /*****************************************************************************/
  /* Mode batch: convertit un lot d'images vectorielles en images matricielles */
  /*****************************************************************************/

  else{

      conversion_vect_mat(&l, &dessin, argv[1]);

      puts("\nVotre image vectorielle a été convertie avec succès");

  }


  puts("\nAu revoir !\n");
  
  return EXIT_SUCCESS;
}
