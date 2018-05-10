#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>

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
	for (vector<vector<Case>>::iterator i =grid.begin();i!=grid.end();i++){
		for (vector<Case>::iterator j =i->begin();j!=i->end();j++){//on parcourt toutes les cases
			Cellule* c = new Cellule('L');//a changer pour avoir du 50 50
			j->cel_=c;
			map<char,float> metab;
			metab['A']=25; // -> A initial mis dans chaque case. Concentration ???
			metab['B']=25;
			metab['C']=2.;
			j->metab_=metab;
		} 	   
	}
	grille_=grid;
}
	
void Grid::step(float Pdeath, float Pmut){ // Pas nécessaire Pdeath et Pmut, ce sont des attributs de la classe
	//diffusion metabolite
	diffusion();
	
	//mort des cellules
	list<Cellule*> dead_cells;
	for (unsigned int i(0);i<taille_;i++){
		//for (unsigned int j(0);j<taille_;j++){
		for (vector<Case>::iterator j =grille_[i].begin();j!=grille_[i].end();j++){//on parcourt la grille
			if(j->cel_->is_dead(Pdeath)){//si la cellule meurt
				//map<string,float> reseau=j->cel_->getReseauMet();
				
				
				//Cellule* c1 = (grille_[i][j]).cel_;
				
				//cout<<c1->getFitness()<<endl;
				
				j->metab_['A']+=j->cel_->getReseauMet()["Glucose"];
				j->metab_['B']+=j->cel_->getReseauMet()["Acetate"];
				j->metab_['C']+=j->cel_->getReseauMet()["Ethanol"];
				dead_cells.push_back((*j).cel_);//on l'ajoute à la liste
				cout<<dead_cells.size()<<endl; //Nombre de cellules mortes
				j->cel_->set_Genotype('K');
			}
		}
	}

		//on conserve les coordonnées où il y a mort dans un conteneur pour l'etape d'apres (list de paire d'int?)
	//faire un rdm pour savoir quelle case vide on traite en premier, puis comparer les getfitness de toute les cellules autour
		//faire un constructeur divide, qui prend en entrée une cellule et Pmut et qui sort une copie avec moitié moins de métabolite et eventuellement muté (L->s et s->L)
		//on fait &grille_[coordonnées mortes].cel=cmere.divide()
		//&grille_[coordonnées mère].cel=cmere.divide()
	//fonctionnement metabolique: !!dt=0.1!!
	/*for(int i = 0; i < 10 ; i++){ 
	  for (vector<vector<Case>>::iterator i =grille_.begin();i!=grille_.end();i++){
		  for (vector<Case>::iterator j =i->begin();j!=i->end();j++){
		    if (j->cel_->getGen()=='L'){//Cas ou la cellule est de type Ga (Large)
		    //Stockage des données au debut du pas de temps
		      float A_out = j->metab_['A']; //Quantite de Glucose dans la case j
		      float A_in = j->cel_->get_Glucose(); //Quantite de Glucose dans la cellule de la case j
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
		      float B_in = j->cel_->get_Acetate(); //Quantite d'Acetate dans la cellule de la case j
		    //Calculs du fonctionnement metabolique
		      j->metab_['B'] = B_out * (1 - taux_meta_["Rbb"]);
		      float dB = B_in + (B_out * taux_meta_["Rbb"] - B_in * taux_meta_["Rbc"]);
		      (j->cel_)->set_Acetate(dB);//Quantite d'acetate dans la cellule
		      float dC = B_in * (1 + taux_meta_["Rbc"]);
		      (j->cel_)->set_Ethanol(dC);//Quantite d'ethanol dans la cellule
		    }
		  }
	  }
  }*/


}


