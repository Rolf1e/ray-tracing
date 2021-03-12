#include "Camera.hpp"
#include "objets/Rayon.hpp"

Camera::Camera() {
  position = Point(0.0, 0.0, 2.0);
  ;
  cible = Point(0.0, 0.0, 0.0);
  distance = 2.0;
}

Camera::~Camera() {}

void Camera::genererImage(const Scene& sc, Image& im, int profondeur) {
  // Calcul des dimensions d'un pixel par rapport
  // à la résolution de l'image - On suppose l'image carrée
  // de dimension 2 x 2
  float largeurPixel = 2.0 / im.getLargeur();
  float hauteurPixel = 2.0 / im.getHauteur();

  // Pour chaque pixel
  for (int i = 0; i < im.getLargeur(); i++) {
    for (int j = 0; j < im.getHauteur(); j++) {
      // calcul des coordonnées du centre du pixel
      float milieuX = -1 + largeurPixel / 2.0 + i * largeurPixel;
      float milieuY = 1 - hauteurPixel / 2.0 - j * hauteurPixel;
      Point centre(milieuX, milieuY, 0);

      // Création du rayon
      Vecteur dir(position, centre);
      dir.normaliser();
      Rayon ray(position, dir);

      // Lancer du rayon primaire
      Intersection inter;
      if (sc.intersecte(ray, inter)) {
        im.setPixel(i, j, inter.getCouleur(sc, position, profondeur));
      } else
        im.setPixel(i, j, sc.getFond());

    }  // for j

  }  // for i
}

ostream& operator<<(ostream& out, const Camera& c) {
  out << " position = " << c.position << " - cible = " << c.cible;
  out << " - distance = " << c.distance << flush;
  return out;
}
