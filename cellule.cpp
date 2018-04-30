#include "cellule.h"
#include <cmath>
#include <map>
#include <iostream>
#include <cstdlib>
using namespace std;
/*#############################################*/
/*               CONSTRUCTORS                  */
/*#############################################*/
cellule::cellule(){
  genotype_ = 'S';
  reseauMet_["Glucose"]=0.;
  reseauMet_["Acetate"]=0.;
  reseauMet_["Ethanol"]=0.;
  }

cellule::cellule(char gen){//preconditions: gen='L' ou 'S'
    genotype_ = gen;
    reseauMet_["Glucose"]=0.;
    reseauMet_["Acetate"]=0.;
    reseauMet_["Ethanol"]=0.;
  
}


/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/
float cellule::getFitness() {
	float fitness;
	if (genotype_=='L'){
		fitness= reseauMet_["Acetate"];
	}else{
		fitness= reseauMet_["Ethanol"];
	}
	return fitness;
}

char cellule::getGen(){
	return genotype_;
}

map<string,float> cellule::getReseauMet(){
	return reseauMet_;
}





/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/

/*#############################################*/
/*                  DISPLAY                    */
/*#############################################*/

/*#############################################*/
/*                   METHODS                   */
/*#############################################*/



//méthode:
bool cellule::is_dead(float Pdeath){
	float lancer = rand() %100;
	bool death;
	if (lancer<=Pdeath*100){
		death=true;
	}else{
		death=false;
	}
	return death;
}
bool cellule::is_mutating(float Pmut){
	float lancer = rand() %100;
	bool mutation;
	if (lancer<=mutation*100){
		mutation=true;
	}else{
		mutation=false;
	}
	return mutation;
}
