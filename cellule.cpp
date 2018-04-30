#include "cellule.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

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



//affichage

//méthode:
