#ifndef CEL_H
#define CEL_H

#include <map>

using namespace std;

class cellule {
public :
/*#############################################*/
/*               CONSTRUCTORS                  */
/*#############################################*/
	cellule();
	cellule(char gen);
	
/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/
	float getFitness();
	char getGen();
	map<string,float> getReseauMet();
	
/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/
  
/*#############################################*/
/*                  DISPLAY                    */
/*#############################################*/
  void printc;
  
/*#############################################*/
/*                   METHODS                   */
/*#############################################*/
	bool is_mutating(float Pmut);
	bool is_dead(float Pdeath);

protected :
	
private :
	//parametres
	char genotype_; //Ga ou Gb
	map<string,float> reseauMet_; //quantité de A,B et C dans la cellule
	
};

#endif
