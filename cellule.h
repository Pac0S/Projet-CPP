#ifndef CEL_H
#define CEL_H

#include <map>

using namespace std;

class Cellule {
	public :
/*#############################################*/
/*               CONSTRUCTORS                  */
/*#############################################*/
		//Cellule();
		Cellule(char gen);
		Cellule(Cellule* mere, float& p_mut); // Constructeur spécifique à la division cellulaire
		
/*#############################################*/
/*               DESTRUCTOR                    */
/*#############################################*/
    	//~Cellule();
    
/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/
		float getFitness();
		char getGen();
		map<string,float> getReseauMet();
		float get_Glucose();
		float get_Acetate();
		float get_Ethanol();
		bool is_alive();
		
		
		unsigned int get_nb_cellules_L();
		unsigned int get_nb_cellules_S();
		unsigned int get_nb_total();
		unsigned int get_nb_cellules_mortes();
	
/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/
		void set_Genotype(char g);
		void set_Glucose(float a);
		void set_Acetate(float b);
		void set_Ethanol(float c);
		void empty_Met();
		void empty_cells();
/*#############################################*/
/*                  DISPLAY                    */
/*#############################################*/
		void printc();
  
/*#############################################*/
/*                   METHODS                   */
/*#############################################*/
		void mutates(float Pmut);
		bool roll_a_dice(float Pdeath);
		void kill();

	protected :
/*#############################################*/
/*                   ATTRIBUTES                */
/*#############################################*/

		char genotype_; //Ga ou Gb  ou rien 
		map<string,float> reseauMet_; //quantité de A,B et C dans la cellule
		bool alive_;
		static unsigned int nb_cellules_L_;
		static unsigned int nb_cellules_S_;
		unsigned int nb_cellules_dead;
		
	
	
};

#endif
