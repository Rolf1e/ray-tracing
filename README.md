# Load balacing in Ray Tracing computations


## Probleme

Les calculs de ray-tracing requierent gros temps de calcul sur cpu. Comme les
calculs pour chaque pixels sont independants, la parallelisation semble une
bonne approche.

Mais, les temps sont tres variables d'un pixel a l'autre, resultant d'une
balance entre les threads peu avantageuse.

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


Le Ray Tracing est un probleme qui semble etre approprie pour la
parallelisation. Mais, il patit du probleme de repartition des taches sur le
cpu, n'utilisant pas toutes les capacites du cpu disponible.

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


## II - Local Distributed Control Division de l'ecran en zone de pixels 2x2. On
Taurus Topology
Divise les regions sur les differentes processeurs de maniere intervalle. Cette
methode de division permet de maniere rare (pas sur de la trad) des
repartitions egales, mais semble offrir de meilleures performances.

Pendant les calculs, les IDLE noeuds recuperent du travail des noeuds pleine
action. On veut garder le processeur occuper le plus souvent possible.

Avec chaque noeud a 4 voisins connus. Ils sont numerotes de maniere cyclique:
le plus haut centre est le 1, les autres sont 2,3,4 dans le sens des aiguilles
d'un montre. Si un noeud est IDLE, il demande a son voisinage, s'il tombe sur
un noeud travaillant, il lui demande la moitie du travail.
 
## III - Global Distributed Control
 Ring Topology
 Les N processeurs sont organises en topologie bagues, toujours division de
 l'ecran en region de 2x2 pixels. Quand un processeur devient IDLE, il parcourt
 la bague et demande a chaque processeur s'il a du travail pour lui. Le noeud
 demandant, retient le noeud qu'il lui a donne le travail. S'il redevient IDLE,
 il recommencera par lui, le noeud donnant, se souvient du noeud demandant, et
 agit de meme. Si dans sa recherche un noeud revient sur lui meme, il s'arrete,
 a priori, y a plus rien a faire.


