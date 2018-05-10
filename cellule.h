#ifndef CEL_H
#define CEL_H

#include <map>

using namespace std;

class Cellule {
	public :
/*#############################################*/
/*               CONSTRUCTORS                  */
/*#############################################*/
		Cellule();
		Cellule(char gen);
	
/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/
		float getFitness();
		char getGen();
		map<string,float> getReseauMet();
		float get_Glucose();
		float get_Acetate();
		float get_Ethanol();
		void set_Genotype(char g);
	
/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/
		void set_Glucose(float a);
		void set_Acetate(float b);
		void set_Ethanol(float c);
/*#############################################*/
/*                  DISPLAY                    */
/*#############################################*/
		void printc();
  
/*#############################################*/
/*                   METHODS                   */
/*#############################################*/
		bool is_mutating(float Pmut);
		bool is_dead(float Pdeath);

	protected :
/*#############################################*/
/*                   ATTRIBUTES                */
/*#############################################*/

		char genotype_; //Ga ou Gb  ou rien 
		map<string,float> reseauMet_; //quantité de A,B et C dans la cellule
		static float A_init; //Concentration initiale en A dans chaque Cellule (plutot que de modifier le constructeur on pourra modifier l'initialisation de A).
	
	
};

#endif
