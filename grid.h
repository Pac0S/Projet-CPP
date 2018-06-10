#ifndef GRID_H
#define GRID_H

#include <map>
#include <vector>
#include <set>

#include "cellule.h"
using namespace std;


struct Case//pour manipuler on fait NomCase.cel ou NomCase.metab
{
    Cellule* cel_;
    map<char,float> metab_;

};


class Grid {
	public :


/*#############################################*/
/*             CONSTRUCTORS                    */
/*#############################################*/

		Grid(int T, float A_init);
	
/*#############################################*/
/*             DESTRUCTOR                      */
/*#############################################*/

		~Grid();

/*#############################################*/
/*                  METHODS                    */
/*#############################################*/
		void step();
		void run();
		void diffusion();
		void dying();
		void metaboliser();
		void division();
		void lavage();


/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/

		int get_taille();
		float get_coeff_diff();
		float get_p_death();
		float get_p_mut();
		float get_W_min();
		float get_Raa();
		float get_Rab();
		float get_Rbb();
		float get_Rbc();

/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/



/*#############################################*/
/*                   DISPLAY                   */
/*#############################################*/

		string zoliaffissage();
		string zoliaffissagemet();

	protected :
		

/*#############################################*/
/*                 ATTRIBUTES                  */
/*#############################################*/
		int taille_;
		float coeff_diff_;
		float p_death_;
		float p_mut_;
		float W_min_; //Fitness minimum
		unsigned int temps_; // Temps de simulation par intervalles de 0.1. Apres T pas de temps (T E [1,1500]),réinitialisation de l'environnement. Fin de la simulation à t = 5000. 
		map<string,float> taux_meta_;
		vector<vector<Case>> grille_;
		float A_init_; //Concentration initiale en A dans chaque Case
		int T_;
		unsigned int temps_simulation_;
		vector<vector<int>> coord_dead_cells_; //Stocke les coordonnées des cellules mortes non remplacées
		int max_L_lvg; //Nb maximum de L atteint avant un lavage, 0 si mort des cellules avant le premier lavage
};

#endif
