#include <iostream>
#include <cmath>
#include <vector>

#include "grid.h"




/*#############################################*/
/*             CONSTRUCTORS                    */
/*#############################################*/

Grid::Grid(){
	taille_= 32;
	coeff_diff_=0.5;
	p_death_=0.;
	p_mut_=0.;
	W_min_=0.1; //Fitness minimum
	taux_meta_["Raa"]=1;
	taux_meta_["Rab"]=1;
	taux_meta_["Rbb"]=1;
	taux_meta_["Rbc"]=1;
	/*vector< vector<Case> > grille(taille_, vector<Case>(taille_));
	for (vector<vector<Case>>::iterator i =grille.begin();i!=grille.end();i++){
		for (vector<Case>::iterator j =(*i).begin();j!=(*i).end();j){//on parcourt toute les cases
			cellule c ('L');//a changer pour avoir du 50 50
	   	   *((*j).cel)=c;
	   	   vector<float> metab(3);
	   	   metab[0]=0;
	   	   metab[1]=1;
	   	   metab[2]=2;
	   	   (*j).metab=metab;
	   }
	   	   
   }
	grille_=grille;*/
	
}
	


/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/

int Grid::get_taille(){
	return taille_;
}
	
	
float Grid::get_coeff_diff(){
	return coeff_diff_;
}
	
	
float Grid::get_p_death(){
	return p_death_;
}
	
	
float Grid::get_p_mut(){
	return p_mut_;
}
	
	
float Grid::get_W_min(){
	return W_min_;
}
	
	
float Grid::get_Raa(){
	return taux_meta_["Raa"];
}
	
	
float Grid::get_Rab(){
	return taux_meta_["Rab"];
}
	
float Grid::get_Rbb(){
	return taux_meta_["Rbb"];
}
	
float Grid::get_Rbc(){
	return taux_meta_["Rbc"];
}
/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/



/*#############################################*/
/*                   DISPLAY                   */
/*#############################################*/



/*#############################################*/
/*                  METHODS                    */
/*#############################################*/
