#include <iostream>
#include <map>
#include "cellule.h"
#include "grid.h"

using namespace std;

int main(int argc, char* argv[]){
	cellule c('m');// test cellule
	//test cellule::is_dead et cellule::is_mutating
	
	
	return 0;
}

void test_bool_function(cellule c,int try_nbr, int Pdeath, int Pmutation){
	int morts =0;
	int mutations=0;
	for (int i(0);i<=try_nbr;i++){
		if(c.is_dead(Pdeath)){morts++;}
		if(c.is_mutating(Pmutation)){mutations++;}
	}
	cout << morts << "morts et "<<mutations<< "mutations.\n"<<endl; //resultat bizarre je tombe sur 7 7 beaucoup trop souvent à voir..
	
	
}
	
