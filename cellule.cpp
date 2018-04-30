#include "cellule.h"
#include <cmath>
#include <map>
#include <iostream>

using namespace std;
//getters
/*float cellule::getFitness() {
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

*/
//constructors
cellule::cellule(){
  genotype_ = 'S';
  reseauMet_["Glucose"]=0.;
  reseauMet_["Acetate"]=0.;
  reseauMet_["Ethanol"]=0.;
  }

cellule::cellule(char gen){
  if(gen == 'L' || gen == 'S'){
    genotype_ = gen;
    reseauMet_["Glucose"]=0.;
    reseauMet_["Acetate"]=0.;
    reseauMet_["Ethanol"]=0.;
  }else{
    cout << gen << " is not a type. Please try again."<< endl;
  }
}


//affichage

//setters



//méthode:

