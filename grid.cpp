#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <string>

#include "grid.h"
#include "cellule.h"

using namespace std;



/*#############################################*/
/*             CONSTRUCTORS                    */
/*#############################################*/

/************************ Constructeur par défaut ************************/
/*                                                                       */
/* Cree une grille torique de taille taille_ * taille_ qui possede des   */
/* parametres tels que :                                                 */
/*    coeff_diff : taux de diffusion des cellules dans leur environnement*/
/*    p_death : probabilité de décès d'un individu                       */
/*    p_mut : probabilité de mutation de deux individus fils apres une   */
/*            division                                                   */
/*    W_min : seuil minimum de la fitness pour un individu               */
/*    temps : temps initial                                              */
/*    taux_meta_ : map contenant les taux permettant de convertir ou     */
/*                 d'importer les ressources de l'environnement          */
/*                                                                       */
/*  La grille contient 50% d'individus de type S et 50% d'individus de   */
/* type L. Chaque case de la grille contient une cellule.                */
/* Il n'y a pas de cases vides au temps initial.                         */ 
/*                                                                       */
/*************************************************************************/

Grid::Grid(int T, float A_init){
	T_ = T;
	A_init_ = A_init;
	taille_= 32; //W=H
	coeff_diff_=0.1; //D
	p_death_=0.02;
	p_mut_=0.000;
	temps_= 0;
	taux_meta_["Raa"]=0.1;
	taux_meta_["Rab"]=0.1;
	taux_meta_["Rbb"]=0.1;
	taux_meta_["Rbc"]=0.1;
	temps_simulation_=5000;
	
	
	vector<Case> y_axis(taille_);
	vector< vector<Case> > grid(taille_, y_axis);
	
	// On stocke les genotypes de chaque cellule à l'initialisation dans un vecteur
	vector<char> genotypes(taille_*taille_); 
	
	/*
	* Precondition : On suppose une grille possédant un nombre de cases pair
	* On obtient ainsi le meme nombre de cellules L et S
	*/
	for(vector<char>::iterator it=genotypes.begin(); it!= genotypes.begin() + (taille_*taille_/2);it++){ 
		*it = 'S';	
	}
	for(vector<char>::iterator it=genotypes.begin() + (taille_*taille_/2); it!= genotypes.end();it++){ 
		*it = 'L';	
	}
	// On mélange aleatoirement les 50% S et les 50% L dans le vecteur
	random_shuffle(genotypes.begin(),genotypes.end()); 
	
	/*for(vector<char>::iterator it=genotypes.begin(); it!= genotypes.end();it++){ 
		cout << *it << endl;
	}*/
	
	vector<char>::iterator it = genotypes.begin(); // Itérateur qui parcoure le vecteur des genotypes
	//on parcourt toutes les cases de la grille
	for (vector<vector<Case>>::iterator i =grid.begin();i!=grid.end();i++){
		for (vector<Case>::iterator j =i->begin();j!=i->end();j++){ 
			Cellule* c = new Cellule(*it); // On copie le génotype dans la nouvelle cellule
			j->cel_=c; // On ajoute cette cellule dans la case
			map<char,float> metab;
			metab['A']=A_init_; // -> Quantite de A initial mis dans chaque case
			metab['B']=0;
			metab['C']=0;
			j->metab_=metab;		
			it++; // On passe au génotype suivant
		} 	   
	}
	grille_=grid;
	//cout << "DONE !" << endl;
}









/*#############################################*/
/*              DESTRUCTOR                     */
/*#############################################*/


Grid::~Grid(){
	for (vector<vector<Case>>::iterator i =grille_.begin();i!=grille_.end();++i){
		vector<Case> y_axis = *i;
		for (vector<Case>::iterator j =y_axis.begin();j!=y_axis.end();++j){
			Case here = *j;
			delete here.cel_;
		}
	}
}










/*#############################################*/
/*                  METHODS                    */
/*#############################################*/

