#include <iostream>
#include <map>
#include "cellule.h"
#include "grid.h"
#include <ctime>
#include <cstdlib>
using namespace std;

void test_grid_getters(Grid g);
void test_bool_function(cellule c,int try_nbr, float Pdeath, float Pmutation);

int main(int argc, char* argv[]){
	cellule c1('L');// test cellule
	Grid g1;
	
	//test_grid_getters(g1);
	//test_bool_function(c1,50,0.2,0.2);
	
	
	return 0;
}

void test_grid_getters(Grid g){
	cout << "Taille de la grille : " << g.get_taille() << endl;
	cout << "Coefficient de diffusion D : " << g.get_coeff_diff() << endl;
	cout << "Probabilité de mort des cellules : " << g.get_p_death() << endl;
	cout << "Probabilité de mutation des cellules : " << g.get_p_mut() << endl;
	cout << "Fitness minimale nécessaire à la division : " << g.get_W_min() << endl;
	cout << "Taux métabolique Raa : " << g.get_Raa() << endl;
	cout << "Taux métabolique Rab : " << g.get_Rab() << endl;
	cout << "Taux métabolique Rbb : " << g.get_Rbb() << endl;
	cout << "Taux métabolique Rbc : " << g.get_Rbc() << endl;
}

void test_bool_function(cellule c,int try_nbr, float Pdeath, float Pmutation){
	
	srand(time(0));//initialise les valeurs aléatoire, a mettre au debut du code
	int morts =0;
	int mutations=0;
	for (int i(0);i<=try_nbr;i++){
		if(c.is_dead(Pdeath)){morts++;}
		if(c.is_mutating(Pmutation)){mutations++;}
	}
	cout << morts << "morts et "<<mutations<< "mutations.\n"<<endl; //resultat bizarre je tombe sur 7 7 beaucoup trop souvent à voir..
	
	
}
	
