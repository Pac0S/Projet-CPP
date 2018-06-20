#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <fstream>

#include "cellule.h"
#include "grid.h"


using namespace std;

void test_grid_getters(Grid& g);
void test_bool_function(Cellule c,int try_nbr, float Pdeath, float Pmutation);
//void test_affichages(Grid& g1);
void test_division(Cellule c1, float p_mut);
void final_simulation(float A_init_min, float A_init_max, int a_init_step, int T_min, int T_max, int T_step);

int main(int argc, char* argv[]){
	cout << " --------------------------------------------------" << endl;
	srand(time(0));//initialise les valeurs aléatoire, a mettre au debut du code
	//Cellule c1('L');// test Cellule

	//Grid g1(30,50);
	
	//test_grid_getters(g1); //change le genotype de toute les cellules wtf? Erreur de segmentation quand compilé avec diffusion...
	//test_bool_function(c1,50,0.2,0.2);
	//test_affichages(g1);
	//test_division(c1,0.5);
	//cout<<g1.zoliaffissage()<<endl;
	//cout<<g1.zoliaffissagemet()<<endl;
	//g1.run();
	//1mn05 chrono à l'exécution pour 5000 pas de temps à 32*32
	//ça va etre sacrément drôle de faire un portrait de phase
	//A ce rhytme on peut faire 37(A_init) * 37(T_) simulations en 24h (entre deux redémarrages des ordis)
	
	
	final_simulation(50, 50 , 1, 1231, 1501, 15);
	 
	
	return 0;
}

void test_grid_getters(Grid& g){
	cout << "Taille de la grille : " << g.get_taille() << endl;
	cout << "Coefficient de diffusion D : " << g.get_coeff_diff() << endl;
	cout << "Probabilité de mort des cellules : " << g.get_p_death() << endl;
	cout << "Probabilité de mutation des cellules : " << g.get_p_mut() << endl;
	cout << "Taux métabolique Raa : " << g.get_Raa() << endl;
	cout << "Taux métabolique Rab : " << g.get_Rab() << endl;
	cout << "Taux métabolique Rbb : " << g.get_Rbb() << endl;
	cout << "Taux métabolique Rbc : " << g.get_Rbc() << endl;
}

void test_bool_function(Cellule& c,int try_nbr, float P){
	
	srand(time(0));//initialise les valeurs aléatoire, a mettre au debut du code
	int nbr_true =0;
	for (int i(0);i<=try_nbr;i++){
		if(c.roll_a_dice(P)){
			nbr_true++;
		}
	}
	cout << nbr_true << " vrai pour "<<try_nbr<< "essais (p="<<P<<")\n"<<endl;
}


/*
void test_affichages(Grid& g1){
	cout<<g1.zoliaffissage()<<endl;
	
	cout<<g1.zoliaffissagemet()<<endl;
	g1.step();
	cout<<g1.zoliaffissagemet()<<endl;
	g1.step();
	cout << g1.zoliaffissage()<< endl;
	g1.step();
	
	g1.lavage();
	cout<<g1.zoliaffissagemet()<<endl;
	cout << g1.zoliaffissage()<< endl;
	g1.step();
	cout << g1.zoliaffissage()<< endl;
	g1.step();
	cout << g1.zoliaffissage()<< endl;
	g1.step();
	cout << g1.zoliaffissage()<< endl;
	g1.step();
	cout << g1.zoliaffissage()<< endl;
	g1.step();
	cout << g1.zoliaffissage()<< endl;
	
	cout<<g1.zoliaffissage()<<endl;
	
}
*/

/*
void test_division(Cellule c1, float p_mut){
	cout<<"\n"<<"Cellule mere avant division : " << endl;
	cout << c1.getGen()<<endl;
	cout<<c1.getReseauMet()["Glucose"]<<endl;
	cout<<"\n"<<c1.getReseauMet()["Acetate"]<<endl;
	cout<<"\n"<<c1.getReseauMet()["Ethanol"]<<endl<<endl;
	
	Cellule c2(c1,p_mut);
	
	cout<<"\n"<<"Cellule mere apres division : " << endl;
	cout << c1.getGen()<<endl;
	cout<<c1.getReseauMet()["Glucose"]<<endl;
	cout<<"\n"<<c1.getReseauMet()["Acetate"]<<endl;
	cout<<"\n"<<c1.getReseauMet()["Ethanol"]<<endl<<endl;
	
	cout<<"\n"<<"Cellule fille : " << endl;
	cout << c2.getGen()<<endl;
	cout<<c2.getReseauMet()["Glucose"]<<endl;
	cout<<"\n"<<c2.getReseauMet()["Acetate"]<<endl;
	cout<<"\n"<<c2.getReseauMet()["Ethanol"]<<endl<<endl;
}*/

void final_simulation(float A_init_min, float A_init_max, int A_init_step, int T_min, int T_max, int T_step){


	/*#######################################*/
	/*###   Initialisation du temps   #######*/
	/*#######################################*/
	
	float time;
    clock_t t1, t2;
    t1 = clock(); //Départ de l'horloge
    
    
    /*#######################################*/
	/*###     Ouverture d'un fichier  #######*/
	/*#######################################*/
	
	ofstream results("n_mut_50_50|1231_1501.txt", ios::out | ios::trunc);	
	if(results){	
	
		float A_init;
		int T;
		results<<"A_init\tT\tS\tL\tmax_L_lvg\tEtat"<<endl;
		for(A_init = A_init_min; A_init<=A_init_max; A_init+=A_init_step){
			for(T= T_min; T<=T_max; T+=T_step){
				Grid g(T, A_init);
				g.run();
			}
		}
		results.close(); //Fermeture du fichier
	}else{
	  cerr << "Error opening the file" << endl;
	}
	
	t2 = clock();//Arrêt de l'horloge
    time = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("Simulation complète :  %f secondes\n", time);
	
}
			
	
