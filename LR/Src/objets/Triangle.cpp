#include "Triangle.hpp"
#include "../Plan.hpp"
#include "../infra/Vecteur.hpp"

Triangle::Triangle() : Objet() {
  s[0].set(-1, 0, -1);
  s[1].set(1, 0, -1);
  s[2].set(0, 0, 1);
  n.set(0, 0, 1);
}

Triangle::Triangle(const Point p[3], Materiau m) : Objet(m) {
  for (int i = 0; i < 3; i++) s[i] = p[i];
  // calcul de la normale à partir du produit vectoriel AB^AC
  // cette normale doit ensuite être normalisée...

  auto ab = Vecteur(p[0], p[1]);
  auto ac = Vecteur(p[0], p[2]);

  auto res = Vecteur::cross(ab, ac);
  res.normaliser();
  this->n.set(res.dx, res.dy, res.dz);
}

Triangle::~Triangle() {}

bool Triangle::intersecte(const Rayon& r, Intersection& inter) {
  auto origin = r.origine;
  auto direction = r.direction;

  //       d − n⋅ P
  // t = -----------
  //         n⋅d

  // Downside
  auto down = this->n * direction;
  if (down == 0) {
    return false;  // ray is parallel
  }

  // Upside
  auto p = Vecteur(origin.X, origin.Y, origin.Z);

  // d = n * A
  auto a = this->s[0];
  auto d = this->n * Vecteur(a.X, a.Y, a.Z);
  // d - n * P
  auto up = d - this->n * p;

  // t
  auto t = up / down;

  if (t < 0) {
    return false;  // triangle behind
  }

  auto b = this->s[1];
  auto c = this->s[2];
  auto q = Point(origin.X + t * direction.dx, origin.Y + t * direction.dy,
                 origin.Z + t * direction.dz);

  Vecteur ab = Vecteur(a, b);
  Vecteur qa = Vecteur(q, a);

  if ((Vecteur::cross(ab, qa) * this->n) >= 0) {
    return false;
  }

  Vecteur bc = Vecteur(b, c);
  Vecteur qb = Vecteur(q, b);
  if ((Vecteur::cross(bc, qb) * this->n) >= 0) {
    return false;
  }

  Vecteur ca = Vecteur(c, a);
  Vecteur qc = Vecteur(q, c);

  if ((Vecteur::cross(ca, qc) * this->n) >= 0) {
    return false;
  }

  inter = Intersection(q, this, t);

  return true;
}

bool Triangle::coupe(const Rayon& r) { return false; }

Vecteur Triangle::getNormale(const Point& p) { return n; }

ostream& operator<<(ostream& sortie, Triangle& t) {
  sortie << "triangle : ";
  for (int i = 0; i < 3; i++) sortie << t.s[i] << " - ";
  sortie << endl;

  return sortie;
}

void Triangle::affiche(ostream& out) {
  out << "triangle : ";
  for (int i = 0; i < 3; i++) out << s[i] << " - ";
  out << endl;
}