/******************************** Step **********************************/
/* Représente tous les evenements se deroulant dans un pas de temps.    */
/* Celui-ci comprend :                                                  */
/*    - la diffusion des cellules dans leur environnement               */
/*    - la mort des cellules (selon p_death)                            */
/*    - le fonctionnement metabolique des cellules (precision : celui-ci*/
/*       se déroule en un dixième de temps. Les individus metabolisent  */
/*       donc 10 fois en un pas de temps)                               */
/************************************************************************/
void Grid::step(){

	temps_++;
	
	//diffusion metabolite//
	diffusion();
	
	//mort des cellules//
	dying();
	
	
	//division des cellules//
	division(); //Aucune division au premier pas ????
		
		
	//fonctionnement metabolique: !!dt=0.1!!
	for(int i = 0; i < 10 ; i++){
		metaboliser();
	}
	
	

	
	
	//-----------------------------------------//
	//   Ecriture des donnees en fichier txt   //
	//-----------------------------------------//
	
	//Ouverture du fichier initialisé dans run
	string A = to_string(A_init_);
	string A_trc = A.substr(0,4); //Pour récupérer seulement 50.0 plutot que 50.000000
	
	string simulation = A_trc + "|" + to_string(T_)+ ".txt";
	//ouverture d'un fichier :
	ofstream file(simulation.c_str(), ios::out | ios::app);	
	//Si l'ouverture a fonctionné
	if(file){
		file<<temps_<<"\t"<<to_string(grille_[0][0].cel_->get_nb_cellules_S())<<"\t"<<to_string(grille_[0][0].cel_->get_nb_cellules_L())<<"\t"<<to_string(grille_[0][0].cel_->get_nb_dead())<<endl;
		
		file.close(); //Fermeture du fichier
	}
	else{
	  cerr << "Error opening the file" << endl;
	}
	
}



void Grid::run(){
	
	
	/*#######################################*/
	/*###   Initialisation du temps   #######*/
	/*#######################################*/
	
	float time;
    clock_t t1, t2;
    t1 = clock(); //Départ de l'horloge
 
  
	
	
	/*#######################################*/
	/*###   Initialisation du fichier   #####*/
	/*#######################################*/
	

	string A = to_string(A_init_);
	string A_trc = A.substr(0,4);
	
	
	
	string simulation = A_trc + "|" + to_string(T_)+ ".txt";
	ofstream file(simulation.c_str(), ios::out | ios::trunc);	
	//Si l'ouverture a fonctionné
	if(file){
		file << "temps\tS\tL\tdead_in_grid"<<endl;
		file<<temps_<<"\t"<<to_string(grille_[0][0].cel_->get_nb_cellules_S())<<"\t"<<to_string(grille_[0][0].cel_->get_nb_cellules_L())<<"\t"<<to_string(grille_[0][0].cel_->get_nb_dead())<<endl;
		
		
		file.close(); //Fermeture du fichier
	}
	else{
		cerr << "Error opening the file" << endl;
	}
	
	
	
	/*#######################################*/
	/*########    Boucle principale     #####*/
	/*#######################################*/
	
	while(temps_!=temps_simulation_ && grille_[0][0].cel_->get_nb_total()!=0 && grille_[0][0].cel_->get_nb_cellules_L()!=taille_*taille_){
		
		if(temps_ % T_ == 0){
			lavage();
		}
		step();
	}
	
	int final_state;
	
	if(grille_[0][0].cel_->get_nb_cellules_S() == 0 && grille_[0][0].cel_->get_nb_cellules_L()!=0){
		final_state = 1; //Exclusion
	}else if(grille_[0][0].cel_->get_nb_cellules_S() == 0 && grille_[0][0].cel_->get_nb_cellules_L()==0){
		final_state = 0; //Extinction
	}else if(grille_[0][0].cel_->get_nb_cellules_S() != 0 && grille_[0][0].cel_->get_nb_cellules_L()!=0){
		final_state = 2; //Cohabitation
	}else{
		final_state = -1; //Pas normal
	}
	
	
	
	
	
	
	
	/*#######################################*/
	/*## Affichage du temps d'exécution   ###*/
	/*#######################################*/
	
	
	t2 = clock();//Arrêt de l'horloge
    time = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f secondes\n", time);
    
    
    /*#######################################*/
	/*###   Affichage des résultats     #####*/
	/*#######################################*/
	
	
	string written_results;
	written_results = "A_init \t T \t nb_cell_S \t nb_cell_L \t nb_cell_dead \t Etat final\n" + to_string(A_init_) + "\t" + to_string(T_) + "\t" + to_string(grille_[0][0].cel_->get_nb_cellules_S()) + "\t" + to_string(grille_[0][0].cel_->get_nb_cellules_L())+"\t"+ to_string(grille_[0][0].cel_->get_nb_dead())+"\t"+to_string(final_state);
    
	cout<<written_results<<endl<<endl;
	
	
	
	/*#######################################*/
	/*###   Sauvegarde des résultats    #####*/
	/*#######################################*/
	
	
	ofstream results("0_10|1_151.txt", ios::out | ios::app);	
	//Si l'ouverture a fonctionné
	if(results){	
	
		results<<A_trc<<"\t"<<to_string(T_)<<"\t"<<to_string(grille_[0][0].cel_->get_nb_cellules_S())<<"\t"<<to_string(grille_[0][0].cel_->get_nb_cellules_L())<<"\t"<<to_string(final_state)<<endl;
	
		
		results.close(); //Fermeture du fichier
	}
	else{
	  cerr << "Error opening the file" << endl;
	}
	
	
	/*#######################################*/
	/*###   Réinitialisation de la grille  ##*/
	/*#######################################*/
	
	
	grille_[0][0].cel_->empty_cells();
}










