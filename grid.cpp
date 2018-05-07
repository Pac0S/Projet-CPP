#include <iostream>
#include <cmath>
#include <vector>
#include "grid.h"
#include <list>
using namespace std;



static float A_init=25;

/*#############################################*/
/*             CONSTRUCTORS                    */
/*#############################################*/

Grid::Grid(){
	taille_= 4; //W=H
	coeff_diff_=0.1; //D
	p_death_=0.02;
	p_mut_=0.;
	W_min_=0.001; //Fitness minimum
	temps_=0.;
	taux_meta_["Raa"]=0.1;
	taux_meta_["Rab"]=0.1;
	taux_meta_["Rbb"]=0.1;
	taux_meta_["Rbc"]=0.1;
	
	
	vector<Case> y_axis(taille_);
	vector< vector<Case> > grid(taille_, y_axis);
	//vector< vector<Case> > grille(taille_, vector<Case>(taille_));
	for (vector<vector<Case>>::iterator i =grid.begin();i!=grid.end();++i){
		for (vector<Case>::iterator j =i->begin();j!=i->end();j++){//on parcourt toute les cases
			Cellule* c = new Cellule('L');//a changer pour avoir du 50 50
			j->cel_=c;
			map<char,float> metab;
			metab['A']=25; // -> A intitial mis dans chaque case Concentration ???
			metab['B']=1.;
			metab['C']=2.;
			j->metab_=metab;
		} 	   
	}
	grille_=grid;
}
	
void Grid::step(float Pdeath, float Pmut){
	//diffusion metabolite libre 
		//voir algo sur le pdf
	//mort des cellules
	list<Cellule*> dead_cells;
	for (unsigned int i(0);i<taille_;i++){
		for (vector<Case>::iterator j =grille_[i].begin();j!=grille_[i].end();j++){//on parcourt la grille
			if(j->cel_->is_dead(Pdeath)){//si la cellule meurt
				dead_cells.push_back((*j).cel_);//on l'ajoute à la liste
			}
		}
	}
		//on conserve les coordonnées où il y a mort dans un conteneur pour l'etape d'apres (list de paire d'int?)
	//faire un rdm pour savoir quelle case vide on traite en premier, puis comparer les getfitness de toute les cellules autour
		//faire un constructeur divide, qui prend en entrée une cellule et Pmut et qui sort une copie avec moitié moins de métabolite et eventuellement muté (L->s et s->L)
		//on fait &grille_[coordonnées mortes].cel=cmere.divide()
		//&grille_[coordonnées mère].cel=cmere.divide()
	//fonctionnement metabolique: !!dt=0.1!!
	for(int i = 0; i < 10 ; i++){ //
	  for (vector<vector<Case>>::iterator i =grille_.begin();i!=grille_.end();++i){
		  for (vector<Case>::iterator j =i->begin();j!=i->end();j++){
		    if (j->cel_->getGen()=='L'){//Cas ou la cellule est de type Ga (Large)
		    //Stockage des données au debut du pas de temps
		      float A_out = j->metab_['A']; //Quantite de Glucose dans la case j
		      float A_in = j->cel_->getReseauMet()["Glucose"]; //Quantite de Glucose dans la cellule de la case j
		    //Calculs du fonctionnement metabolique
		      j->metab_['A'] = A_out * (1 - taux_meta_["Raa"]);
		      float dA = A_in + (A_out * taux_meta_["Raa"] - A_in * taux_meta_["Rab"]);
		      j->cel_->set_Glucose(dA);
		      float dB = A_in * (1 + taux_meta_["Rab"]);
		      j->cel_->set_Acetate(dB);
		    }
		    else{ //Cas ou la cellule est de type Gb (Small)
		    //Stockage des données au debut du pas de temps
		      float B_out = j->metab_['B']; //Quantite d'Acetate dans la case j
		      float B_in = (j->cel_)->getReseauMet()["Acetate"]; //Quantite d'Acetate dans la cellule de la case j
		    //Calculs du fonctionnement metabolique
		      j->metab_['B'] = B_out * (1 - taux_meta_["Rbb"]);
		      float dB = B_in + (B_out * taux_meta_["Rbb"] - B_in * taux_meta_["Rbc"]);
		      (j->cel_)->set_Acetate(dB);//Quantite d'acetate dans la cellule
		      float dC = B_in * (1 + taux_meta_["Rbc"]);
		      (j->cel_)->set_Ethanol(dC);//Quantite d'ethanol dans la cellule
		    }
		  }
	  }
  }


}

/*#############################################*/
/*              DESTRUCTOR                     */
/*#############################################*/


Grid::~Grid(){
	for (vector<vector<Case>>::iterator i =grille_.begin();i!=grille_.end();++i){
		vector<Case> y_axis = *i;
		for (vector<Case>::iterator j =y_axis.begin();j!=y_axis.end();j++){
			Case here = *j;
			delete here.cel_;
		}
	}
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

string Grid::zoliaffissage(){//pas encore testé parce que le constructeur de grid est pas fini.
	string zoli = "";
	for (vector<vector<Case>>::iterator ligne =grille_.begin();ligne!=grille_.end();++ligne){
		for (int i(0);i<taille_*2+1;i++){
			zoli+='-';
		}
		zoli+='\n';
		zoli+='|';
		for (vector<Case>::iterator colonne = ligne->begin();colonne!=ligne->end();colonne++){
			if(colonne->cel_->getGen()=='L'){
				zoli+="L|";
			}else if((colonne->cel_)->getGen()=='S'){
				zoli+="S|";
			}
		}
		zoli+='\n';
	}
	for (int j(0);j<taille_*2+1;j++){
		zoli+='-';
	}
	return zoli;
}






/*#############################################*/
/*                  METHODS                    */
/*#############################################*/




