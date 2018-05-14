#include <cmath>
#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "cellule.h"

using namespace std;
/*#############################################*/
/*               CONSTRUCTORS                  */
/*#############################################*/
Cellule::Cellule(){
	genotype_ = 'S';
	reseauMet_["Glucose"]=0.;
	reseauMet_["Acetate"]=0.;
	reseauMet_["Ethanol"]=0.;
 }

Cellule::Cellule(char gen){//preconditions: gen='L' ou 'S' ou 'N'(Nothing)
    genotype_ = gen;
    reseauMet_["Glucose"]=0.;
    reseauMet_["Acetate"]=0.;
    reseauMet_["Ethanol"]=0.;
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

float Cellule::get_Glucose(){
	return reseauMet_["Glucose"];
}

float Cellule::get_Acetate(){
	return reseauMet_["Acetate"];
}

float Cellule::get_Ethanol(){
	return reseauMet_["Ethanol"];
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



//méthode:
bool Cellule::roll_a_dice(float P){
	float lancer = rand() %100;
	bool result;
	if (lancer<=P*100){
		//cout<<"true"<<endl;
		result=true;
	}else{
		result=false;
		//cout<<"false"<<endl;
	}
	return result;
}

