#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm> 

#include "grid.h"

using namespace std;



static float A_init=25;

/*#############################################*/
/*             CONSTRUCTORS                    */
/*#############################################*/

/************************ Constructeur par défaut ************************/
/*                                                                       */
/* Cree une grille torique de taille taille_ * taille_ qui possede des   */
/* parametres tels que :                                                 */
/*    coeff_diff : taux de diffusion des cellules dans leur environnement*/
/*    p_death : probabilité de décès d'un individu                       */
/*    p_mut : probabilité de mutation de deux individus fils apres une   */
/*            division                                                   */
/*    W_min : seuil minimum de la fitness pour un individu               */
/*    temps : temps initial                                              */
/*    taux_meta_ : map contenant les taux permettant de convertir ou     */
/*                 d'importer les ressources de l'environnement          */
/*                                                                       */
/*  La grille contient 50% d'individus de type S et 50% d'individus de   */
/* type L. Chaque case de la grille contient une cellule.                */
/* Il n'y a pas de cases vides au temps initial.                         */ 
/*                                                                       */
/*************************************************************************/

Grid::Grid(){
	taille_= 4; //W=H
	coeff_diff_=0.1; //D
	p_death_=0.02;
	p_mut_=0.;
	W_min_=0.001; //Fitness minimum
	temps_= 1;
	taux_meta_["Raa"]=0.1;
	taux_meta_["Rab"]=0.1;
	taux_meta_["Rbb"]=0.1;
	taux_meta_["Rbc"]=0.1;
	
	
	vector<Case> y_axis(taille_);
	vector< vector<Case> > grid(taille_, y_axis);
	
	// On stocke les genotypes de chaque cellule à l'initialisation dans un vecteur
	vector<char> genotypes(taille_*taille_); 
	
	/*
	* Precondition : On suppose une grille possédant un nombre de cases pair
	* On obtient ainsi le meme nombre de cellules L et S
	*/
	for(vector<char>::iterator it=genotypes.begin(); it!= genotypes.begin() + (taille_*taille_/2);it++){ 
		*it = 'S';	
	}
	for(vector<char>::iterator it=genotypes.begin() + (taille_*taille_/2); it!= genotypes.end();it++){ 
		*it = 'L';	
	}
	// On mélange aleatoirement les 50% S et les 50% L dans le vecteur
	random_shuffle(genotypes.begin(),genotypes.end()); 
	
	for(vector<char>::iterator it=genotypes.begin(); it!= genotypes.end();it++){ 
		cout << *it << endl;
	}
	
	int count = 1;
	vector<char>::iterator it = genotypes.begin(); // Itérateur qui parcoure le vecteur des genotypes
	//on parcourt toutes les cases de la grille
	for (vector<vector<Case>>::iterator i =grid.begin();i!=grid.end();i++){
		for (vector<Case>::iterator j =i->begin();j!=i->end();j++){ 
			Cellule* c = new Cellule(*it); // On copie le génotype dans la nouvelle cellule
			j->cel_=c; // On ajoute cette cellule dans la case
			map<char,float> metab;
			metab['A']=25; // -> Quantite de A initial mis dans chaque case. Concentration ???
			metab['B']=25;
			metab['C']=2.;
			j->metab_=metab;		
			it++; // On passe au génotype suivant
			cout << count << " Cells added" << endl;
			count++;
		} 	   
	}
	grille_=grid;
	cout << "DONE !" << endl;
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
/*                  METHODS                    */
/*#############################################*/

/******************************** Step **********************************/
/* Représente tous les evenements se deroulant dans un pas de temps.    */
/* Celui-ci comprend :                                                  */
/*    - la diffusion des cellules dans leur environnement               */
/*    - la mort des cellules (selon p_death)                            */
/*    - le fonctionnement metabolique des cellules (precision : celui-ci*/
/*       se déroule en un dixième de temps. Les individus metabolisent  */
/*       donc 10 fois en un pas de temps)                               */
/************************************************************************/
void Grid::step(float Pdeath, float Pmut){ // Pas nécessaire Pdeath et Pmut, ce sont des attributs de la classe
	//diffusion metabolite//
	diffusion();
	
	//mort des cellules//
	vector<vector<int>> coord_dead_cells = dead_position(Pdeath);
    
    /**************** Notes a nous-memes ********************/
		//on conserve les coordonnées où il y a mort dans un conteneur pour l'etape d'apres (list de paire d'int?)
	  //faire un rdm pour savoir quelle case vide on traite en premier, puis comparer les getfitness de toute les cellules autour
		//faire un constructeur divide, qui prend en entrée une cellule et Pmut et qui sort une copie avec moitié moins de métabolite et eventuellement muté (L->s et s->L)
		//on fait &grille_[coordonnées mortes].cel=cmere.divide()
		//&grille_[coordonnées mère].cel=cmere.divide()
		/********************************************************/
	
	//fonctionnement metabolique: !!dt=0.1!!
	for(int i = 0; i < 10 ; i++){ 
	  metaboliser();
  }
}

/**************** Fonctions utilisees par step() ************************/

/************* Diffusion des cellules **************/

void Grid::diffusion(){

  /* tableau de taille_ * taille_ contenant les concentrations des 
  *  3 métabolites A, B et C pour chaque case.*/
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


/*************Position des cellules mortes************/

vector<vector<int>> Grid::dead_position(float Pdeath){
  vector<vector<int>> coord_dead_cells;
	for (unsigned int i(0);i<taille_;i++){
		for (unsigned int j(0);j<taille_;j++){
			if(grille_[i][j].cel_->roll_a_dice(Pdeath)){//si la cellule meurt
				grille_[i][j].metab_['A']+=grille_[i][j].cel_->getReseauMet()["Glucose"];
				grille_[i][j].metab_['B']+=grille_[i][j].cel_->getReseauMet()["Acetate"];
				grille_[i][j].metab_['C']+=grille_[i][j].cel_->getReseauMet()["Ethanol"];
				vector<int> coord;
				coord.push_back(i);
				coord.push_back(j);
				coord_dead_cells.push_back(coord);
			}
		}
	}
	return coord_dead_cells;
}

/***********Metabolisme d'une cellule !!!!! dt = 0.1 !!!!!************/

void Grid::metaboliser(){
  for (vector<vector<Case>>::iterator i =grille_.begin();i!=grille_.end();i++){
    for (vector<Case>::iterator j =i->begin();j!=i->end();j++){
	    if (j->cel_->getGen()=='L'){//Cas ou la cellule est de type Ga (Large)
	    //Stockage des données au debut du pas de temps
	      float A_out = j->metab_['A']; //Quantite de Glucose dans la case j
	      float A_in = j->cel_->get_Glucose(); //Quantite de Glucose dans la cellule de la case j
	    //Calculs du fonctionnement metabolique suivant les formules fournies
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
	    //Calculs du fonctionnement metabolique suivant les formules fournies
	      j->metab_['B'] = B_out * (1 - taux_meta_["Rbb"]);
	      float dB = B_in + (B_out * taux_meta_["Rbb"] - B_in * taux_meta_["Rbc"]);
	      (j->cel_)->set_Acetate(dB);//Quantite d'acetate dans la cellule
	      float dC = B_in * (1 + taux_meta_["Rbc"]);
	      (j->cel_)->set_Ethanol(dC);//Quantite d'ethanol dans la cellule
	    }
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
	zolimet+="A";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\tB";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\tC";
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

