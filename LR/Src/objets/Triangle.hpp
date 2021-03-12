#ifndef _TRIANGLE_HPP
#define _TRIANGLE_HPP

#include <iostream>
using namespace std;

#include "Objet.hpp"
#include "Vecteur.hpp"

/**
 * \class Triangle
 * Classe représentant un triangle représenté par ses 3 sommets
 * La classe implante les méthodes permettant sont utilisation dans le cadre
 * d'un algorithme de lancer de rayons.
 *
 * @author  C. Renaud
 * @version 1.0
 * @date Janvier 2021
 * @remark Cette classe fait partie de l'application de lancer de rayons simplifiée 
 * développée pour servir d'exemple aux travaux pratiques dans les modules "High Parallel
 * Computing" et "Initiation à la recherche" du master informatique de l'Université du
 * Littoral Côte d'Opale. 
 * 
 */

class Triangle : public Objet {
private:
  Point s[3];/**< Sommets du triangle, données dans l'ordre direct */
  Vecteur n; /**< Normale à la surface du triangle */
public:
  /**
   * Construit un triangle standard
   */
  Triangle();
  /**
   * Construit un à partir de 3 sommets, de matériau m
   * @param p tableau des 3 sommets du triangle
   * @param m matériau du triangle.
   */
  Triangle(const Point p[3], Materiau m);

  /**
   * détruit le triangle
   */
  ~Triangle();

  /**
   * Calcule l'intersection entre un rayon et le triangle si elle existe. 
   * @param r le rayon pour lequel il faut calculer l'intersection
   * @param inter l'intersection trouvée si elle existe
   * @return true si une intersection est trouvée, auquel cas le paramètre
   * inter contient la description de cette intersection ; false sinon.
   */
  bool intersecte(const Rayon& r, Intersection& inter);

  /**
   * Détermine si le triangle coupe le rayon entre son origine
   * et l'extrémité de son vecteur directeur.
   * @param r le rayon pour lequel le test doit être effectué
   * @return true si le plan coupe le rayon entre son origine
   *  et l'extrémité de son vecteur directeur, false sinon.
   */
  bool coupe(const Rayon& r);

    /**
   * Calcule la normale à la surface du triangle au point considéré.
   * Le vecteur retourné doit être normalisé.
   * @param p le point auquel la normale doit être calculée
   * @return la normale à la surface du triangle au point considéré. Le vecteur
   * retourné est normalisé.
   */
  virtual Vecteur getNormale(const Point &p);


  /**
   * Affichage de la description du triangle sur le flot de sortie,
   *  dans un format lisible par un utilisateur humain.
   * @param sortie le flot de sortie
   * @param p le triangle à afficher
   * @return le flot modifié
   */
  friend ostream& operator<<(ostream & sortie, Triangle & t);



  virtual void affiche(ostream& out);

};
#endif
