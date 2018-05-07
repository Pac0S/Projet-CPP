#include <iostream>
#include <cmath>
#include <vector>
#include "grid.h"
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
			map<char,float> metab(3);
			metab['A']=0.1; // Concentration ???
			metab['B']=0.1;
			metab['C']=0.1;
			j->metab_=metab;
		} 	   
	}
	grille_=grid;
}
	
void Grid::step(){
	//diffusion metabolite libre 
	//voir algo sur le pdf
	
	
	//mort des cellules
		//on conserve les coordonnées où il y a mort dans un conteneur pour l'etape d'apres (list de paire d'int?)
	//faire un rdm pour savoir quelle case vide on traite en premier, puis comparer les getfitness de toute les cellules autour
		//faire un constructeur divide, qui prend en entrée une cellule et Pmut et qui sort une copie avec moitié moins de métabolite et eventuellement muté (L->s et s->L)
		//on fait &grille_[coordonnées mortes].cel=cmere.divide()
		//&grille_[coordonnées mère].cel=cmere.divide()
	//fonctionnement metabolique:
		//!!dt=0.1!!



}

/*
void Grid::diffusion(){
tableau de taille_ * taille_ contenant les concentration des 3 métabolites 
	A, B et C pour chaque case.*/
	/*vector<vector<map<string,float>>> metab_t_plus_un(taille_, vector<map<string,float>>(taille_); 
	
	//Parcours des cases de notre grille (t)
	for (int i1=0;i1<taille_;++i1){
		for (int i2=0;i2<taille_;++i2){
		
			//Copie des concentrations de t en t+1
			metab_t_plus_un[i1][i2]['A'] = grille_[i][j].metab_['A'];
			metab_t_plus_un[i1][i2]['B'] = grille_[i][j].metab_['B'];
			metab_t_plus_un[i1][i2]['C'] = grille_[i][j].metab_['C'];
			
			//Parcours des 9 cases autour de notre case (t)
			for(int j1=-1;j1<=1;++j1){
				for(int j2=-1;j2<=1;++j2){
				
					//Ajout des métabolites des cases voisines diffusés en t+1 et stockage dans le tableau en t+1
					metab_t_plus_un[i1+j1][i2+j2]['A'] += grille_[i1+j1][i2+j2].metab_['A']*coeff_diff_;
					metab_t_plus_un[i1+j1][i2+j2]['B'] += grille_[i1+j1][i2+j2].metab_['B']*coeff_diff_;
					metab_t_plus_un[i1+j1][i2+j2]['C'] += grille_[i1+j1][i2+j2].metab_['C']*coeff_diff_;
				}
			}
		}
		//Soustraction de la partie diffusée de la case
		metab_t_plus_un[i1][i2]['A'] -= 9 * coeff_diff_ * grille_[i][j].metab_['A'];
		metab_t_plus_un[i1][i2]['B'] -= 9 * coeff_diff_ * grille_[i][j].metab_['B'];
		metab_t_plus_un[i1][i2]['C'] -= 9 * coeff_diff_ * grille_[i][j].metab_['C'];
	}
	for (int i1=0;i1<taille_;++i1){
		for (int i2=0;i2<taille_;++i2){
			//Copie des concentrations de t+1 en t
			grille_[i][j].metab_['A']=metab_t_plus_un[i1][i2]['A'];
			grille_[i][j].metab_['B']=metab_t_plus_un[i1][i2]['B'];
			grille_[i][j].metab_['C']=metab_t_plus_un[i1][i2]['C'];
		}
	}
}
*/


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




