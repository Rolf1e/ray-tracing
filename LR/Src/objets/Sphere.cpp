#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere() : Objet() { rayon = 1.0; }

Sphere::Sphere(float xc, float yc, float zc, float r, Materiau m)
    : Objet(m), centre(xc, yc, zc) {
  rayon = r;
}

Sphere::~Sphere() {}

bool Sphere::intersecte(const Rayon& r, Intersection& inter) {
  auto origin = r.origine;
  auto center = this->centre;
  auto oc_x = origin.X - center.X;
  auto oc_y = origin.Y - center.Y;
  auto oc_z = origin.Z - center.Z;
  auto rdir = r.direction;
  auto v_rdir = Vecteur(rdir.dx, rdir.dy, rdir.dz);

  auto a = v_rdir * v_rdir;
  auto oc = Vecteur(oc_x, oc_y, oc_z);
  auto b = 2 * (oc * r.direction);

  auto c = oc * oc - this->rayon * this->rayon;

  auto discriminant = b * b - 4 * a * c;

  if (discriminant < SP_EPSILON) {
    return false;
  }

  float t1, t2, t;

  t1 = (-b - sqrt(discriminant)) / (2 * a);
  t2 = (-b + sqrt(discriminant)) / (2 * a);

  t = min(t1, t2);
  if (t < 0 ) {
    return false;
  }

  auto x = r.origine.X + t * r.direction.dx;
  auto y = r.origine.Y + t * r.direction.dy;
  auto z = r.origine.Z + t * r.direction.dz;

  inter = Intersection(Point(x, y, z), this, t);
  return true;
}

bool Sphere::coupe(const Rayon& r) {

  auto origin = r.origine;
  auto center = this->centre;
  auto oc_x = origin.X - center.X;
  auto oc_y = origin.Y - center.Y;
  auto oc_z = origin.Z - center.Z;
  auto rdir = r.direction;
  auto v_rdir = Vecteur(rdir.dx, rdir.dy, rdir.dz);

  auto a = v_rdir * v_rdir;
  auto oc = Vecteur(oc_x, oc_y, oc_z);
  auto b = 2 * (oc * r.direction);

  auto c = oc * oc - this->rayon * this->rayon;

  auto discriminant = b * b - 4 * a * c;

  if (discriminant < SP_EPSILON) {
    return false;
  }

  float t1, t2, t;

  t1 = (-b - sqrt(discriminant)) / (2 * a);
  t2 = (-b + sqrt(discriminant)) / (2 * a);

  t = min(t1, t2);
  if (t < 0 ) {
    return false;
  }

  auto x = r.origine.X + t * r.direction.dx;
  auto y = r.origine.Y + t * r.direction.dy;
  auto z = r.origine.Z + t * r.direction.dz;
  return true; 
}

ostream& operator<<(ostream& sortie, Sphere& s) {
  // affichage de l'équation de la sphère
  sortie << "Sphere : de rayon " << s.rayon << ", de centre ";
  sortie << s.centre;
  // affichage du matériau de la sphère
  Objet* po = &s;
  sortie << *po << flush;
  return sortie;
}

Vecteur Sphere::getNormale(const Point& p) {
  // la normale à la sphère au point P est égale
  // au vecteur CP, avec C le centre de la sphère
  Vecteur n(p.X - centre.X, p.Y - centre.Y, p.Z - centre.Z);
  n.normaliser();
  return n;
}

void Sphere::affiche(ostream& out) {
  out << "Sphere : de rayon " << rayon << ", de centre ";
  out << centre;
  Objet::affiche(out);
}

