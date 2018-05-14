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
		Cellule(Cellule*& mere, float& p_mut); // Constructeur spécifique à la division cellulaire
	
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
		void mutates(float Pmut);
		bool roll_a_dice(float Pdeath);

	protected :
/*#############################################*/
/*                   ATTRIBUTES                */
/*#############################################*/

		char genotype_; //Ga ou Gb  ou rien 
		map<string,float> reseauMet_; //quantité de A,B et C dans la cellule
		static float A_init; //Concentration initiale en A dans chaque Cellule (plutot que de modifier le constructeur on pourra modifier l'initialisation de A).
	
	
};

#endif
