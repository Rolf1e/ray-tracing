#include "Vecteur.hpp"
#include "Point.hpp"

#include <cmath>

Vecteur:: Vecteur(){
  dx = dy = dz = 0.0;
}
 
Vecteur::Vecteur(float Xp, float Yp,  float Zp){
  dx = Xp; dy = Yp; dz = Zp;
  }

Vecteur::Vecteur(const Point& PA, const Point& PB){
  dx = PB.X - PA.X;
  dy = PB.Y - PA.Y;
  dz = PB.Z - PA.Z;
}

/*Vecteur::Vecteur(const Vecteur& v){
  dx = v.dx; dy = v.dy; dz = v.dz;

  }*/

Vecteur:: ~Vecteur(){}

void Vecteur::normaliser(){
  float norme = (float)sqrt(dx*dx+dy*dy+dz*dz);
  dx /= norme; dy /= norme; dz /= norme;
}

float Vecteur::operator*(const Vecteur& v){
  return (dx*v.dx + dy*v.dy + dz*v.dz);
}

Vecteur Vecteur::operator*(float k){
  return Vecteur(k*dx, k*dy, k*dz);
}


Vecteur Vecteur::operator+(const Vecteur& v){
  return Vecteur(dx+v.dx, dy+v.dy, dz+v.dz);
}

Vecteur Vecteur::operator-(const Vecteur& v){
  return Vecteur(dx-v.dx, dy-v.dy, dz-v.dz);
}

ostream& operator<<(ostream & sortie, const Vecteur & v){
  sortie << "(" << v.dx << "," << v.dy << "," << v.dz << ")" << flush;
  return sortie;
}


