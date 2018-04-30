#ifndef GRID_H
#define GRID_H

#include <map>
#include <vector>
#include "cellule.h"
#include "metabolite.h"
struct Case//pour manipuler on fait NomCase.cel ou NomCase.metab
{
    cellule* cel;
    vector<float> metab[3];
};


class Grid {
	public :


/*#############################################*/
/*             CONSTRUCTORS                    */
/*#############################################*/

		Grid();

	
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



/*#############################################*/
/*                  METHODS                    */
/*#############################################*/

	protected :
		

/*#############################################*/
/*                 ATTRIBUTES                  */
/*#############################################*/
		int taille_;
		float coeff_diff_;
		float p_death_;
		float p_mut_;
		float W_min_; //Fitness minimum
		map<string,float> taux_meta_;
	


};

#endif
