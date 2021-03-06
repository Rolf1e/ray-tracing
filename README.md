# Load balacing in Ray Tracing computations


## Probleme

Les calculs de ray-tracing requierent gros temps de calcul sur cpu. Comme les
calculs pour chaque pixels sont independants, la parallelisation semble une
bonne approche.

Mais, les temps sont tres variables d'un pixel a l'autre, resultant d'une
balance entre les threads peu avantageuse.

Les tentatives de résolutions naïves de parallelisations procurent une faible accélération due à la différence de 
charge entre les différents processeurs.
L'objectif est d'uniformiser la charge entre les différents cpu.

Ce papier tente de proposer deux nouvelles methodes de chargement de schema de
balancement:
 - Local Distributed Control (LDC)
 - Global Distributed Control (GDC)

Les strategies sont complementaires, LDC est meilleur sur les images peut
complexes a calculer et GDC sur les plus complexes. Des strategies sur les
Image Space. (l29)

## I - Introduction

**Ray Tracing** : une methode pour generer des images 3D, afin d'y mettre un
maximum de details, comme les ombres et les reflets. Trois modeles de
lumiosite: Ombrages/Shading, Reflection, Refraction. On effectue pour chaque
pixel, le calcul des couleurs (RGB) aux intersections entre les objets et des
rayons de lumiere.

Le temps de calcul requis pour chaque pixel dépend du nombre d'objets touché
par ce rayon.

Le Ray Tracing est un probleme qui semble etre approprie pour la
parallelisation car chaque pixel est indépendant des autres. Mais, il patit du probleme de repartition des taches sur le
cpu, n'utilisant pas toutes les capacites du cpu disponible (car le temps pour générer un pixel 
peut énormément varier d'un pixel a un autre).

Deux approches se distinguent: 
 - Object space 
 - Image space 
 
#### Object space On divise l'espace en volummes reguliers ou non. Les volummes
 sont ainsi alloues au processeur de maniere a ce que les volummes voisins soit
 proches dans le cpu. Il faut en effet communiquer les informations d'un rayon
 qui passent d'un volumme a l'autre. Il y a conservation de quel processeur
 s'occuper de quel volumme. 

Le principal probleme de cette approche est le decoupage des volummes afin de
balancer la repartition. 

#### Image space L'image 2D est divisee en "region". Chaque processeur se voit
asigner un certain nombre de regions. Pendant le calcul, on peut effectuer un
swap dans les processeurs, afin de balancer la repartition, si un calcul se
voit etre trop long.


### Description de la machine Courte description du nombre de processeur et de
la machine utilisee pour les experiences.
512 Noeuds avec un maillage de 16 * 32, chaque noeud est un Intel i860.


## II - Local Distributed Control Division de l'ecran en zone de pixels 2x2. On
Taurus Topology
Divise les regions sur les differentes processeurs de maniere intervalle. Cette
methode de division permet de maniere rare (pas sur de la trad) des
repartitions egales, mais semble offrir de meilleures performances.

Pendant les calculs, les IDLE noeuds recuperent du travail des noeuds pleine
action. On veut garder le processeur occuper le plus souvent possible.

Avec chaque noeud a 4 voisins connus. Ils sont numerotes de maniere cyclique:
le plus haut centre est le 1, les autres sont 2,3,4 dans le sens des aiguilles
d'une montre. Si un noeud est IDLE, il demande a son voisinage, s'il tombe sur
un noeud travaillant, il lui demande la moitie de son travail restant.
Quand tous les noeuds vont terminé leur travail, le Ray tracing est terminé. 
 
## III - Global Distributed Control
 Ring Topology
 Les N processeurs sont organises en topologie en anneau, il y a toujours une division de
 l'ecran en region de 2x2 pixels.
 Un processeur va d'abord travailler sur sa région qui lui est assigné. 
Quand un processeur devient IDLE, il parcourt
 la bague et demande a chaque processeur s'il a du travail pour lui. Le noeud
 demandant, retient le noeud qu'il lui a donne le travail. S'il redevient IDLE,
 il recommencera par lui, le noeud donnant, se souvient du noeud demandant, et
 agit de meme. Si dans sa recherche un noeud revient sur lui meme, il s'arrete,
 a priori, y a plus rien a faire.
 Cela garantit que la recherche se terminera lorsque tous les noeuds seront inactifs.

Brouillons :
 Pi demande du travail a Pj
 Pj demande du travail a Pk
 Pi redemande a Pj (si pas de travail) demande directement a Pk sans passer par les noeud entre Pj et Pk

## IV - Experimental Result for High Quality Images

Le tableau 1 montre les caractéristiques de répartition de la charge pour chaque scène.
Chaque scène a une résolution de 512x512 avec un "subray" d'anti aliasing.
La scène est divisée en 256 régions de taille 32x32

La méthode GDC est systématiquement la plus performante.
Elle donne une accélération quasiment linéaire pour les trois scènes

LDC fonctionne également bien, il est légèrement plus rapide que GDC pour moins de 64 processeurs 
et il est très comparable à GDC.
LDC cependant se détériore pour un large nombre de processeurs

(pas sur) : La scène de la balle est la moins 'bonne', elle a la plus grande variation de temps 
de calcul pour les pixels


## V Experimental Results Quality Images

Après les tests sur les trois scènes on remarque que LDC et GDC donnent des bonnes performances.
Les images utilisées étaient de dimension 512x512 avec un anti aliasing de 16.

Cette grande quantité de calcul à tendance a masqué le gros coût associé au load balancing (pas sur du tout)

Il n'est pas toujours nécessaire de générer des images avec autant de qualité.
Si on réalise une simulation avec un faible anti aliasing, alors on aura moins de qualité d'image mais aussi 
beaucoup moins de calcul à faire, cette qualité peut convenir pour beaucoup d'usage / application.

Pour tester l'efficacité de GDC et LDC avec un faible anti aliasing, une expérimentation a été faite sur la 
scène "Tree" avec un anti aliasing de 1 et une image de dimension 256x256.

Les figures 7 et 8 montrent les résultats pour GDC et LDC pour cette expérimentation.

Contrairement au précédente expérimentation on remarque que LDC est plus efficace que GDC.
On a des performances similaires entre 1 et 128 processeurs puis il y a une détérioration notable sur
les performances de GDC avec 256 à 512 noeuds.