/**************** Fonctions utilisees par step() ************************/

/************* Diffusion des cellules **************/

void Grid::diffusion(){

  /* tableau de taille_ * taille_ contenant les concentrations des 
     3 métabolites A, B et C pour chaque case.*/
	vector<vector<Case>> metab_t_plus_un(taille_, vector<Case>(taille_)); 
	
	//Parcours des cases de notre grille (t)
	for (int i1=0;i1<taille_;i1++){
		for (int j1=0;j1<taille_;j1++){
		
			//Copie des concentrations de t en t+1
			(metab_t_plus_un[i1][j1]).metab_['A'] = (grille_[i1][j1]).metab_['A'];
			(metab_t_plus_un[i1][j1]).metab_['B'] = (grille_[i1][j1]).metab_['B'];
			(metab_t_plus_un[i1][j1]).metab_['C'] = (grille_[i1][j1]).metab_['C'];
			
			//Parcours des 9 cases autour de notre case (t)
			int x; //Abscisse du voisin qui se diffuse vers notre case
			int y; //Ordonnée du voisin qui se diffuse vers notre case
			for(int i2=-1;i2<=1;++i2){
				for(int j2=-1;j2<=1;++j2){
					if(i1+i2<0){ //Cas où on est sur la limite à gauche de la grille
						x = taille_ - 1;
					}else if(i1+i2>taille_-1){ //Cas où on est sur la limite à droite de la grille
						x=0;
					}else{
						x=i1+i2;
					}
					if(j1+j2<0){ //Cas où on est sur la limite en bas de la grille
						y = taille_ - 1;
					}else if(j1+j2>taille_-1){ //Cas où on est sur la limite en haut de la grille
						y = 0;
					}else{
						y = j1+j2;
					}
					
					//Ajout des métabolites des cases voisines diffusés en t+1 et stockage dans le tableau en t+1
					(metab_t_plus_un[i1][j1]).metab_['A'] += grille_[x][y].metab_['A']*coeff_diff_;
					(metab_t_plus_un[i1][j1]).metab_['B'] += grille_[x][y].metab_['B']*coeff_diff_;
					(metab_t_plus_un[i1][j1]).metab_['C'] += grille_[x][y].metab_['C']*coeff_diff_;
				}
			}
			//Soustraction de la partie diffusée de la case
			metab_t_plus_un[i1][j1].metab_['A'] -= 9 * coeff_diff_ * grille_[i1][j1].metab_['A'];
			metab_t_plus_un[i1][j1].metab_['B'] -= 9 * coeff_diff_ * grille_[i1][j1].metab_['B'];
			metab_t_plus_un[i1][j1].metab_['C'] -= 9 * coeff_diff_ * grille_[i1][j1].metab_['C'];
		}
		
	}
	for (int i1=0;i1<taille_;i1++){
		for (int j1=0;j1<taille_;j1++){
		
			//Copie des concentrations de t+1 en t
			
			grille_[i1][j1].metab_['A']=metab_t_plus_un[i1][j1].metab_['A'];
			grille_[i1][j1].metab_['B']=metab_t_plus_un[i1][j1].metab_['B'];
			grille_[i1][j1].metab_['C']=metab_t_plus_un[i1][j1].metab_['C'];
		}
	}
}












/*************Position des cellules mortes************/

