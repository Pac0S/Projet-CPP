#include "cellule.h"
#include <cmath>
#include <map>
#include <iostream>

using namespace std;
//getters



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

