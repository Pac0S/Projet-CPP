#include <cmath>
#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "cellule.h"

using namespace std;

int Cellule::nb_cellules_L_ = 0;
int Cellule::nb_cellules_S_ = 0;

/*#############################################*/
/*               CONSTRUCTORS                  */
/*#############################################*/
Cellule::Cellule(char gen){//preconditions: gen='L' ou 'S'
    genotype_ = gen;
    // Mise à jour du nombre de cellules
    if (genotype_ == 'L'){
      nb_cellules_L_ ++;
    } else{
      nb_cellules_S_ ++;
    }
    reseauMet_["Glucose"]=0.;
    reseauMet_["Acetate"]=0.;
    reseauMet_["Ethanol"]=0.;
    alive_=true;
}

Cellule::Cellule(Cellule* mere, float& p_mut){
	//Division par deux des quantités de métabolites dans la cellule mere
	(*mere).reseauMet_["Glucose"]=(*mere).reseauMet_["Glucose"]/2;
	(*mere).reseauMet_["Acetate"]=(*mere).reseauMet_["Acetate"]/2;
	(*mere).reseauMet_["Ethanol"]=(*mere).reseauMet_["Ethanol"]/2;
	reseauMet_ = (*mere).reseauMet_;
	genotype_ = (*mere).genotype_;
	// Mise à jour du nombre de cellules
	if (genotype_ == 'L'){
		nb_cellules_L_ ++;
	} else{
		nb_cellules_S_ ++;
	}
	
	float who_mutates = rand() %100; // Les 2 cellules sont identiques, il faut voir si l'une des deux mute.

	if(who_mutates < 50){ // La fille mute
		mutates(p_mut);
	}else{ // La mere mute
		mere->mutates(p_mut);
	}
	alive_=true;
}


/*#############################################*/
/*               DESTRUCTOR                    */
/*#############################################*/
Cellule::~Cellule(){
  if (genotype_ == 'L'){
    nb_cellules_L_ --;
  } else{
    nb_cellules_S_ --;
  }
}


/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/
float Cellule::getFitness() {
	float fitness;
	if (genotype_=='L'){
		fitness= reseauMet_["Acetate"];
	}else{
		fitness= reseauMet_["Ethanol"];
	}
	return fitness;
}

char Cellule::getGen(){
	return genotype_;
}

map<string,float> Cellule::getReseauMet(){
	return reseauMet_;
}
bool Cellule::is_alive(){
	return alive_;	
}

float Cellule::get_Glucose(){
	return reseauMet_["Glucose"];
}

float Cellule::get_Acetate(){
	return reseauMet_["Acetate"];
}

float Cellule::get_Ethanol(){
	return reseauMet_["Ethanol"];
}

unsigned int Cellule::get_nb_cellules_L(){
  return nb_cellules_L_;
}
unsigned int Cellule::get_nb_cellules_S(){
  return nb_cellules_S_;
}
unsigned int Cellule::get_nb_total(){
  return nb_cellules_S_ + nb_cellules_L_;
}
/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/
void Cellule::set_Glucose(float a){
	reseauMet_["Glucose"]= a;
}

void Cellule::set_Acetate(float b){
	reseauMet_["Acetate"]= b;
}

void Cellule::set_Ethanol(float c){
	reseauMet_["Ethanol"]= c;
}

void Cellule::set_Genotype(char g){
	genotype_=g;
}
/*#############################################*/
/*                  DISPLAY                    */
/*#############################################*/

/*#############################################*/
/*                   METHODS                   */
/*#############################################*/



/*
* Effectue une epreuve de Bernouilli avec une 
* probabilite de reussite p_reussite
* Retourne un booleen
*/
bool Cellule::roll_a_dice(float p_reussite){
	float lancer = rand() %100;
	bool result;
	if (lancer<=p_reussite*100){
		result=true;
	}else{
		result=false;
	}
	return result;
}

void Cellule::kill(){
	alive_=false;
	if(genotype_=='S'){
		nb_cellules_S_ --;
	}else if(genotype_=='L'){
		nb_cellules_L_ --;
	}		
}

/*
* Mutation de la cellule selon la probabilite Pmut
* Utilise la fonction roll_a_dice
*/
void Cellule::mutates(float Pmut){
	if (roll_a_dice(Pmut)){
		if(genotype_=='S'){
			genotype_='L';
		}else{
			genotype_ = 'S';
		}
	}
}
