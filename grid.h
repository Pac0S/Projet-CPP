#ifndef GRID_H
#define GRID_H

#include <map>
#include <vector>
#include "cellule.h"
#include "metabolite.h"
using namespace std;


struct Case//pour manipuler on fait NomCase.cel ou NomCase.metab
{
    Cellule* cel_;
    vector<float> metab_;
};


class Grid {
	public :


/*#############################################*/
/*             CONSTRUCTORS                    */
/*#############################################*/

		Grid();

	
	
/*#############################################*/
/*             DESTRUCTOR                      */
/*#############################################*/

		~Grid();


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

/*#############################################*/
/*                  METHODS                    */
/*#############################################*/
		void step(float Pdeath,float Pmut);
		//
		//



	protected :
		

/*#############################################*/
/*                 ATTRIBUTES                  */
/*#############################################*/
		int taille_;
		float coeff_diff_;
		float p_death_;
		float p_mut_;
		float W_min_; //Fitness minimum
		float temps_; // Temps de simulation par intervalles de 0.1. Apres T pas de temps (T E [1,1500]),réinitialisation de l'environnement. Fin de la simulation à t = 5000.
		map<string,float> taux_meta_;
		vector<vector<Case>> grille_;
	


};

#endif
