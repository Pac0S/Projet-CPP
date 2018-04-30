#include "cellule.h"
#include <cmath>
#include <map>
#include <iostream>
#include <cstdlib>
using namespace std;
//getters
float cellule::getFitness() {
	float fitness;
	if (genotype_=='L'){
		fitness= reseauMet_[Acetate];
	}else{
		fitness= reseauMet_[Ethanol];
	}
	return fitness;
}

char cellule::getGen(){
	return genotype_;
}

map<string,float> cellule::getReseauMet(){
	return reseauMet_;
}


//constructors
cellule::cellule(){
  genotype_ = 'S'
  reseauMet_["Glucose"]=0;
  reseauMet_["Acetate"]=0;
  reseauMet_["Ethanol"]=0;
  }

cellule::cellule(char gen, map<string, float> metabolisme){
  while(gen == 'L' || gen == 'S'){
    genotype_ = '\0'
  }else{
    cout << gen << " is not a type. Please try again."<< endl;
  }
  reseauMet_["Glucose"]=0;
  reseauMet_["Acetate"]=0;
  reseauMet_["Ethanol"]=0;
}


//affichage

//setters



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