void Grid::diffusion(){

/*tableau de taille_ * taille_ contenant les concentration des 3 métabolites 
A, B et C pour chaque case.*/
	vector<vector<Case>> metab_t_plus_un(taille_, vector<Case>(taille_)); 
	
	//Parcours des cases de notre grille (t)
	for (int i1=0;i1<taille_;++i1){
		for (int j1=0;j1<taille_;++j1){
		
			//Copie des concentrations de t en t+1
			(metab_t_plus_un[i1][j1]).metab_['A'] = (grille_[i1][j1]).metab_['A'];
			(metab_t_plus_un[i1][j1]).metab_['B'] = (grille_[i1][j1]).metab_['B'];
			(metab_t_plus_un[i1][j1]).metab_['C'] = (grille_[i1][j1]).metab_['C'];
			
			//Parcours des 9 cases autour de notre case (t)
			int x; //Abscisse du voisin qui se diffuse vers notre case
			int y; //Ordonnée du voisin qui se diffuse vers notre case
			for(int i2=-1;i2<=1;++i2){
				for(int j2=-1;j2<=1;++j2){
					if(i1+i2<0){ //Cas où on est sur la limite à gauche de la grille
						x=taille_ - 1; 
					}else if(i1+i2>taille_-1){ //Cas où on est sur la limite à droite de la grille
						x=0;
					}else{
						x=i1+i2;
					}
					if(j1+j2<0){ //Cas où on est sur la limite en bas de la grille
						y = taille_ - 1;
					}else if(j1+j2>taille_-1){ //Cas où on est sur la limite en haut de la grille
						y = 0;
					}else{
						y = j1+j2;
					}
					
					//Ajout des métabolites des cases voisines diffusés en t+1 et stockage dans le tableau en t+1
					(metab_t_plus_un[i1][j1]).metab_['A'] += grille_[x][y].metab_['A']*coeff_diff_;
					(metab_t_plus_un[i1][j1]).metab_['B'] += grille_[x][y].metab_['B']*coeff_diff_;
					(metab_t_plus_un[i1][j1]).metab_['C'] += grille_[x][y].metab_['C']*coeff_diff_;
				}
			}
			//Soustraction de la partie diffusée de la case
			metab_t_plus_un[i1][j1].metab_['A'] -= 9 * coeff_diff_ * grille_[i1][j1].metab_['A'];
			metab_t_plus_un[i1][j1].metab_['B'] -= 9 * coeff_diff_ * grille_[i1][j1].metab_['B'];
			metab_t_plus_un[i1][j1].metab_['C'] -= 9 * coeff_diff_ * grille_[i1][j1].metab_['C'];
		}
		
	}
	for (int i1=0;i1<taille_;++i1){
		for (int j1=0;j1<taille_;++j1){
		
			//Copie des concentrations de t+1 en t
			
			grille_[i1][j1].metab_['A']=metab_t_plus_un[i1][j1].metab_['A'];
			grille_[i1][j1].metab_['B']=metab_t_plus_un[i1][j1].metab_['B'];
			grille_[i1][j1].metab_['C']=metab_t_plus_un[i1][j1].metab_['C'];
		}
	}
}



/*#############################################*/
/*              DESTRUCTOR                     */
/*#############################################*/


Grid::~Grid(){
	for (vector<vector<Case>>::iterator i =grille_.begin();i!=grille_.end();++i){
		vector<Case> y_axis = *i;
		for (vector<Case>::iterator j =y_axis.begin();j!=y_axis.end();++j){
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
			}else if(colonne->cel_->getGen()=='S'){
				zoli+="S|";
			}else{
				zoli+="X|";
			}
		}
		zoli+='\n';
	}
	for (int j(0);j<taille_*2+1;j++){
		zoli+='-';
	}
	return zoli;
}


string Grid::zoliaffissagemet(){
	string zolimet = "";
	zolimet+="G";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\tA";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\tE";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\n";
	for (int i(0);i<taille_;i++){
		for (int l(0);l<3;l++){
			zolimet+="|";
			for (int j(0);j<taille_;j++){
				int a = int(grille_[i][j].metab_['A'+l]);
				zolimet+=to_string(a);
				zolimet+="|";
			}
			zolimet+="\t";
		}
		zolimet+="\n";
		for (int k(0);k<3;k++){
			for (int l(0);l<taille_*2+1;l++){
				zolimet+="-";
			}
			zolimet+="\t";
		}

		zolimet+="\n";
	}
	return zolimet;
}



/*#############################################*/
/*                  METHODS                    */
/*#############################################*/



