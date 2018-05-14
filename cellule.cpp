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
    reseauMet_["Glucose"]=0.5;
    reseauMet_["Acetate"]=0.5;
    reseauMet_["Ethanol"]=0.5;
}

Cellule::Cellule(Cellule& mere, float p_mut){
	//Division par deux des quantités de métabolites dans la cellule mere
	mere.reseauMet_["Glucose"]=mere.reseauMet_["Glucose"]/2;
	mere.reseauMet_["Acetate"]=mere.reseauMet_["Acetate"]/2;
	mere.reseauMet_["Ethanol"]=mere.reseauMet_["Ethanol"]/2;
	reseauMet_ = mere.reseauMet_;
	genotype_ = mere.genotype_;
	
	float who_mutates = rand() %100; // Les 2 cellules sont identiques, il faut voir si l'une des deux mute.

	if(who_mutates < 50){ // La fille mute
		mutates(p_mut);
	}else{ // La mere mute
		mere.mutates(p_mut);
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
bool Cellule::is_dead(float Pdeath){
	float lancer = rand() %100;
	bool death;
	if (lancer<=Pdeath*100){
		//cout<<"true"<<endl;
		death=true;
	}else{
		death=false;
		//cout<<"false"<<endl;
	}
	return death;
}


void Cellule::mutates(float Pmut){
	float lancer = rand() %100;
	if (lancer<=Pmut*100){
		if(genotype_=='S'){
			genotype_='L';
		}else{
			genotype_ = 'S';
		}
	}
}
