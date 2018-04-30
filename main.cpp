#include <iostream>
#include <map>
#include "cellule.h"
#include "grid.h"

using namespace std;

int main(int argc, char* argv[]){
	cellule c('m');// test cellule
	//test cellule::is_dead et cellule::is_mutating
	int morts =0;
	int mutations=0;
	for (int i(0);i<=4;i++){
		if(c.is_dead(0.5)){morts++;}
		if(c.is_mutating(0.5)){mutations++;}
	}
	cout << morts << "morts et "<<mutations<< "mutations.\n"<<endl; //resultat bizarre je tombe sur 7 7 beaucoup trop souvent à voir..
	return 0;
}