void Grid::dying(){
	for (unsigned int i(0);i<taille_;i++){
		for (unsigned int j(0);j<taille_;j++){
			if(grille_[i][j].cel_->is_alive()){
				if(grille_[i][j].cel_->roll_a_dice(p_death_)){//si la cellule meurt
					grille_[i][j].metab_['A']+=grille_[i][j].cel_->getReseauMet()["Glucose"];
					grille_[i][j].metab_['B']+=grille_[i][j].cel_->getReseauMet()["Acetate"];
					grille_[i][j].metab_['C']+=grille_[i][j].cel_->getReseauMet()["Ethanol"];
					grille_[i][j].cel_->empty_Met();
					grille_[i][j].cel_->kill();
					vector<int> coord;
					coord.push_back(i);
					coord.push_back(j);
					coord_dead_cells_.push_back(coord);
				}
			}
		}
	}
}











/***********Concurrence pour la division dans les cases vides************/

void Grid::division(){


	vector<vector<int>> new_coords;
	
	while (! coord_dead_cells_.empty()){
		//cout<< coord_dead_cells_.size()<<endl;
		int rand_cell_nbr;
		
		if (coord_dead_cells_.size()!=1){
			rand_cell_nbr = rand() % (coord_dead_cells_.size()-1);
		}else{
			rand_cell_nbr = 0;
		}
		int dead_cell_x=coord_dead_cells_[rand_cell_nbr][0];
		int dead_cell_y=coord_dead_cells_[rand_cell_nbr][1];
		int realx=dead_cell_x-1;
		int realy=dead_cell_y-1;
		if (realx<0){realx=taille_-1;}
		if (realx==taille_){realx=0;}
		if (realy<0){realy=taille_-1;}
		if (realy==taille_){realy=0;}
		Cellule* dividing_cell = grille_[realx][realy].cel_;
		for (int x =dead_cell_x-1;x<=dead_cell_x+1;x++){
			for (int y =dead_cell_y-1;y<=dead_cell_y+1;y++){
				if(x!=dead_cell_x || y!=dead_cell_y){
					
					realx=x;
					realy=y;
					if (realx<0){realx=taille_-1;}
					if (realx==taille_){realx=0;}
					if (realy<0){realy=taille_-1;}
					if (realy==taille_){realy=0;}
					//si la valeur de la dividing_cell est plus petite que celle que pointe les coord, ou si elle est égale et que un lacer de dé de proba 1/2 donne true
					if( dividing_cell->getFitness() < grille_[realx][realy].cel_->getFitness() || (rand()%2==0 && dividing_cell->getFitness() == grille_[realx][realy].cel_->getFitness()) ){
						
						dividing_cell = grille_[realx][realy].cel_;
					}
				}
			}
		}
		if(dividing_cell->getFitness()!=0){
			delete grille_[dead_cell_x][dead_cell_y].cel_;
			grille_[0][0].cel_->decrease_dead();
			grille_[dead_cell_x][dead_cell_y].cel_= new Cellule(dividing_cell,p_mut_);
		}
		
		if(!grille_[dead_cell_x][dead_cell_y].cel_->is_alive()){//Si la cellules n'est pas vivante, càd si la morte n'a pas été remplacée
			new_coords.push_back(*(coord_dead_cells_.begin()+rand_cell_nbr));
		}
		
		coord_dead_cells_.erase(coord_dead_cells_.begin()+rand_cell_nbr); //On efface le vecteur de cellules mortes d'origine
		
		
		
		
		
		
			
		/*Oui mais non... Si on supprime une cellule qui n'a pas été remplacée, elle ne sera plus considérée aux steps suivants. 
		Elle ne sera donc jamais remplacée. Il faut la stocker et la récupérer au step suivant*/
		

	}
	
	coord_dead_cells_ = new_coords;
}












/***********Metabolisme d'une cellule !!!!! dt = 0.1 !!!!!************/

