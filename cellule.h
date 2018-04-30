#ifndef CEL_H
#define CEL_H



class cellule {
public :
	//getters
	float getFitness();
	char getGen();
	map<string,float> getReseauMet();
	//setters

	//constructor
	cellule();
	cellule(char gen, map<string, float> metabolisme);
	//affichage
	void printc;
	//methode
	bool is_mutating(float Pmut);
	bool is_dead(float Pdeath);
	
protected :
	
private :
	//parametres
	char genotype_; //Ga ou Gb
	map<string,float> reseauMet_; //quantité de A,B et C dans la cellule
	
	
};

#endif
