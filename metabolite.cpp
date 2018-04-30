#include "metabolite.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

//getters
float Comp::getre() {
	return re_;
}
float Comp::getim(){
	return im_;
}
float Comp::getmod(){
	return mod_;
}
float Comp::getarg(){
	return arg_;
}
//constructors
Comp::Comp(float re_, float im_){ //à partir des parties réelles et imaginaires
	this->re_=re_;
	this->im_=im_;
	this->mod_=sqrt(re_*re_+im_*im_);
	this->arg_=2*atan(im_/(re_+getmod()));
}
Comp::Comp(){  //par défaut, on fixe le complexe à 1+i
	this->re_=1;
	this->im_=1;
	this->mod_=sqrt(re_*re_+im_*im_);
	this->arg_=2*atan(im_/(re_+getmod()));
}
Comp::Comp(float mod_, float arg_,int methode){ //à partir de l'argument et du module
	//la valeur de methode n'importe pas, elle permet de différencier ce constructeur de l'autre
	this->mod_=mod_;
	this->arg_=arg_;
	this->re_=cos(arg_)*mod_;
	this->im_=sin(arg_)*mod_;
}
Comp::Comp(const Comp& c1){ //par copie
	this->re_=c1.re_;
	this->im_=c1.im_;
	this->mod_=c1.mod_;
	this->arg_=c1.arg_;	
	
}


//affichage
void Comp::print(){
	printf("z=%f + %f*i \n mod:%f arg:%f\n",getre(),getim(),getmod(),getarg());
}
//setters
void Comp::setre(float re){
	re_=re;
	mod_=sqrt(re_*re_+im_*im_);
	arg_=2*atan(im_/(re_+getmod()));
}
void Comp::setim(float im){
	im_=im;
	mod_=sqrt(re_*re_+im_*im_);
	arg_=2*atan(im_/(re_+getmod()));

}

//méthode:
Comp Comp::conj(){//retourne le complexe conjugué
	Comp t(re_,-1*im_);
	return t;
}
			//opérateur:
Comp Comp::add(Comp c){//+
	Comp t (re_+c.re_,im_+c.im_);
	return t;
}
Comp Comp::sub(Comp c){//-
	Comp t (re_-c.re_,im_-c.im_);
	return t;
}
Comp Comp::mult(Comp c){//*
	Comp t (mod_*c.mod_,fmod(arg_+c.arg_,2*M_PI),2);
	return t;
}
Comp Comp::div(Comp c){// divisé
	Comp t (mod_/c.mod_,fmod(arg_-c.arg_,2*M_PI),2);
	return t;
}