void Grid::metaboliser(){
	for (vector<vector<Case>>::iterator i =grille_.begin();i!=grille_.end();i++){
		for (vector<Case>::iterator j =i->begin();j!=i->end();j++){
			if(j->cel_->is_alive()){
			
				//Stockage des données au debut du pas de temps
				float A_out = j->metab_['A']; //Quantite de Glucose dans la case j
				float A_in = j->cel_->get_Glucose(); //Quantite de Glucose dans la cellule de la case j
			
				float B_out = j->metab_['B']; //Quantite d'Acetate dans la case j
				float B_in = j->cel_->get_Acetate(); //Quantite d'Acetate dans la cellule de la case j
			
				//float C_out = j->metab_['C']; //Quantite d'Ethanol dans la case j
				float C_in = j->cel_->get_Ethanol(); //Quantite d'Ethanol dans la cellule de la case j
			
				if (j->cel_->getGen()=='L'){//Cas ou la cellule est de type Ga (Large)
			
				//Calculs du fonctionnement metabolique suivant les formules fournies
					j->metab_['A'] = A_out * (1 - taux_meta_["Raa"]); //mise à jour de A dans la case
				
					float new_A = A_in + A_out * taux_meta_["Raa"] - A_in * taux_meta_["Rab"];
					j->cel_->set_Glucose(new_A);//Mise à jour de A dans la cellule
				
					float new_B = B_in + A_in * taux_meta_["Rab"];
					j->cel_->set_Acetate(new_B);//Mise à jour de B dans la cellule
				
				}else{ //Cas ou la cellule est de type Gb (Small)
			
				//Calculs du fonctionnement metabolique suivant les formules fournies
					j->metab_['B'] = B_out * (1 - taux_meta_["Rbb"]);//mise à jour de B dans la case
				
					float dB = B_in + B_out * taux_meta_["Rbb"] - B_in * taux_meta_["Rbc"];
					(j->cel_)->set_Acetate(dB);//Mise à jour de A dans la cellule
				  
				  
					float new_C = C_in + B_in * taux_meta_["Rbc"];
					(j->cel_)->set_Ethanol(new_C);//Mise à jour de C dans la cellule
				}
			}
		}
	}
}














/* Vidage de la grille de ses métabolites */
void Grid::lavage(){
	for(vector<vector<Case>>::iterator it1=grille_.begin();it1 != grille_.end(); ++it1){
		for (vector<Case>::iterator it2 =it1->begin();it2!=it1->end();it2++){
			it2->metab_['A']=A_init_;
			it2->metab_['B']=0;
			it2->metab_['C']=0;
		}
	}
}
	













/*#############################################*/
/*                 GETTERS                     */
/*#############################################*/

int Grid::get_taille(){
	return taille_;
}
	
	
float Grid::get_coeff_diff(){
	return coeff_diff_;
}
	
	
float Grid::get_p_death(){
	return p_death_;
}
	
	
float Grid::get_p_mut(){
	return p_mut_;
}
	
	
float Grid::get_Raa(){
	return taux_meta_["Raa"];
}
	
	
float Grid::get_Rab(){
	return taux_meta_["Rab"];
}
	
float Grid::get_Rbb(){
	return taux_meta_["Rbb"];
}
	
float Grid::get_Rbc(){
	return taux_meta_["Rbc"];
}
/*#############################################*/
/*                  SETTERS                    */
/*#############################################*/






/*#############################################*/
/*                   DISPLAY                   */
/*#############################################*/

string Grid::zoliaffissage(){
	string zoli = "";
	for (vector<vector<Case>>::iterator ligne =grille_.begin();ligne!=grille_.end();++ligne){
		for (int i(0);i<taille_*2+1;i++){
			zoli+='-';
		}
		zoli+='\n';
		zoli+='|';
		for (vector<Case>::iterator colonne = ligne->begin();colonne!=ligne->end();colonne++){
			if(colonne->cel_->is_alive()){
				if (colonne->cel_->getGen()=='L'){
					zoli+="L|";
				}else if(colonne->cel_->getGen()=='S'){
					zoli+="S|";
				}
			}else{
				zoli+="X|";
			}
		}
		zoli+='\n';
	}
	for (int j(0);j<taille_*2+1;j++){
		zoli+='-';
	}
	return zoli;
}











string Grid::zoliaffissagemet(){
	string zolimet = "";
	zolimet+="A";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\tB";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\tC";
	for (int i (1);i<taille_*2+1;i++){
		zolimet+="-";
	}
	zolimet+="\n";
	for (int i(0);i<taille_;i++){
		for (int l(0);l<3;l++){
			zolimet+="|";
			for (int j(0);j<taille_;j++){
				int a = int(grille_[i][j].metab_['A'+l]);
				zolimet+=to_string(a);
				zolimet+="|";
			}
			zolimet+="\t";
		}
		zolimet+="\n";
		for (int k(0);k<3;k++){
			for (int l(0);l<taille_*2+1;l++){
				zolimet+="-";
			}
			zolimet+="\t";
		}

		zolimet+="\n";
	}
	return zolimet;
}


